#include <Arduino.h>
#include <avr/eeprom.h>
#include "TimeConfig.h"

class Config
{
private:
    TimeConfig *begin;
    TimeConfig *end;

    void load()
    {
        byte hour = eeprom_read_byte(0);
        Serial.print("Start hour red: ");
        Serial.println(hour);

        byte minute = eeprom_read_byte(1);
        Serial.print("Start minute red: ");
        Serial.println(minute);
        if (hour > 23)
        {
            hour = 8;
        }
        begin->set(hour, minute);

        hour = eeprom_read_byte(2);
        Serial.print("End hour red: ");
        Serial.println(hour);

        minute = eeprom_read_byte(3);
        Serial.print("End minute red: ");
        Serial.println(minute);
        if (hour > 23)
        {
            hour = 19;
        }
        begin->set(hour, minute);
    }

    void save()
    {
        eeprom_update_byte(0, begin->getHour());
        eeprom_update_byte(1, begin->getMinute());
        eeprom_update_byte(2, end->getHour());
        eeprom_update_byte(3, end->getMinute());
    }

public:
    Config()
    {
        begin = new TimeConfig();
        end = new TimeConfig();
        load();
    }

    TimeConfig *getBegin()
    {
        return begin;
    }

    TimeConfig *getEnd()
    {
        return end;
    }

    void setBegin(byte hour, byte minute)
    {
        begin->set(hour, minute);
        save();
    }

    void setEnd(byte hour, byte minute)
    {
        end->set(hour, minute);
        save();
    }
};
