#include <stdint.h>

/* Commands
 * NoOp - 0
 * D0 - 1
 * D1 - 2
 * D2 - 3
 * D3 - 4
 * D4 - 5
 * D5 - 6
 * D6 - 7
 * D7 - 8
 * DecodeMode - 9
 * Intensity - A
 * ScanLimit - B
 * Shutdown - C
 * DisplayTest - F
 */

typedef enum {
    NOOP = 0,
    DIGIT0,
    DIGIT1,
    DIGIT2,
    DIGIT3,
    DIGIT4,
    DIGIT5,
    DIGIT6,
    DIGIT7,
    DECODEMODE,
    INTENSITY,
    SCANLIMIT,
    SHUTDOWN,
    DISPLAYTEST = 0x0f
} MAX72XX_Commands_t;

typedef uint8_t Dev_t;
typedef uint8_t DecodeMode_t;
typedef uint8_t Intensity_t;
typedef uint8_t ScanLimit_t;
typedef uint8_t Shutdown_t;
typedef uint8_t TestMode_t;
typedef uint8_t Segment_t;
typedef uint8_t Digit_t;

static void MAX72XX_set_digit_n(Dev_t device, Segment_t segments, Digit_t digit);

void MAX72XX_write_to_device(void)
{
}

void MAX72XX_set_decode_mode(Dev_t device, DecodeMode_t mode)
{
    /* bit 0 -> digit 0
     * bit 1 -> digit 1
     * ...
     * bit set -> decode mode B active
     * bit not set -> no decode */
}

void MAX72XX_set_intensity(Dev_t device, Intensity_t intensity)
{
    /* 16 steps, 0x0 - 0xF */
}

void MAX72XX_set_scan_limit(Dev_t device, ScanLimit_t scan_limit)
{
    /* Enable / disable digits
     * 0 -> only digit 0 active
     * 1 -> digit 0 + 1
     * ...
     * 7 -> all digits active */
}

void MAX72XX_set_shutdown(Dev_t device, Shutdown_t mode)
{
    /* 1 -> enable shutdowns mode
     * 0 -> normal display mode */
}

void MAX72XX_set_display_test(Dev_t device, TestMode_t mode)
{
    /* 1 -> enable test mode
     * 0 -> normal mode resp.shutdown mode when active */
}

void MAX72XX_set_digit_0(Dev_t device, Segment_t segment)
{
    MAX72XX_set_digit_n(device, segment, 0);
}

static void MAX72XX_set_digit_n(Dev_t device, Segment_t segments, Digit_t digit)
{
    /* put into local display buffer */
}
