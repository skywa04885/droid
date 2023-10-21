#include "config.hpp"
#include "MyDisplay.hpp"
#include "MyAccelerometer.hpp"
#include "MyCom.hpp"
#include "MyGPS.hpp"

namespace lacar::droid::firmware
{
    static const char CROSS_GLYPH[8] = {
        0x0,
        0x1b,
        0xe,
        0x4,
        0xe,
        0x1b,
        0x0,
    };

    static const char CHECKMARK_GLYPH[8] = {
        0x0,
        0x1,
        0x3,
        0x16,
        0x1c,
        0x8,
        0x0,
    };

    static const char ACCELEROMETER_GLYPH[8] = {
        0b10000,
        0b10000,
        0b10000,
        0b10011,
        0b11100,
        0b10000,
        0b01100,
        0b00011,
    };

    static const char RADIO_GLYPH[8] = {
        0b01110,
        0b10001,
        0b10101,
        0b10001,
        0b00100,
        0b00100,
        0b00100,
        0b00100,
    };

    static const char LOCATION_GLYPH[8] = {
        0b01110,
        0b10001,
        0b10101,
        0b10101,
        0b01010,
        0b01010,
        0b00100,
        0b00100,
    };

    MyDisplay MyDisplay::s_Instance;

    MyDisplay::MyDisplay() : m_Rows(2U), m_Cols(16U),
                             m_LiquidCrystal(0x27, m_Rows, m_Cols),
                             m_Bank(std::nullopt),
                             m_LastBankSwitchMillis(0UL)
    {
    }

    void MyDisplay::entryRadioBank(void) noexcept
    {
        m_LiquidCrystal.clear();

        m_LiquidCrystal.setCursor(0U, 0U);
        m_LiquidCrystal.printf("CH:%02u", LACAR_DROID_FIRMWARE__RF24__CHANNEL);
    }

    void MyDisplay::doRadioBank(void) noexcept
    {
    }

    void MyDisplay::exitRadioBank(void) noexcept
    {
    }

    void MyDisplay::entrySystemBank(void) noexcept
    {
        m_LiquidCrystal.clear();

        m_LiquidCrystal.createChar(0U, CHECKMARK_GLYPH);
        m_LiquidCrystal.createChar(1U, CROSS_GLYPH);
        m_LiquidCrystal.createChar(2U, ACCELEROMETER_GLYPH);
        m_LiquidCrystal.createChar(3U, RADIO_GLYPH);
        m_LiquidCrystal.createChar(4U, LOCATION_GLYPH);

        m_LiquidCrystal.setCursor(0U, 0U);
        m_LiquidCrystal.write(2U);
        m_LiquidCrystal.print('|');
        m_LiquidCrystal.write(3U);
        m_LiquidCrystal.print('|');
        m_LiquidCrystal.write(4U);

        m_LiquidCrystal.setCursor(0U, 1U);
        m_LiquidCrystal.write(MyAccelerometer::getInstance().getStatus() == 0U ? 0U : 1U);
        m_LiquidCrystal.print('|');
        m_LiquidCrystal.write(MyCom::getInstance().getStatus() == 0U ? 0U : 1U);
        m_LiquidCrystal.print('|');
        m_LiquidCrystal.write(MyGPS::getInstance().getStatus() == MyGPS::Status::Ok ? 0U : 1U);
    }

    void MyDisplay::doSystemBank(void) noexcept
    {
    }

    void MyDisplay::exitSystemBank(void) noexcept
    {
    }

    void MyDisplay::entryGpsBank(void) noexcept
    {
        m_LiquidCrystal.clear();

        m_LiquidCrystal.setCursor(0U, 0U);
        m_LiquidCrystal.printf("H:%02.01f", MyGPS::getInstance().getHDOP());
    }

    void MyDisplay::doGpsBank(void) noexcept
    {
    }

    void MyDisplay::exitGpsBank(void) noexcept
    {
    }

    void MyDisplay::entryBank(void) noexcept
    {
        if (!m_Bank)
        {
            return;
        }

        switch (*m_Bank)
        {
        case Bank::Radio:
            entryRadioBank();
            break;
        case Bank::System:
            entrySystemBank();
            break;
        case Bank::GPS:
            entryGpsBank();
            break;
        }
    }

    void MyDisplay::doBank(void) noexcept
    {
        if (!m_Bank)
        {
            return;
        }

        switch (*m_Bank)
        {
        case Bank::Radio:
            doRadioBank();
            break;
        case Bank::System:
            doSystemBank();
            break;
        case Bank::GPS:
            doGpsBank();
            break;
        }
    }

    void MyDisplay::exitBank(void) noexcept
    {
        if (!m_Bank)
        {
            return;
        }

        switch (*m_Bank)
        {
        case Bank::Radio:
            exitRadioBank();
            break;
        case Bank::System:
            exitSystemBank();
            break;
        case Bank::GPS:
            exitGpsBank();
            break;
        }
    }

    /// @brief Updates the bank indicator.
    void MyDisplay::updateBankIndicator(void) noexcept
    {
        m_LiquidCrystal.setCursor(m_Cols - 1U, 0U);

        if (m_Bank)
        {
            m_LiquidCrystal.printf(F("%d"), *m_Bank);
        }
        else
        {
            m_LiquidCrystal.printf(F("-"));
        }
    }

    void MyDisplay::begin(void) noexcept
    {
        m_LiquidCrystal.init();
        m_LiquidCrystal.backlight();

        transition(Bank::Radio);
    }

    /// @brief Transitions the state machine to the given bank.
    /// @param bank The bank to transition to.
    void MyDisplay::transition(Bank bank) noexcept
    {
        exitBank();

        m_Bank = bank;

        entryBank();

        updateBankIndicator();
    }

    void MyDisplay::updatePerformBankSwitch(void) noexcept
    {
        const uint32_t currentMillis = millis();
        if (currentMillis - m_LastBankSwitchMillis < 2000)
        {
            return;
        }

        if (!m_Bank)
        {
            return;
        }

        switch (*m_Bank)
        {
        case Bank::GPS:
            transition(Bank::System);
            break;
        case Bank::System:
            transition(Bank::Radio);
            break;
        case Bank::Radio:
            transition(Bank::GPS);
            break;
        }

        m_LastBankSwitchMillis = currentMillis;
    }

    void MyDisplay::update(void) noexcept
    {
        updatePerformBankSwitch();

        doBank();
    }
}
