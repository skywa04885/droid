#pragma once

#include <Adafruit_ADXL345_U.h>

namespace lacar::droid::firmware
{
    class MyAccelerometer
    {
    private:
        static MyAccelerometer s_Instance;
    
    public:
        static inline MyAccelerometer &getInstance(void) noexcept {
            return s_Instance;
        }

    private:
        Adafruit_ADXL345_Unified m_ADXL345;
        uint8_t m_Status;
    
    public:
        MyAccelerometer(void) noexcept;

    public:
        inline const uint8_t &getStatus(void) const noexcept
        {
            return m_Status;
        }

    public:

        void setup(void) noexcept;

        void loop(void) noexcept;
    };
}