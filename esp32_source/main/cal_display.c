#include <stdint.h>
#include <string.h>
#include "max72xx.h"
#include "cal_display.h"

#include "esp_log.h"

/*
   D a b c d e f g  | D a b c d e f g
--------------------+----------------
1  E s M o r g e n  | L s i n d T e s
2  H e u t e G i s  | t D n o c h A o
3  m e h r Q a l s  | L j s e c h s N
4  e i n e z w e i  | d r e i v i e r
5  f ü n f M T a g  | e W o c h e n Z
6  T b i s m z u m  | F r e d a s O p
6  b i s m z u m F  | r e d a s d e r // corrected version with der
7  m R o n j a s v  | H e n d r i k s
8  Y e r s t e n t  | z w e i t e n x
--------------------+-------------------
1  d r i t t e n L  | v i e r t e n u  5
2  A y e H e i l i  | g a b e n d P h  6
3  L a r s N G e b  | u r t s t a g D  7
4  A d v e n t s S  | y l v e s t e r  8
--------------------+-------------------
   a b c d e f g DP | a b c d e f g DP
*/

typedef struct {
    uint16_t pattern;
    Digit_t digit;
    Dev_t dev;
} Cal_word_t;

/* Device 0/1 */

/* Digit 0 */
static const Cal_word_t Word_Es     = { .pattern = 0xC000, .digit = Digit1, .dev = 0 };
static const Cal_word_t Word_Morgen = { .pattern = 0x3F00, .digit = Digit1, .dev = 0 };
static const Cal_word_t Word_sind   = { .pattern = 0x0078, .digit = Digit1, .dev = 0 };
// static const Cal_word_t Word_es     = { .pattern = 0x0003, .digit = Digit1, .dev = 0 };

/* Digit 1 */
static const Cal_word_t Word_Heute  = { .pattern = 0xF800, .digit = Digit2, .dev = 0 };
static const Cal_word_t Word_ist    = { .pattern = 0x0380, .digit = Digit2, .dev = 0 };
static const Cal_word_t Word_noch   = { .pattern = 0x003C, .digit = Digit2, .dev = 0 };

/* Digit 2 */
static const Cal_word_t Word_mehr   = { .pattern = 0xF000, .digit = Digit3, .dev = 0 };
static const Cal_word_t Word_als    = { .pattern = 0x0700, .digit = Digit3, .dev = 0 };
static const Cal_word_t Word_sechs  = { .pattern = 0x003E, .digit = Digit3, .dev = 0 };

/* Digit 3 */
static const Cal_word_t Word_eine   = { .pattern = 0xF000, .digit = Digit4, .dev = 0 };
static const Cal_word_t Word_ein    = { .pattern = 0xE000, .digit = Digit4, .dev = 0 };
static const Cal_word_t Word_zwei   = { .pattern = 0x0F00, .digit = Digit4, .dev = 0 };
static const Cal_word_t Word_drei   = { .pattern = 0x00F0, .digit = Digit4, .dev = 0 };
static const Cal_word_t Word_vier   = { .pattern = 0x000F, .digit = Digit4, .dev = 0 };

/* Digit 4 */
static const Cal_word_t Word_fuenf  = { .pattern = 0xF000, .digit = Digit5, .dev = 0 };
static const Cal_word_t Word_Tage   = { .pattern = 0x0780, .digit = Digit5, .dev = 0 };
// static const Cal_word_t Word_Tag    = { .pattern = 0x0700, .digit = Digit5, .dev = 0 };
static const Cal_word_t Word_Wochen = { .pattern = 0x007E, .digit = Digit5, .dev = 0 };
static const Cal_word_t Word_Woche  = { .pattern = 0x007C, .digit = Digit5, .dev = 0 };
static const Cal_word_t Word_der    = { .pattern = 0x00A2, .digit = Digit5, .dev = 0 };
/* for the corrected front plate this word suits better
static const Cal_word_t Word_der    = { .pattern = 0x0007, .digit = Digit7, .dev = 0 };
*/

