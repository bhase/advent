#include <stdint.h>

/*
   D a b c d e f g | D a b c d e f g
--------------------+----------------
1  E s M o r g e n  | L s i n d T e s
2  H e u t e G i s  | t D n o c h A o
3  m e h r Q a l s  | L j s e c h s N
4  e i n e z w e i  | d r e i v i e r
5  f ü n f M T a g  | e W o c h e n Z
6  T b i s m z u m  | F r e d a s O p
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

typedef enum {
    Ronjas_Geburtstag,
    Hendriks_Geburtstag,
    Fredas_Geburtstag,
    Lars_Geburtstag,
    Erster_Advent,
    Zweiter_Advent,
    Dritter_Advent,
    Vierter_Advent,
    Heiligabend,
    Sylvester
} Cal_Event_t;

#if 0

/* Digit 0 */
static const uint16_t Word_Es     = 0xC000;
static const uint16_t Word_Morgen = 0x3F00;
static const uint16_t Word_sind   = 0x0070;
static const uint16_t Word_es     = 0x0003;

/* Digit 1 */
static const uint16_t Word_Heute  = 0xF000;
static const uint16_t Word_ist    = 0x0380;
static const uint16_t Word_noch   = 0x003C;

/* Digit 2 */
static const uint16_t Word_mehr   = 0xF000;
static const uint16_t Word_als    = 0x0700;
static const uint16_t Word_sechs  = 0x003E;

/* Digit 3 */
static const uint16_t Word_eine   = 0xF000;
static const uint16_t Word_ein    = 0xE000;
static const uint16_t Word_zwei   = 0x0F00;
static const uint16_t Word_drei   = 0x00F0;
static const uint16_t Word_vier   = 0x000F;

/* Digit 4 */
static const uint16_t Word_fuenf  = 0xF000;
static const uint16_t Word_Tage   = 0x0710;
static const uint16_t Word_Tag    = 0x0700;
static const uint16_t Word_Wochen = 0x007E;
static const uint16_t Word_Woche  = 0x007C;

/* Digit 5 */
static const uint16_t Word_bis    = 0x7000;
static const uint16_t Word_zum    = 0x0700;
static const uint16_t Word_zu     = 0x0600;
static const uint16_t Word_Fredas = 0x00FC;

/* Digit 6 */
static const uint16_t Word_Ronjas = 0x7E00;
static const uint16_t Word_Hendriks = 0x00FF;

/* Digit 7 */
static const uint16_t Word_ersten = 0x7E00;
static const uint16_t Word_zweiten = 0x00FE;

/* Digit 0 + 4 */
static const uint16_t Word_dritten = 0xFE00;
static const uint16_t Word_vierten = 0x00FE;

/* Digit 1 + 5 */
static const uint16_t Word_Heiligabend = 0x1FFC;

/* Digit 2 + 6 */
static const uint16_t Word_Lars = 0xF000;
static const uint16_t Word_Geburtstag = 0x07FE;

/* Digit 3 + 7 */
static const uint16_t Word_Advent = 0xFE00;
static const uint16_t Word_Sylvester = 0x01FF;
#endif 

#define HIGH_BYTE(val) (((val) & 0xFF00) >> 8)
#define LOW_BYTE(val)   ((val) & 0x00FF) 

void Cal_display_until_event(Cal_Event_t event, unsigned int days)
{
    int weeks = 0;
    uint16_t display_to = 0;

    if (days >= 7) {
        weeks = days / 7;
        if (weeks == 1) {
            /* Es ist noch eine Woche ... bis */
            display_to = 1;
        } else if (weeks <= 6) {
            /* Es sind noch ... Wochen bis */
            display_to = 1;
        } else {
            /* Es sind noch mehr als ... Wochen bis */
            display_to = 1;
        }
    } else if (days == 1) {
        /* Morgen ist */
    } else if (days == 0) {
        /* Heute ist */
    } else {
        /* Es sind noch ... Tage bis */
        display_to = 1;
    }

    switch (event) {
    case Ronjas_Geburtstag:
        if (display_to == 1) {
            /* zu */
        }
        break;
    case Hendriks_Geburtstag:
        if (display_to == 1) {
            /* zu */
        }
        break;
    case Fredas_Geburtstag:
        if (display_to == 1) {
            /* zu */
        }
        break;
    case Lars_Geburtstag:
        if (display_to == 1) {
            /* zu */
        }
        break;
    case Erster_Advent:
        if (display_to == 1) {
            /* zum */
        }
        break;
    case Zweiter_Advent:
        if (display_to == 1) {
            /* zum */
        }
        break;
    case Dritter_Advent:
        if (display_to == 1) {
            /* zum */
        }
        break;
    case Vierter_Advent:
        if (display_to == 1) {
            /* zum */
        }
        break;
    case Heiligabend:
        break;
    case Sylvester:
        break;
    }
}
