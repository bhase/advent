#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "esp_log.h"

#include "cal_display.h"

typedef struct {
    Cal_Event_t event;
    int day;
    int month;
} Time_Event_t;

typedef enum {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
} weekday_t;

static Time_Event_t Time_events[] = {
    [Ronjas_Geburtstag] = { .event = Ronjas_Geburtstag, .day = 2, .month = 12 },
    [Hendriks_Geburtstag] = { .event = Hendriks_Geburtstag, .day = 6, .month = 12 },
    [Fredas_Geburtstag] = { .event = Fredas_Geburtstag, .day = 31, .month = 1 },
    [Lars_Geburtstag] = { .event = Lars_Geburtstag, .day = 19, .month = 12 },
    [Erster_Advent] = { .event = Erster_Advent, .day = -1, .month = -1 },
    [Zweiter_Advent] = { .event = Zweiter_Advent, .day = -1, .month = -1 },
    [Dritter_Advent] = { .event = Dritter_Advent, .day = -1, .month = -1 },
    [Vierter_Advent] = { .event = Vierter_Advent, .day = -1, .month = -1 },
    [Heiligabend] = { .event = Heiligabend, .day = 24, .month = 12 },
    [Sylvester] = { .event = Sylvester, .day = 31, .month = 12 },
};



static weekday_t weekday_of(int year, int month, int day)
{
    return ((( (int)(day + floor(2.6 * ((month + 9) % 12 + 1) - 0.2)
                            + year % 100 + floor(year % 100 / 4) + floor(year / 400)
                            - 2 * floor(year / 100) - 1)
                      % 7) + 7) % 7 + 1) % 7;
}

static int days_until(int year, int month, int day)
{
    time_t now = time(NULL);
    struct tm *then = localtime(&now);

    then->tm_year = year - 1900;
    then->tm_mon = month - 1;
    then->tm_mday = day;

    int seconds = difftime(mktime(then), now);
    return seconds / (60 * 60 * 24);
}

void Time_show_event(void)
{
    static int current_event = 0;
    int days_until_event = 0;

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    do {
        int year = timeinfo->tm_year + 1900;
        if ((Time_events[current_event].month == 1) && (timeinfo->tm_mon > 0)) {
            year += 1; /* event is in next year */
        }
        days_until_event = days_until(year, Time_events[current_event].month, Time_events[current_event].day);
        current_event++;
    } while ((days_until_event < 0) && (current_event < (sizeof(Time_events) / sizeof(Time_events[0]))) );
    ESP_LOGI("CAL", "Showing event %d with days %d", Time_events[current_event].event, days_until_event);
    Cal_display_until_event(Time_events[current_event - 1].event, days_until_event);

    if (current_event >= (sizeof(Time_events) / sizeof(Time_events[0]))) {
        current_event = 0;
    }
}

void Time_init(void)
{
    setenv("TZ", ":Europe/Berlin", 1);
    tzset();

    /* Calculate dates of Advent */
    time_t rawtime;
    struct tm *info; /* member tm_wday: 0 - 6 with 0 := Sunday (days since Sunday) */

    time(&rawtime);
    info = localtime(&rawtime);
    
    int weekday_of_christmas_eve = weekday_of(info->tm_year + 1900, Time_events[Heiligabend].month, Time_events[Heiligabend].day);

    Time_events[Vierter_Advent].day = 24 - weekday_of_christmas_eve;
    Time_events[Vierter_Advent].month = 12; /* Can be only in december */

    Time_events[Dritter_Advent].day = Time_events[Vierter_Advent].day - 7;
    Time_events[Dritter_Advent].month = 12; /* Can be only in december */

    Time_events[Zweiter_Advent].day = Time_events[Dritter_Advent].day - 7;
    Time_events[Zweiter_Advent].month = 12; /* Can be only in december */

    if (Time_events[Zweiter_Advent].day > 7) {
        Time_events[Erster_Advent].day = Time_events[Zweiter_Advent].day - 7;
        Time_events[Erster_Advent].month = 12;
    } else {
        Time_events[Erster_Advent].day = Time_events[Zweiter_Advent].day - 7 + 30;
        Time_events[Erster_Advent].month = 11;
    }

}
