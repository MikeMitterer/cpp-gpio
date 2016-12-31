//
// Created by Mike Mitterer on 22.07.16.
//

#ifndef RASPIHELLOWORLD_GPIO_H
#define RASPIHELLOWORLD_GPIO_H

//#include <RF24/nRF24L01.h>
//#include <RF24/RF24.h>
#include <functional>

/*! was 1 - This means pin HIGH, true, 3.3volts on a pin. */
#undef HIGH
/*! was 0 - This means pin LOW, false, 0volts on a pin. */
#undef LOW

// RV24 definiert eigenes delay!
#undef delay

/**
 * Example GPIO.h file
 *
 * @defgroup GPIO GPIO Example
 *
 * See RF24_arch_config.h for additional information
 * @{
 */



namespace mm {

    namespace gpio {

        class Board {
        private:
            bool initialized = false;

        public:

            /// Necessary!!!!
            /// Returns true if it succeeds - otherwise it returns false
            bool init();

        virtual ~Board();

        private:

        };

        class Pin {
        public:
            enum class Direction {
                INPUT, OUTPUT, UNDEFINED
            };

            enum class InputState {
                /*! This means pin HIGH, true, 3.3volts on a pin. */
                        HIGH,
                /*! This means pin LOW, false, 0volts on a pin. */
                        LOW
            };

            enum class OutputState { ON, OFF};

        private:
            const uint8_t pin;
            Direction direction = Direction::UNDEFINED;
            std::function<void (Pin& pin)> closing = [] (Pin& pin) { printf("Closing function!\n"); };

        public:

            Pin(const uint8_t pinParam) : pin{pinParam} {
            }

            Pin(const uint8_t pinParam,std::function<void (Pin& pin)> closing) : pin{pinParam} {
                mode(direction);
                this->closing = closing;
            }

            ~Pin() {
                closing(*this);
            }

            const Direction& mode(const Direction& direction);

            InputState read();

            void write(const OutputState state);

            friend std::ostream &operator<<(std::ostream &os, const Pin &pin);
        };

        void delay(int8_t milliseconds);

        std::ostream &operator<<(std::ostream &os, const Pin::Direction& direction);
        std::ostream &operator<<(std::ostream &os, const Pin::OutputState& outputState);
    }
}

#endif //RASPIHELLOWORLD_GPIO_H
