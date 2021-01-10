/**
 * timer.hpp
 * Header and implementations of Timer class.
 */

#pragma once

#include <iostream>
#include <thread>
#include <chrono>

namespace zpr{

    /**
     Class responsible for making new thread for vehicles simulation.
     */
    class Timer {
        bool clear_ = false;

    public:
        /**
         * Method which stops the "timer" - deletes thread.
         */
        void stopTimer(){
            this->clear_ = true;
        };
        /**
         * Template method which allows to execute function after certain delay.
         * @param function - Function which will be executed.
         * @param delay - Time after which function will be executed.
         */
        template <typename Function>
        void setTimeout(Function function, int delay) {
            this->clear_ = false;
            std::thread t([=]() {
                if(this->clear_) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                if(this->clear_) return;
                function();
                });
            t.detach();
        };
        /**
         * Template method which allows to execute function after certain delay.
         * @param function - Function which will be executed.
         * @param interval - Interval of time after function is executed.
         */
        template <typename Function>
        void setInterval(Function function, int interval) {
            this->clear_ = false;
            std::thread t([=]() {
                while(true) {
                    if(this->clear_) return;
                    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                    if(this->clear_) return;
                    function();
                }
            });
            t.detach();
        };
    };
}
