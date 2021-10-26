#include <Arduino.h>
#include <SimpleDHT.h>

class Sensors
{
public:
    Sensors();
    void turnOnPump();
    void detectLights();
    void detectTempAndHumidiry();

private:
    SimpleDHT11 dht11;
};

Sensors::Sensors()
{
    // // pump
    // pinMode(PIN2, OUTPUT);

    // // humidity
    pinMode(PIN3, INPUT);

    // lights sensor
    pinMode(PIN_A0, INPUT);
    SimpleDHT11 dht11(3);
};

void Sensors::turnOnPump()
{
    digitalWrite(PIN2, HIGH);
    digitalWrite(PIN2, LOW);
};

void Sensors::detectLights()
{
    int data = analogRead(PIN_A0);
    Serial.print("Lights: ");
    Serial.println(data);
};

void Sensors::detectTempAndHumidiry()
{
    float temperature = 0;
    float humidity = 0;
    byte data[40] = {0};
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read2(&temperature, &humidity, data)) != SimpleDHTErrSuccess)
    {
        Serial.print("Read DHT22 failed, err=");
        Serial.print(SimpleDHTErrCode(err));
        Serial.print(",");
        Serial.println(SimpleDHTErrDuration(err));
        return;
    }

    Serial.print("Sample OK: ");
    Serial.print((float)temperature);
    Serial.print(" *C, ");
    Serial.print((float)humidity);
    Serial.println(" RH%");
};
