#include <Arduino.h>

class Moisture
{
public:
    String read(char buf[100])
    {
        int pin = 0;
        switch (buf[2])
        {
        case '1':
            pin = PIN_A1;
            break;
        case '2':
            pin = PIN_A2;
            break;
        case '3':
            pin = PIN_A3;
            break;
        case '4':
            pin = PIN_A4;
            break;
        case '5':
            pin = PIN_A5;
            break;
        }
        if (pin == 0)
        {
            return "F";
        }
        return (String)analogRead(pin);
    }
};