/* Digit 5 */
static const Cal_word_t Word_bis    = { .pattern = 0x7000, .digit = Digit6, .dev = 0 };
static const Cal_word_t Word_zum    = { .pattern = 0x0700, .digit = Digit6, .dev = 0 };
static const Cal_word_t Word_zu     = { .pattern = 0x0600, .digit = Digit6, .dev = 0 };
static const Cal_word_t Word_Fredas = { .pattern = 0x00FC, .digit = Digit6, .dev = 0 };

/* Digit 6 */
static const Cal_word_t Word_Ronjas   = { .pattern = 0x7E00, .digit = Digit7, .dev = 0 };
static const Cal_word_t Word_Hendriks = { .pattern = 0x00FF, .digit = Digit7, .dev = 0 };

/* Digit 7 */
static const Cal_word_t Word_ersten  = { .pattern = 0x7E00, .digit = Digit8, .dev = 0 };
static const Cal_word_t Word_erste   = { .pattern = 0x7C00, .digit = Digit8, .dev = 0 };
static const Cal_word_t Word_zweiten = { .pattern = 0x00FE, .digit = Digit8, .dev = 0 };
static const Cal_word_t Word_zweite  = { .pattern = 0x00FD, .digit = Digit8, .dev = 0 };

/* Device 2 */

/* Digit 0 + 4 */
static const Cal_word_t DWord_dritten = { .pattern = 0xFE00, .digit = Digit1, .dev = 2 };
static const Cal_word_t DWord_dritte  = { .pattern = 0xFD00, .digit = Digit1, .dev = 2 };
static const Cal_word_t DWord_vierten = { .pattern = 0x00FE, .digit = Digit1, .dev = 2 };
static const Cal_word_t DWord_vierte  = { .pattern = 0x00FC, .digit = Digit1, .dev = 2 };

/* Digit 1 + 5 */
static const Cal_word_t DWord_Heiligabend = { .pattern = 0x1FFC, .digit = Digit2, .dev = 2 };

/* Digit 2 + 6 */
static const Cal_word_t DWord_Lars       = { .pattern = 0xF000, .digit = Digit3, .dev = 2 };
static const Cal_word_t DWord_Geburtstag = { .pattern = 0x07FE, .digit = Digit3, .dev = 2 };

/* Digit 3 + 7 */
static const Cal_word_t DWord_Advent     = { .pattern = 0xFC00, .digit = Digit4, .dev = 2 };
static const Cal_word_t DWord_Sylvester  = { .pattern = 0x01FF, .digit = Digit4, .dev = 2 };

#define DEV_0_VAL(val)  (((val) & 0xFF00) >> 8)
#define DEV_1_VAL(val)   ((val) & 0x00FF) 

#define DEV_2_DIGIT_a(val)  (((val) & 0xFF00) >> 8)
#define DEV_2_DIGIT_b(val)   ((val) & 0x00FF) 

#define MALE 0
#define FEMALE 1

static const Cal_word_t *Cal_get_word_for_number(int number, int female);

