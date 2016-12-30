//
// Created by Mike Mitterer on 23.10.16.
//

#include <iostream>
#include <thread>
#include "GPIO.h"

namespace mm {
    namespace gpio {

        std::ostream &operator<<(std::ostream &os, const Pin::Direction &direction) {
            std::string state;

            switch (direction) {
                case Pin::Direction::INPUT :
                    state = "input";
                    break;
                case Pin::Direction::OUTPUT :
                    state = "output";
                    break;
                default:
                    state = "undefined";
            }
            return os << state;
        }

        std::ostream &operator<<(std::ostream &os, const Pin::OutputState &outputState) {
            std::string state;

            switch (outputState) {
                case Pin::OutputState::ON :
                    state = "on";
                    break;
                case Pin::OutputState::OFF :
                    state = "off";
                    break;
            }
            return os << state;
        }

        std::ostream &operator<<(std::ostream &os, const Pin &pin) {
            return os << "Pin " << std::to_string(pin.pin);
        }

        void delay(int8_t milliseconds) {
            std::cout << "wait " << static_cast<int>(milliseconds) << "ms...." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        }

    }
}

