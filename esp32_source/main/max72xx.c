#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

#include "max72xx.h"
#include "max72xx_config.h"


typedef enum {
    NoOp_cmd = 0,
    NoOp_reg = 0,
    Digit0_cmd = 1,
    Digit0_reg = 1,
    Digit1_cmd = 2,
    Digit1_reg = 2,
    Digit2_cmd = 3,
    Digit2_reg = 3,
    Digit3_cmd = 4,
    Digit3_reg = 4,
    Digit4_cmd = 5,
    Digit4_reg = 5,
    Digit5_cmd = 6,
    Digit5_reg = 6,
    Digit6_cmd = 7,
    Digit6_reg = 7,
    Digit7_cmd = 8,
    Digit7_reg = 8,
    Decodemode_cmd = 9,
    Decodemode_reg = 9,
    Intensity_cmd = 0xA,
    Intensity_reg = 0xA,
    Scanlimit_cmd = 0xB,
    Scanlimit_reg = 0xB,
    Shutdown_cmd = 0xC,
    Shutdown_reg = 0xC,
    Displaytest_cmd = 0x0f,
    Displaytest_reg = 0xD,
} MAX72XX_Commands_t;

typedef struct {
    /* 14 register per device */
    uint8_t register_mirror[14];
    /* Which registers shall be written */
    uint8_t current_pos;
    MAX72XX_Commands_t transmit_queue[2 * MAX72XX_QUEUE_SIZE]; /* Cmd + data */
} MAX72XX_transfer_list_t;


static spi_device_handle_t MAX72XX_spi;

static MAX72XX_transfer_list_t MAX72XX_transfer_list[MAX72XX_DEVICENUM];

/* Send data to the LCD. Uses spi_device_polling_transmit, which waits until the
 * transfer is complete.
 *
 * Since data transactions are usually small, they are handled in polling
 * mode for higher speed. The overhead of interrupt transactions is more than
 * just waiting for the transaction to complete.
 */
static void MAX72XX_transmit(const uint8_t *data, int len)
{
    esp_err_t ret;
    spi_transaction_t t;
    if (len==0) return;             //no need to send anything
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=len*8;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=data;               //Data
    t.user=(void*)1;                //D/C needs to be set to 1
    ret=spi_device_polling_transmit(MAX72XX_spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

static void MAX72XX_spi_init(void)
{
    esp_err_t ret;
    spi_bus_config_t buscfg={
        .miso_io_num=-1,
        .mosi_io_num=MAX72XX_PIN_NUM_MOSI,
        .sclk_io_num=MAX72XX_PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=32,
    };
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=MAX72XX_SPI_FREQ_HZ,    //Clock out at defined frequency
        .mode=0,                                //SPI mode 0
        .spics_io_num=MAX72XX_PIN_NUM_CS,       //CS pin
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
    };
    //Initialize the SPI bus
    ret=spi_bus_initialize(HSPI_HOST, &buscfg, 0); /* 0 -> no DMA; 1 or 2 could be used */
    ESP_ERROR_CHECK(ret);
    //Attach the device to the SPI bus
    ret=spi_bus_add_device(HSPI_HOST, &devcfg, &MAX72XX_spi);
    ESP_ERROR_CHECK(ret);
}


void MAX72XX_write_to_device(void)
{
    uint8_t transfer_buffer[2 * MAX72XX_DEVICENUM];
    int only_nops = false;
    /* write all relevant registers */
    /* each register is an own transmit event */
    for (int i = 0; (i < (MAX72XX_QUEUE_SIZE * 2)) && (only_nops == false); i += 2) {
        /* max 14 commands to transmit */
        only_nops = true;
        for (int d = 0; d < MAX72XX_DEVICENUM; d++) {
            MAX72XX_transfer_list_t *dev = &MAX72XX_transfer_list[d];
            if (dev->transmit_queue[i] != NoOp_cmd) {
                only_nops = false;
            }
            /* command */
            transfer_buffer[d * 2    ] = dev->transmit_queue[i];
            /* value */
            transfer_buffer[d * 2 + 1] = dev->transmit_queue[i + 1];
        }
        MAX72XX_transmit(transfer_buffer, sizeof(transfer_buffer));
    }

    for (int d = 0; d < MAX72XX_DEVICENUM; d++) {
        memset(MAX72XX_transfer_list[d].transmit_queue, 0, sizeof(MAX72XX_transfer_list[d].transmit_queue));
        MAX72XX_transfer_list[d].current_pos = 0;
    }
}

void MAX72XX_set_decode_mode(Dev_t device, DecodeMode_t mode)
{
    /* bit 0 -> digit 0
     * bit 1 -> digit 1
     * ...
     * bit set -> decode mode B active
     * bit not set -> no decode */
    MAX72XX_transfer_list_t *list = &MAX72XX_transfer_list[device];
    list->register_mirror[Decodemode_reg] = mode;
    list->transmit_queue[list->current_pos++] = Decodemode_cmd;
    list->transmit_queue[list->current_pos++] = mode;
}

void MAX72XX_set_intensity(Dev_t device, Intensity_t intensity)
{
    if (device >= MAX72XX_DEVICENUM) {
        /* out of range */
        return;
    }
    /* 16 steps, 0x0 - 0xF */
    MAX72XX_transfer_list_t *list = &MAX72XX_transfer_list[device];
    list->register_mirror[Intensity_reg] = intensity;
    list->transmit_queue[list->current_pos++] = Intensity_cmd;
    list->transmit_queue[list->current_pos++] = intensity;
}

void MAX72XX_set_scan_limit(Dev_t device, ScanLimit_t scan_limit)
{
    if (device >= MAX72XX_DEVICENUM) {
        /* out of range */
        return;
    }
    /* Enable / disable digits
     * 0 -> only digit 0 active
     * 1 -> digit 0 + 1
     * ...
     * 7 -> all digits active */
    MAX72XX_transfer_list_t *list = &MAX72XX_transfer_list[device];
    list->register_mirror[Scanlimit_reg] = scan_limit;
    list->transmit_queue[list->current_pos++] = Scanlimit_cmd;
    list->transmit_queue[list->current_pos++] = scan_limit;
}

void MAX72XX_set_shutdown(Dev_t device, Shutdown_t mode)
{
    if (device >= MAX72XX_DEVICENUM) {
        /* out of range */
        return;
    }
    /* 1 -> enable shutdowns mode
     * 0 -> normal display mode */
    MAX72XX_transfer_list_t *list = &MAX72XX_transfer_list[device];
    list->register_mirror[Shutdown_reg] = mode;
    list->transmit_queue[list->current_pos++] = Shutdown_cmd;
    list->transmit_queue[list->current_pos++] = mode;
}

void MAX72XX_set_display_test(Dev_t device, TestMode_t mode)
{
    if (device >= MAX72XX_DEVICENUM) {
        /* out of range */
        return;
    }
    /* 1 -> enable test mode
     * 0 -> normal mode resp.shutdown mode when active */
    MAX72XX_transfer_list_t *list = &MAX72XX_transfer_list[device];
    list->register_mirror[Displaytest_reg] = mode;
    list->transmit_queue[list->current_pos++] = Displaytest_cmd;
    list->transmit_queue[list->current_pos++] = mode;
}


void MAX72XX_set_digit_n(Dev_t device, Digit_t digit, Segment_t segments)
{
    if (device >= MAX72XX_DEVICENUM) {
        /* out of range */
        return;
    }
    /* put into local display buffer */
}

void MAX72XX_init(void)
{
    MAX72XX_spi_init();
    memset(MAX72XX_transfer_list, 0, sizeof(MAX72XX_transfer_list));
}
