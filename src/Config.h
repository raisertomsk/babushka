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
        byte minute = eeprom_read_byte(1);
        if (hour > 23)
        {
            hour = 8;
        }
        begin->set(hour, minute);

        hour = eeprom_read_byte(2);
        minute = eeprom_read_byte(3);
        if (hour > 23)
        {
            hour = 19;
        }
        end->set(hour, minute);
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
