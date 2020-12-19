#ifndef MAX72XX_CONFIG_H_
#define MAX72XX_CONFIG_H_

/* The number of devices in daisy chain */
#define MAX72XX_DEVICENUM 3

/* IO pins used */
#define MAX72XX_PIN_NUM_MOSI 13
#define MAX72XX_PIN_NUM_CLK  14
#define MAX72XX_PIN_NUM_CS   15

/* SPI frequency */
#define MAX72XX_SPI_FREQ_HZ (1*1000*1000)

/* The chip has 14 'register', so max 14 commands should be sufficient */
#define MAX72XX_QUEUE_SIZE  14

#endif
