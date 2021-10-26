#include <Arduino.h>

#include "Moisture.h"
#include "Weather.h"
#include "TimeController.h"
#include "Lights.h"

Moisture *moisture;
Weather *weather;
TimeController *time;
Lights *lights;

void setup()
{
  Serial.begin(9600);
  moisture = new Moisture();
  weather = new Weather();
  time = new TimeController();
  lights = new Lights();
}

void read()
{
  if (Serial.available() > 0)
  {
    char buf[100];
    int rlen = Serial.readBytesUntil('\n', buf, 100);

    if (buf[0] == 'S')
    {
      if (buf[1] == 'T')
      {
        time->setTime(buf);
      }
      if (buf[1] == 'L')
      {
        if (buf[2] == '1')
        {
          lights->turnOn();
        }
        else
        {
          lights->turnOff();
        }
      }
    }
    else if (buf[0] == 'G')
    {
      if (buf[1] == 'T')
      {
        Serial.println(time->getTimeString());
      }
      else if (buf[1] == 'W')
      {
        Serial.println(weather->getTempAndHumidity());
      }
      else if (buf[1] == 'G')
      {
        Serial.println(moisture->read(buf));
      }
    }

    Serial.print("I received: ");
    for (int i = 0; i < rlen; i++)
    {
      Serial.print(buf[i]);
    }
    Serial.println();
  }
}

void setLights()
{
  Ds1302::DateTime dt = time->getTime();
  if (dt.hour >= 8 && dt.hour < 19)
  {
    lights->turnOn();
  }
  else
  {
    lights->turnOff();
  }
}

void loop()
{
  delay(2000);
  read();
  setLights();
}
