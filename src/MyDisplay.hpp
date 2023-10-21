#pragma once

#include <optional>
#include <LiquidCrystal_I2C.h>

namespace lacar::droid::firmware
{
    class MyDisplay
    {
    public:
        enum class Bank : uint8_t
        {
            Radio = 0,
            System = 1,
            GPS = 2,
        };

    private:
        static MyDisplay s_Instance;

    public:
        static inline MyDisplay &getInstance(void) noexcept
        {
            return s_Instance;
        }

    private:
        uint8_t m_Rows, m_Cols;
        LiquidCrystal_I2C m_LiquidCrystal;
        std::optional<Bank> m_Bank;
        uint32_t m_LastBankSwitchMillis;

    public:
        MyDisplay();

    private:
        void entryRadioBank(void) noexcept;

        void doRadioBank(void) noexcept;

        void exitRadioBank(void) noexcept;

        void entrySystemBank(void) noexcept;

        void doSystemBank(void) noexcept;

        void exitSystemBank(void) noexcept;

        void entryGpsBank(void) noexcept;
        
        void doGpsBank(void) noexcept;

        void exitGpsBank(void) noexcept;

        void entryBank(void) noexcept;

        void doBank(void) noexcept;

        void exitBank(void) noexcept;

        /// @brief Updates the bank indicator.
        void updateBankIndicator(void) noexcept;

    public:
        /// @brief Transitions the state machine to the given bank.
        /// @param bank The bank to transition to.
        void transition(Bank bank) noexcept;

        void begin(void) noexcept;

        void updatePerformBankSwitch(void) noexcept;

        void update(void) noexcept;
    };
}