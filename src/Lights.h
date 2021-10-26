#include <Arduino.h>

class Lights
{
private:
    bool lightsOn;

public:
    Lights()
    {
        pinMode(PIN2, OUTPUT);
        lightsOn = false;
    }

    void turnOn()
    {
        if (lightsOn)
        {
            return;
        }
        digitalWrite(PIN2, HIGH);
        lightsOn = true;
    }

    void turnOff()
    {
        if (!lightsOn)
        {
            return;
        }
        digitalWrite(PIN2, LOW);
        lightsOn = false;
    }
};
