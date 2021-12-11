#include <Arduino.h>

class TimeConfig
{
private:
    byte hour;
    byte minute;

public:
    void set(byte newHour, byte newMinute)
    {
        if (newHour < 0 || newHour > 23)
        {
            hour = 0;
        }
        else
        {
            hour = newHour;
        }

        if (newMinute < 0 || newMinute > 59)
        {
            minute = 0;
        }
        else
        {
            minute = newMinute;
        }
    }

    byte getHour()
    {
        return hour;
    }

    byte getMinute()
    {
        return minute;
    }
};
