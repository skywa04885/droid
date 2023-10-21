#include "MyCom.hpp"
#include "config.hpp"
#include "MyGPS.hpp"

namespace lacar::droid::firmware
{
    MyCom MyCom::s_Instance;

    MyCom::MyCom(void) noexcept : m_RF24(LACAR_DROID_FIRMWARE__RF24__CE, LACAR_DROID_FIRMWARE__RF24__CS),
                                  m_RF24Network(m_RF24),
                                  m_Status(255U)
    {
    }

    void MyCom::setup(void) noexcept
    {
        if (!m_RF24.begin())
        {
            m_Status = 1U;
            return;
        }

        if (!m_RF24.setDataRate(LACAR_DROID_FIRMWARE__RF24__DATA_RATE))
        {
            m_Status = 2U;
            return;
        }

        m_RF24.setPALevel(LACAR_DROID_FIRMWARE__RF24__PA_LAVEL);
        m_RF24.setChannel(LACAR_DROID_FIRMWARE__RF24__CHANNEL);

        m_RF24Network.begin(LACAR_DROID_FIRMWARE__RF24__ADDR);

        m_Status = 0U;
    }

    void MyCom::loop(void) noexcept
    {
        if (m_Status != 0U)
        {
            return;
        }

        m_RF24Network.update();

        while (m_RF24Network.available())
        {
            RF24NetworkHeader header;
            uint8_t message[256];

            // Reads the message from the network.
            const uint16_t messageSize = m_RF24Network.read(header, message,
                                                            sizeof(message));

            // Calls the appropriate callback based on the message type.
            switch (header.type)
            {
            case static_cast<uint8_t>(PacketType::RTCMStreamChunk):
                MyGPS::getInstance().writeRTCMStreamChunk(message, messageSize);
                break;
            default:
                break;
            }
        }
    }
}