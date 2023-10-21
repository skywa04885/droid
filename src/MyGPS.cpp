#include "MyGPS.hpp"
#include "config.hpp"

namespace lacar::droid::firmware
{
    MyGPS MyGPS::s_Instance;

    MyGPS::MyGPS(void) noexcept : m_GPS(),
                                  m_Status(Status::Ok),
                                  m_LastUpdateMillis(0U),
                                  m_HDOP(0),
                                  m_PDOP(0)
    {
    }

    /// @brief performs all the setup for the GPS. 
    void MyGPS::setup(void) noexcept
    {
        if (!m_GPS.begin())
        {
            m_Status = Status::BeginFailed;
            return;
        }

        m_Status = Status::Ok;
    }

    /// @brief performs all the processing for the GPS.
    void MyGPS::loop(void) noexcept
    {
        if (m_Status != Status::Ok)
        {
            return;
        }

        const uint32_t currentMillis = millis();
        if (currentMillis - m_LastUpdateMillis < 10)
        {
            return;
        }

        m_HDOP = static_cast<float>(m_GPS.getHorizontalDOP()) / 100.0f;
        m_PDOP = static_cast<float>(m_GPS.getPDOP()) / 100.0f;
    }

    /// @brief writes the given RTCM stream chunk.
    /// @param chunk the RTCM stream chunk.
    /// @param chunkSize the RTCM stream chunk size.
    void MyGPS::writeRTCMStreamChunk(uint8_t *chunk, uint16_t chunkSize) noexcept
    {
        if (m_GPS.pushRawData(chunk, chunkSize)) return;
        m_Status = Status::PushRawDataFailed;
    }
}
