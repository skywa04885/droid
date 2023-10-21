#include "MyAccelerometer.hpp"
#include "config.hpp"

namespace lacar::droid::firmware
{
    MyAccelerometer MyAccelerometer::s_Instance;

    MyAccelerometer::MyAccelerometer(void) noexcept : m_ADXL345(),
                                                      m_Status(255U)
    {
    }

    void MyAccelerometer::setup(void) noexcept
    {
        m_ADXL345.begin();

        if (m_ADXL345.getDeviceID() != 0xE5)
        {
            m_Status = 1U;
            return;
        }

        m_Status = 0U;
    }

    void MyAccelerometer::loop(void) noexcept
    {
        if (m_Status != 0U)
        {
            return;
        }
    }
}
