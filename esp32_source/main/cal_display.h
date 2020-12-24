#ifndef CAL_DISPLAY_H_
#define CAL_DISPLAY_H_

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

void Cal_display_until_event(Cal_Event_t event, int days);
void Cal_init_display(void);

#endif