void Cal_display_until_event(Cal_Event_t event, int days)
{
    int weeks = 0;
    uint16_t display_to = 0;

    /* we know there are 3 devices with 8 digits each... */
    /* XXX digits start with 1 - this MAX72.. implementation specific!
     * This also means: index 0 is unused! */
    uint8_t display_buffer[3][9];

    ESP_LOGI("CAL", "Got event %d with %d days left", event, days);

    /* clear display */
    memset(display_buffer, 0, sizeof(display_buffer));

    if (days < 0) {
        /* we do not handle events in the past... */
        return;
    } 

    /* and then add pattern... */
    if (days >= 7) {
        weeks = days / 7;

        if ((days % 7) != 0) {
            /* Es sind noch mehr als ... Wochen bis */
            display_buffer[Word_mehr.dev    ][Word_mehr.digit] |= DEV_0_VAL(Word_mehr.pattern);
            display_buffer[Word_mehr.dev + 1][Word_mehr.digit] |= DEV_1_VAL(Word_mehr.pattern);

            display_buffer[Word_als.dev    ][Word_als.digit] |= DEV_0_VAL(Word_als.pattern);
            display_buffer[Word_als.dev + 1][Word_als.digit] |= DEV_1_VAL(Word_als.pattern);
        }

        if (weeks == 1) {
            /* Es ist noch eine Woche ... bis */
            display_buffer[Word_Es.dev    ][Word_Es.digit] |= DEV_0_VAL(Word_Es.pattern);
            display_buffer[Word_Es.dev + 1][Word_Es.digit] |= DEV_1_VAL(Word_Es.pattern);

            display_buffer[Word_ist.dev    ][Word_ist.digit] |= DEV_0_VAL(Word_ist.pattern);
            display_buffer[Word_ist.dev + 1][Word_ist.digit] |= DEV_1_VAL(Word_ist.pattern);

            display_buffer[Word_noch.dev    ][Word_noch.digit] |= DEV_0_VAL(Word_noch.pattern);
            display_buffer[Word_noch.dev + 1][Word_noch.digit] |= DEV_1_VAL(Word_noch.pattern);

            display_buffer[Word_eine.dev    ][Word_eine.digit] |= DEV_0_VAL(Word_eine.pattern);
            display_buffer[Word_eine.dev + 1][Word_eine.digit] |= DEV_1_VAL(Word_eine.pattern);

            display_buffer[Word_Woche.dev    ][Word_Woche.digit] |= DEV_0_VAL(Word_Woche.pattern);
            display_buffer[Word_Woche.dev + 1][Word_Woche.digit] |= DEV_1_VAL(Word_Woche.pattern);

            display_buffer[Word_bis.dev    ][Word_bis.digit] |= DEV_0_VAL(Word_bis.pattern);
            display_buffer[Word_bis.dev + 1][Word_bis.digit] |= DEV_1_VAL(Word_bis.pattern);
            display_to = 1;
        } else {
            /* Es sind noch ... Wochen bis */
            display_buffer[Word_Es.dev    ][Word_Es.digit] |= DEV_0_VAL(Word_Es.pattern);
            display_buffer[Word_Es.dev + 1][Word_Es.digit] |= DEV_1_VAL(Word_Es.pattern);

            display_buffer[Word_sind.dev    ][Word_sind.digit] |= DEV_0_VAL(Word_sind.pattern);
            display_buffer[Word_sind.dev + 1][Word_sind.digit] |= DEV_1_VAL(Word_sind.pattern);

            display_buffer[Word_noch.dev    ][Word_noch.digit] |= DEV_0_VAL(Word_noch.pattern);
            display_buffer[Word_noch.dev + 1][Word_noch.digit] |= DEV_1_VAL(Word_noch.pattern);

            /* get word for number */
            const Cal_word_t *word = Cal_get_word_for_number(weeks, FEMALE);
            if (weeks > 6) {
                word = &Word_sechs;
            }
            display_buffer[word->dev    ][word->digit] |= DEV_0_VAL(word->pattern);
            display_buffer[word->dev + 1][word->digit] |= DEV_1_VAL(word->pattern);

            display_buffer[Word_Wochen.dev    ][Word_Wochen.digit] |= DEV_0_VAL(Word_Wochen.pattern);
            display_buffer[Word_Wochen.dev + 1][Word_Wochen.digit] |= DEV_1_VAL(Word_Wochen.pattern);

            if (weeks > 6) {
                /* Es sind noch mehr als ... Wochen bis */
                display_buffer[Word_mehr.dev    ][Word_mehr.digit] |= DEV_0_VAL(Word_mehr.pattern);
                display_buffer[Word_mehr.dev + 1][Word_mehr.digit] |= DEV_1_VAL(Word_mehr.pattern);

                display_buffer[Word_als.dev    ][Word_als.digit] |= DEV_0_VAL(Word_als.pattern);
                display_buffer[Word_als.dev + 1][Word_als.digit] |= DEV_1_VAL(Word_als.pattern);
            }

            display_buffer[Word_bis.dev    ][Word_bis.digit] |= DEV_0_VAL(Word_bis.pattern);
            display_buffer[Word_bis.dev + 1][Word_bis.digit] |= DEV_1_VAL(Word_bis.pattern);
            display_to = 1;
        }
    } else if (days == 1) {
        /* Morgen ist */
        display_buffer[Word_Morgen.dev    ][Word_Morgen.digit] |= DEV_0_VAL(Word_Morgen.pattern);
        display_buffer[Word_Morgen.dev + 1][Word_Morgen.digit] |= DEV_1_VAL(Word_Morgen.pattern);

        display_buffer[Word_ist.dev    ][Word_ist.digit] |= DEV_0_VAL(Word_ist.pattern);
        display_buffer[Word_ist.dev + 1][Word_ist.digit] |= DEV_1_VAL(Word_ist.pattern);
    } else if (days == 0) {
        /* Heute ist */
        display_buffer[Word_Heute.dev    ][Word_Heute.digit] |= DEV_0_VAL(Word_Heute.pattern);
        display_buffer[Word_Heute.dev + 1][Word_Heute.digit] |= DEV_1_VAL(Word_Heute.pattern);

        display_buffer[Word_ist.dev    ][Word_ist.digit] |= DEV_0_VAL(Word_ist.pattern);
        display_buffer[Word_ist.dev + 1][Word_ist.digit] |= DEV_1_VAL(Word_ist.pattern);
    } else {
        /* Es sind noch ... Tage bis */
        display_buffer[Word_Es.dev    ][Word_Es.digit] |= DEV_0_VAL(Word_Es.pattern);
        display_buffer[Word_Es.dev + 1][Word_Es.digit] |= DEV_1_VAL(Word_Es.pattern);

        display_buffer[Word_sind.dev    ][Word_sind.digit] |= DEV_0_VAL(Word_sind.pattern);
        display_buffer[Word_sind.dev + 1][Word_sind.digit] |= DEV_1_VAL(Word_sind.pattern);

        display_buffer[Word_noch.dev    ][Word_noch.digit] |= DEV_0_VAL(Word_noch.pattern);
        display_buffer[Word_noch.dev + 1][Word_noch.digit] |= DEV_1_VAL(Word_noch.pattern);

        /* get word for number */
        const Cal_word_t *word = Cal_get_word_for_number(days, MALE);
        display_buffer[word->dev    ][word->digit] |= DEV_0_VAL(word->pattern);
        display_buffer[word->dev + 1][word->digit] |= DEV_1_VAL(word->pattern);

        display_buffer[Word_Tage.dev    ][Word_Tage.digit] |= DEV_0_VAL(Word_Tage.pattern);
        display_buffer[Word_Tage.dev + 1][Word_Tage.digit] |= DEV_1_VAL(Word_Tage.pattern);

        display_buffer[Word_bis.dev    ][Word_bis.digit] |= DEV_0_VAL(Word_bis.pattern);
        display_buffer[Word_bis.dev + 1][Word_bis.digit] |= DEV_1_VAL(Word_bis.pattern);
        display_to = 1;
    }

    switch (event) {
    case Ronjas_Geburtstag:
        if (display_to == 1) {
            /* zu */
            display_buffer[Word_zu.dev    ][Word_zu.digit] |= DEV_0_VAL(Word_zu.pattern);
            display_buffer[Word_zu.dev + 1][Word_zu.digit] |= DEV_1_VAL(Word_zu.pattern);
        }
        display_buffer[Word_Ronjas.dev    ][Word_Ronjas.digit] |= DEV_0_VAL(Word_Ronjas.pattern);
        display_buffer[Word_Ronjas.dev + 1][Word_Ronjas.digit] |= DEV_1_VAL(Word_Ronjas.pattern);

        display_buffer[DWord_Geburtstag.dev][DWord_Geburtstag.digit    ] |= DEV_2_DIGIT_a(DWord_Geburtstag.pattern);
        display_buffer[DWord_Geburtstag.dev][DWord_Geburtstag.digit + 4] |= DEV_2_DIGIT_b(DWord_Geburtstag.pattern);
        break;
    case Hendriks_Geburtstag:
        if (display_to == 1) {
            /* zu */
            display_buffer[Word_zu.dev    ][Word_zu.digit] |= DEV_0_VAL(Word_zu.pattern);
            display_buffer[Word_zu.dev + 1][Word_zu.digit] |= DEV_1_VAL(Word_zu.pattern);
        }
        display_buffer[Word_Hendriks.dev    ][Word_Hendriks.digit] |= DEV_0_VAL(Word_Hendriks.pattern);
        display_buffer[Word_Hendriks.dev + 1][Word_Hendriks.digit] |= DEV_1_VAL(Word_Hendriks.pattern);

        display_buffer[DWord_Geburtstag.dev][DWord_Geburtstag.digit    ] |= DEV_2_DIGIT_a(DWord_Geburtstag.pattern);
        display_buffer[DWord_Geburtstag.dev][DWord_Geburtstag.digit + 4] |= DEV_2_DIGIT_b(DWord_Geburtstag.pattern);
        break;
    case Fredas_Geburtstag:
        if (display_to == 1) {
            /* zu */
            display_buffer[Word_zu.dev    ][Word_zu.digit] |= DEV_0_VAL(Word_zu.pattern);
            display_buffer[Word_zu.dev + 1][Word_zu.digit] |= DEV_1_VAL(Word_zu.pattern);
        }
        display_buffer[Word_Fredas.dev    ][Word_Fredas.digit] |= DEV_0_VAL(Word_Fredas.pattern);
        display_buffer[Word_Fredas.dev + 1][Word_Fredas.digit] |= DEV_1_VAL(Word_Fredas.pattern);

        display_buffer[DWord_Geburtstag.dev][DWord_Geburtstag.digit    ] |= DEV_2_DIGIT_a(DWord_Geburtstag.pattern);
        display_buffer[DWord_Geburtstag.dev][DWord_Geburtstag.digit + 4] |= DEV_2_DIGIT_b(DWord_Geburtstag.pattern);
        break;
    case Lars_Geburtstag:
        if (display_to == 1) {
            /* zu */
            display_buffer[Word_zu.dev    ][Word_zu.digit] |= DEV_0_VAL(Word_zu.pattern);
            display_buffer[Word_zu.dev + 1][Word_zu.digit] |= DEV_1_VAL(Word_zu.pattern);
        }
        display_buffer[DWord_Lars.dev][DWord_Lars.digit    ] |= DEV_2_DIGIT_a(DWord_Lars.pattern);
        display_buffer[DWord_Lars.dev][DWord_Lars.digit + 4] |= DEV_2_DIGIT_b(DWord_Lars.pattern);

        display_buffer[DWord_Geburtstag.dev][DWord_Geburtstag.digit    ] |= DEV_2_DIGIT_a(DWord_Geburtstag.pattern);
        display_buffer[DWord_Geburtstag.dev][DWord_Geburtstag.digit + 4] |= DEV_2_DIGIT_b(DWord_Geburtstag.pattern);
        break;
    case Erster_Advent:
        if (display_to == 1) {
            /* zum */
            display_buffer[Word_zum.dev    ][Word_zum.digit] |= DEV_0_VAL(Word_zum.pattern);
            display_buffer[Word_zum.dev + 1][Word_zum.digit] |= DEV_1_VAL(Word_zum.pattern);

            display_buffer[Word_ersten.dev    ][Word_ersten.digit] |= DEV_0_VAL(Word_ersten.pattern);
            display_buffer[Word_ersten.dev + 1][Word_ersten.digit] |= DEV_1_VAL(Word_ersten.pattern);
        } else {
            display_buffer[Word_erste.dev    ][Word_erste.digit] |= DEV_0_VAL(Word_erste.pattern);
            display_buffer[Word_erste.dev + 1][Word_erste.digit] |= DEV_1_VAL(Word_erste.pattern);

            display_buffer[Word_der.dev    ][Word_der.digit] |= DEV_0_VAL(Word_der.pattern);
            display_buffer[Word_der.dev + 1][Word_der.digit] |= DEV_1_VAL(Word_der.pattern);
        }
        display_buffer[DWord_Advent.dev][DWord_Advent.digit    ] |= DEV_2_DIGIT_a(DWord_Advent.pattern);
        display_buffer[DWord_Advent.dev][DWord_Advent.digit + 4] |= DEV_2_DIGIT_b(DWord_Advent.pattern);
        break;
    case Zweiter_Advent:
        if (display_to == 1) {
            /* zum */
            display_buffer[Word_zum.dev    ][Word_zum.digit] |= DEV_0_VAL(Word_zum.pattern);
            display_buffer[Word_zum.dev + 1][Word_zum.digit] |= DEV_1_VAL(Word_zum.pattern);

            display_buffer[Word_zweiten.dev    ][Word_zweiten.digit] |= DEV_0_VAL(Word_zweiten.pattern);
            display_buffer[Word_zweiten.dev + 1][Word_zweiten.digit] |= DEV_1_VAL(Word_zweiten.pattern);
        } else {
            display_buffer[Word_zweite.dev    ][Word_zweite.digit] |= DEV_0_VAL(Word_zweite.pattern);
            display_buffer[Word_zweite.dev + 1][Word_zweite.digit] |= DEV_1_VAL(Word_zweite.pattern);

            display_buffer[Word_der.dev    ][Word_der.digit] |= DEV_0_VAL(Word_der.pattern);
            display_buffer[Word_der.dev + 1][Word_der.digit] |= DEV_1_VAL(Word_der.pattern);
        }

        display_buffer[DWord_Advent.dev][DWord_Advent.digit    ] |= DEV_2_DIGIT_a(DWord_Advent.pattern);
        display_buffer[DWord_Advent.dev][DWord_Advent.digit + 4] |= DEV_2_DIGIT_b(DWord_Advent.pattern);
        break;
    case Dritter_Advent:
        if (display_to == 1) {
            /* zum */
            display_buffer[Word_zum.dev    ][Word_zum.digit] |= DEV_0_VAL(Word_zum.pattern);
            display_buffer[Word_zum.dev + 1][Word_zum.digit] |= DEV_1_VAL(Word_zum.pattern);

            display_buffer[DWord_dritten.dev][DWord_dritten.digit    ] |= DEV_2_DIGIT_a(DWord_dritten.pattern);
            display_buffer[DWord_dritten.dev][DWord_dritten.digit + 4] |= DEV_2_DIGIT_b(DWord_dritten.pattern);
        } else {
            display_buffer[DWord_dritte.dev][DWord_dritte.digit    ] |= DEV_2_DIGIT_a(DWord_dritte.pattern);
            display_buffer[DWord_dritte.dev][DWord_dritte.digit + 4] |= DEV_2_DIGIT_b(DWord_dritte.pattern);

            display_buffer[Word_der.dev    ][Word_der.digit] |= DEV_0_VAL(Word_der.pattern);
            display_buffer[Word_der.dev + 1][Word_der.digit] |= DEV_1_VAL(Word_der.pattern);
        }

        display_buffer[DWord_Advent.dev][DWord_Advent.digit    ] |= DEV_2_DIGIT_a(DWord_Advent.pattern);
        display_buffer[DWord_Advent.dev][DWord_Advent.digit + 4] |= DEV_2_DIGIT_b(DWord_Advent.pattern);
        break;
    case Vierter_Advent:
        if (display_to == 1) {
            /* zum */
            display_buffer[Word_zum.dev    ][Word_zum.digit] |= DEV_0_VAL(Word_zum.pattern);
            display_buffer[Word_zum.dev + 1][Word_zum.digit] |= DEV_1_VAL(Word_zum.pattern);

            display_buffer[DWord_vierten.dev][DWord_vierten.digit    ] |= DEV_2_DIGIT_a(DWord_vierten.pattern);
            display_buffer[DWord_vierten.dev][DWord_vierten.digit + 4] |= DEV_2_DIGIT_b(DWord_vierten.pattern);
        } else {
            display_buffer[DWord_vierte.dev][DWord_vierte.digit    ] |= DEV_2_DIGIT_a(DWord_vierte.pattern);
            display_buffer[DWord_vierte.dev][DWord_vierte.digit + 4] |= DEV_2_DIGIT_b(DWord_vierte.pattern);

            display_buffer[Word_der.dev    ][Word_der.digit] |= DEV_0_VAL(Word_der.pattern);
            display_buffer[Word_der.dev + 1][Word_der.digit] |= DEV_1_VAL(Word_der.pattern);
        }

        display_buffer[DWord_Advent.dev][DWord_Advent.digit    ] |= DEV_2_DIGIT_a(DWord_Advent.pattern);
        display_buffer[DWord_Advent.dev][DWord_Advent.digit + 4] |= DEV_2_DIGIT_b(DWord_Advent.pattern);
        break;
    case Heiligabend:
        display_buffer[DWord_Heiligabend.dev][DWord_Heiligabend.digit    ] |= DEV_2_DIGIT_a(DWord_Heiligabend.pattern);
        display_buffer[DWord_Heiligabend.dev][DWord_Heiligabend.digit + 4] |= DEV_2_DIGIT_b(DWord_Heiligabend.pattern);
        break;
    case Sylvester:
        display_buffer[DWord_Sylvester.dev][DWord_Sylvester.digit    ] |= DEV_2_DIGIT_a(DWord_Sylvester.pattern);
        display_buffer[DWord_Sylvester.dev][DWord_Sylvester.digit + 4] |= DEV_2_DIGIT_b(DWord_Sylvester.pattern);
        break;
    }

    /* And now: update device register */
    /* each device */
    for (int dev = 0; dev < 3; dev++) {
        /* every digit */
        for (int digit = 1; digit < 9; digit++) {
            MAX72XX_set_digit_n(dev, digit, display_buffer[dev][digit]);
        }
    }
    MAX72XX_write_to_device();
}

void Cal_init_display(void)
{
    /* Set the initial values for three MAX72.. IC */
    MAX72XX_init();
    for (int dev = 0; dev < 3; dev++) {
        MAX72XX_set_scan_limit(dev, EightDigit);
        MAX72XX_set_shutdown(dev, Normal);
        MAX72XX_set_intensity(dev, 0xF);
    }
    MAX72XX_write_to_device();
}

static const Cal_word_t *Cal_get_word_for_number(int number, int female)
{
    static const Cal_word_t word_empty = { .dev = 0, .digit = Digit1, .pattern = 0 };
    switch(number) {
    case 1:
        if (female) {
            return &Word_eine;
        }
        return &Word_ein;
        break;
    case 2:
        return &Word_zwei;
        break;
    case 3:
        return &Word_drei;
        break;
    case 4:
        return &Word_vier;
        break;
    case 5:
        return &Word_fuenf;
        break;
    case 6:
        return &Word_sechs;
        break;
    default:
        /* what now? */
        return &word_empty;
        break;
    }
}
