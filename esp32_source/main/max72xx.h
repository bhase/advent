#ifndef MAX72XX_H_
#define MAX72XX_H_

/* 0 .. MAX_DEVICE, -1: all devices (not implemented yet) */
typedef int Dev_t;

typedef uint8_t DecodeMode_t;
typedef uint8_t Intensity_t;
typedef uint8_t ScanLimit_t;
typedef enum {
    Normal = 0,
    Shutdown,
} Shutdown_t;
typedef uint8_t TestMode_t;
typedef uint8_t Segment_t;
typedef uint8_t Digit_t;

void MAX72XX_write_to_device(void);
void MAX72XX_set_decode_mode(Dev_t device, DecodeMode_t mode);
void MAX72XX_set_intensity(Dev_t device, Intensity_t intensity);
void MAX72XX_set_scan_limit(Dev_t device, ScanLimit_t scan_limit);
void MAX72XX_set_shutdown(Dev_t device, Shutdown_t mode);
void MAX72XX_set_display_test(Dev_t device, TestMode_t mode);
void MAX72XX_init(void);

#endif
