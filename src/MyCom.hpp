#pragma once

#include <RF24.h>
#include <RF24Network.h>

namespace lacar::droid::firmware
{
    class MyCom
    {
    public:
        enum class PacketType : uint8_t
        {
            RTCMStreamChunk = 0,
        };

    private:
        static MyCom s_Instance;

    public:
        static inline MyCom &getInstance(void) noexcept
        {
            return s_Instance;
        }

    private:
        RF24 m_RF24;
        RF24Network m_RF24Network;
        uint8_t m_Status;

    public:
        MyCom(void) noexcept;

    public:
        inline const uint8_t &getStatus(void) noexcept
        {
            return m_Status;
        }

    public:
        void setup(void) noexcept;

        void loop(void) noexcept;
    };
}