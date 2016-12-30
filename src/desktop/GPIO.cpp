//
// Created by Mike Mitterer on 21.10.16.
//

// Der PC-Teil des GPIO-Tests

#include <chrono>
#include <thread>
#include <iostream>
#include "GPIO.h"

namespace mm {
    namespace gpio {

        bool Board::init() {
            if(!initialized) {
                initialized = true;
                std::cout << "Board initialized!" << std::endl;
            }
            return initialized;
        }

        Board::~Board() {
            std::cout << "Board destructed!" << std::endl;
        }

        const Pin::Direction& Pin::mode(const Pin::Direction &direction) {
            if(this->direction != direction) {
                this->direction = direction;
                std::cout << "Direction for " << *this << " changed to: " << direction << std::endl;
            }

            return this->direction;
        }


        void Pin::write(const Pin::OutputState state) {
            mode(Direction::OUTPUT);
            std::cout << *this << " set to " << state << std::endl;
        }
    }
}