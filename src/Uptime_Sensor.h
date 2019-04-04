#pragma once

#include "ISensor.h"

class Uptime_Sensor : public ISensor
{
  private:
  public:
    Uptime_Sensor() : ISensor(5 * MINUTES) {} // 5 minutes default interval
    Uptime_Sensor(unsigned long interval) : ISensor(interval) {}
    ~Uptime_Sensor() {}

    // publish uptime regularly
    virtual void measure()
    {
        publish("uptime", String((float)millis() / 60000.0)); // publish in minutes
    }
};