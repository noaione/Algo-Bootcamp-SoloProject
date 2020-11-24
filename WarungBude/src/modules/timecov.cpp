#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "timecov.h"

char *mapMonths(int month) {
    switch (month) {
        case 0:
            return (char *)"January";
        case 1:
            return (char *)"February";
        case 2:
            return (char *)"March";
        case 3:
            return (char *)"April";
        case 4:
            return (char *)"May";
        case 5:
            return (char *)"June";
        case 6:
            return (char *)"July";
        case 7:
            return (char *)"August";
        case 8:
            return (char *)"September";
        case 9:
            return (char *)"October";
        case 10:
            return (char *)"November";
        case 11:
            return (char *)"December";
        default:
            return (char *)"Unknown";
    }
}

char *mapDays(int wday) {
    switch (wday) {
        case 0:
            return (char *)"Monday";
        case 1:
            return (char *)"Tuesday";
        case 2:
            return (char *)"Wednesday";
        case 3:
            return (char *)"Thursday";
        case 4:
            return (char *)"Friday";
        case 5:
            return (char *)"Saturday";
        case 6:
            return (char *)"Sunday";
        default:
            return (char *)"Unknown";
    }
}

tm *currentTime() {
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo;
    timeinfo = localtime(&rawtime);
    return timeinfo;
}

TimeData *convertToTimeData(tm *time_info) {
    TimeData *time_proper = (TimeData*)malloc(sizeof(TimeData));
    if (time_info->tm_sec == 60) {
        time_info->tm_sec = 59;
    }
    time_proper->secs = time_info->tm_sec;
    sprintf(time_proper->psecs, "%02d", time_info->tm_sec);
    time_proper->mins = time_info->tm_min;
    sprintf(time_proper->pmins, "%02d", time_info->tm_min);
    time_proper->hours = time_info->tm_hour;
    sprintf(time_proper->phours, "%02d", time_info->tm_hour);
    time_proper->mdays = time_info->tm_mday;
    sprintf(time_proper->pmdays, "%02d", time_info->tm_mday);
    time_proper->months = time_info->tm_mon;
    sprintf(time_proper->pmonths, "%02d", time_info->tm_mon + 1);
    strcpy(time_proper->smonths, mapMonths(time_info->tm_mon));
    sprintf(time_proper->s3months, "%.3s", time_proper->smonths);
    time_proper->years = 1900 + time_info->tm_year;
    time_proper->wdays = time_info->tm_wday;
    strcpy(time_proper->swdays, mapDays(time_proper->wdays));
    sprintf(time_proper->s3wdays, "%.3s", time_proper->swdays);
    time_proper->ydays = time_info->tm_yday;
    sprintf(time_proper->pydays, "%03d", time_proper->ydays + 1);
    if (time_info->tm_isdst > 0) {
        time_proper->is_dst = true;
    } else {
        time_proper->is_dst = false;
    }
    return time_proper;
}