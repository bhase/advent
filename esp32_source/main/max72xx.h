#ifndef MAX72XX_H_
#define MAX72XX_H_

/* 0 .. MAX_DEVICE, -1: all devices */
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

#endif
