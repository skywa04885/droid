#pragma once

#include <Arduino.h>
#include <RF24.h>
#include <RF24Network.h>

namespace lacar::droid::firmware {
    class MyLocalConfig
    {
    private:
        static MyLocalConfig s_Instance;
    
    public:
        static MyLocalConfig &getInstance(void) noexcept {
            return s_Instance;
        }

    private:
        uint8_t m_RadioFrequencyChannel;
    

    };
}