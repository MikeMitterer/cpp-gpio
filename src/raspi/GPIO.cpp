//
// Created by Mike Mitterer on 21.10.16.
//

#include <RF24/nRF24L01.h>
#include <RF24/RF24.h>
#include <functional>
#include <iostream>
#include <thread>
#include "GPIO.h"

// Der ARM-Teil des GPIO-Tests

namespace mm {
    namespace gpio {

        void delay(int8_t  milliseconds) {
            std::cout << "wait " << milliseconds << "ms..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        }

        bool Board::init() {
            if(!initialized) {
                initialized = (bcm2835_init() == 1);
                std::cout << "Board initialized!" << std::endl;
            }
            return initialized;
        }


        Board::~Board() {
            bcm2835_close();
            std::cout << "Board destructed!" << std::endl;
        }

        const Pin::Direction& Pin::mode(const Pin::Direction &direction) {
            if(this->direction != direction) {
                this->direction = direction;

                if(direction == Direction::INPUT) {
                    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
                } else {
                    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
                }

                std::cout << "Direction for " << *this << " changed to: " << direction << std::endl;
            }

            return this->direction;
        }

        Pin::InputState Pin::read() {
            if(direction != Direction::INPUT) {
                direction = mode(Direction::INPUT);
            }
            return bcm2835_gpio_lev(pin) == 0 ? Pin::InputState::LOW : Pin::InputState::HIGH;
        }

        void Pin::write(const Pin::OutputState state) {
            mode(Direction::OUTPUT);
            bcm2835_gpio_write(pin, (uint8_t) (state == OutputState::ON ? 1 : 0));
            std::cout << *this << " set to " << state << std::endl;
        }


    }
}