#pragma once

#include <Arduino.h>
#include <MQTT_Client.h>

#define SECONDS 1000
#define MINUTES 60 * SECONDS
#define HOURS 60 * MINUTES
#define DAYS 24 * HOURS

class ISensor
{
private:
  unsigned long m_meas_interval, m_last_measurement;
  MQTT_Client *m_mqtt_client;

protected:
  /**
   * publish method for sensor measurements
   * ensures that client has been initialized
   * 
   * @param topic sub_topic for mqtt message
   * @param message sensor measurement to publish
  */
  ISensor &publish(const String &p_topic, const String &p_message)
  {
    //check if mqtt_client has been initialized
    if (m_mqtt_client)
    {
      // publish message to topic
      m_mqtt_client->publish(p_topic, p_message);
    }
    return *this;
  }

  /**
   * interface method for sensor measurement
   * only for use inside class
  */
  virtual void measure() = 0;

public:
  ISensor(unsigned long p_interval) : m_meas_interval(p_interval), m_last_measurement(0), m_mqtt_client(nullptr) {}

  ~ISensor() {}

  /**
   * attach existing MQTT_Client to sensor
   * enables publishing of messages
   * 
   * @param client mqtt_client to attach to sensor
  */
  ISensor &setClient(MQTT_Client *p_client)
  {
    m_mqtt_client = p_client;
    return *this;
  }

  /**
   * update method for sensor
   * this will call the overridden measurement function every interval
   * call this method regulary to ensure correct functionality
  */
  ISensor &update()
  {
    // check if interval has expired
    if (millis() > m_last_measurement + m_meas_interval)
    {
      // update last measurment time
      m_last_measurement = millis();

      // call overridden method
      measure();
    }
    return *this;
  }
};