#include <Arduino.h>
#include <Ds1302.h>

class TimeController
{

    const int ASCII_SWAP = 48;
    const int DECIMAL_MULTIPLIER = 10;

private:
    Ds1302 *rtc;

public:
    TimeController()
    {
        pinMode(PIN5, OUTPUT);
        pinMode(PIN6, OUTPUT);
        pinMode(PIN7, OUTPUT);
        rtc = new Ds1302(PIN7, PIN5, PIN6);
        rtc->init();
    }

    void setTime(char buf[100])
    {
        Ds1302::DateTime dt;
        dt.year = (buf[2] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[3] - ASCII_SWAP);
        dt.month = (buf[4] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[5] - ASCII_SWAP);
        dt.day = (buf[6] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[7] - ASCII_SWAP);
        dt.hour = (buf[8] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[9] - ASCII_SWAP);
        dt.minute = (buf[10] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[11] - ASCII_SWAP);
        dt.second = (buf[12] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[13] - ASCII_SWAP);
        rtc->setDateTime(&dt);
    }

    Ds1302::DateTime getTime()
    {
        Ds1302::DateTime dt;
        rtc->getDateTime(&dt);
        return dt;
    }

    String getTimeString()
    {
        Ds1302::DateTime dt = getTime();
        return (String)dt.year + (String)dt.month + (String)dt.day + (String)dt.hour + (String)dt.minute + (String)dt.second;
    }
};
