#pragma once

#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

namespace lacar::droid::firmware
{
    class MyGPS
    {
    public:
        enum class Status : uint8_t {
            Ok = 0,
            BeginFailed,
            PushRawDataFailed,
        };

    private:
        static MyGPS s_Instance;

    public:
        static inline MyGPS &getInstance(void) noexcept
        {
            return s_Instance;
        }

    private:
        SFE_UBLOX_GNSS m_GPS;
        Status m_Status;
        uint32_t m_LastUpdateMillis;
        float m_HDOP;
        float m_PDOP;

    public:
        MyGPS(void) noexcept;

    public:
        inline const Status &getStatus(void) const noexcept
        {
            return m_Status;
        }

        inline const float &getHDOP(void) const noexcept
        {
            return m_HDOP;
        }

        inline const float &getPDOP(void) const noexcept
        {
            return m_PDOP;
        }

    public:
        /// @brief performs all the setup for the GPS. 
        void setup(void) noexcept;

        /// @brief performs all the processing for the GPS.
        void loop(void) noexcept;

        /// @brief writes the given RTCM stream chunk.
        /// @param chunk the RTCM stream chunk.
        /// @param chunkSize the RTCM stream chunk size.
        void writeRTCMStreamChunk(uint8_t *chunk, uint16_t chunkSize) noexcept;
    };
}