#include <Arduino.h>
#include <SimpleDHT.h>

class Weather
{
private:
    SimpleDHT11 dht11;

public:
    Weather()
    {
        dht11 = SimpleDHT11(PIN4);
    }

    String getTempAndHumidity()
    {
        float temperature = 0;
        float humidity = 0;
        byte data[40] = {0};
        int err = SimpleDHTErrSuccess;
        if ((err = dht11.read2(&temperature, &humidity, data)) != SimpleDHTErrSuccess)
        {
            return "F";
        }
        return "T" + (String)temperature + "H" + (String)humidity;
    };
};
