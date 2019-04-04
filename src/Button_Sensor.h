#pragma once

#include "ISensor.h"
#include <Button.h>

class Button_Sensor : public ISensor
{
  private:
    BUTTON m_btn;
    String m_topic;

  public:
    Button_Sensor(uint8_t pin, uint8_t invert = 0) : Button_Sensor("button", pin, invert) {}

    Button_Sensor(const char *topic, uint8_t pin, uint8_t invert = 0) : ISensor(0), m_btn(pin, invert), m_topic(topic) {}

    ~Button_Sensor() {}

    virtual void measure()
    {
        m_btn.update();

        if (m_btn.changingEdge())
        {
            ISensor::publish(m_topic + "/changed", String(m_btn.lastState()));
        }

        if (m_btn.risingEdge())
        {
            ISensor::publish(m_topic + "/pressed", String(1));
        }

        if (m_btn.fallingEdge())
        {
            ISensor::publish(m_topic + "/released", String(1));
        }
    }
};