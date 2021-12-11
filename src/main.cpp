#include <Arduino.h>

#include "Moisture.h"
#include "Weather.h"
#include "TimeController.h"
#include "Lights.h"
#include "Config.h"

Moisture *moisture;
Weather *weather;
TimeController *time;
Lights *lights;
Config *config;

// @TODO make class for this shit
const int ASCII_SWAP = 48;
const int DECIMAL_MULTIPLIER = 10;

void setup()
{
  Serial.begin(9600);
  moisture = new Moisture();
  weather = new Weather();
  time = new TimeController();
  lights = new Lights();
  config = new Config();
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
      else if (buf[1] == 'L')
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
      else if (buf[1] == 'C')
      {
        config->setBegin(
            (buf[2] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[3] - ASCII_SWAP),
            (buf[4] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[5] - ASCII_SWAP));
        config->setEnd(
            (buf[6] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[7] - ASCII_SWAP),
            (buf[8] - ASCII_SWAP) * DECIMAL_MULTIPLIER + (buf[9] - ASCII_SWAP));
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
  int startTime = config->getBegin()->getHour() * 60 + config->getBegin()->getMinute();
  int endTime = config->getEnd()->getHour() * 60 + config->getEnd()->getMinute();

  if ((dt.hour * 60 + dt.minute >= startTime) && (dt.hour * 60 + dt.minute < endTime))
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
  delay(1900);
  read();
  delay(100);
  setLights();
}
