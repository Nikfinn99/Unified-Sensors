#pragma once

#include "ISensor.h"
#include <DHT.h>

class DHT_Sensor : public ISensor
{
  private:
    DHT *m_sensor;

  public:
    DHT_Sensor(int p_pin, int p_type) : DHT_Sensor(p_pin, p_type, 10 * MINUTES) {}

    DHT_Sensor(int p_pin, int p_type, unsigned long p_interval) : ISensor(p_interval)
    {
        // create new dht object attached to corresponding pins
        m_sensor = new DHT(p_pin, p_type);
        m_sensor->begin();
    }

    ~DHT_Sensor()
    {
        // cleanup
        delete m_sensor;
    }

    /**
     * implement measurement function for dht sensor
    */
    virtual void measure() override
    {
        // measure sensor readings
        float temp = m_sensor->readTemperature();
        float hum = m_sensor->readHumidity();

        // set to -1 if sensor measurement was unsucessfull
        if (isnan(temp))
            temp = -1;
        if (isnan(hum))
            hum = -1;

        // publish sensor readings to mqtt
        ISensor::publish("temperature", String(temp));
        ISensor::publish("humidity", String(hum));
    }
};