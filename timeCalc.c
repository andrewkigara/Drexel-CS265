#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct time
{
    int hr;
    int min;
    int sec;
} time;

void sec2hms(int secs)
{
    int timeSec = 0, timeMin = 0, timeHr = 0;

    // Seconds
    timeSec = (secs % 60);
    secs -= timeSec;

    // Minutes
    timeMin = (secs / 60);
    if (timeMin == 60)
    {
        timeMin = 0;
        timeHr += 1;
    }
    else if (timeMin > 60)
    {
        timeMin = (timeMin % 60);
    }
    else
    {
        timeMin = timeMin;
    }

    // Hours
    timeHr += (secs / 3600);
    time sec2hms = {timeHr, timeMin, timeSec};
    printf("The time is %d:%d:%d\n", sec2hms.hr, sec2hms.min, sec2hms.sec);
}

int main()
{
    int timeInSec = 0;
    printf("Enter time in seconds: \n");
    scanf(" %d", &timeInSec);
    sec2hms(timeInSec);
    return 0;
}