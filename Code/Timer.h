#pragma once

#include <iostream>
#include <thread>
#include <chrono>

namespace ZPR{
    class Timer {
        bool clear = false;

        public:
            void stopTimer(){
                this->clear = true;
            };
            template <typename Function>
        void setTimeout(Function function, int delay) {
            this->clear = false;
            std::thread t([=]() {
                if(this->clear) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                if(this->clear) return;
                function();
            });
            t.detach();
        };
            template <typename Function>
        void setInterval(Function function, int interval) {
            this->clear = false;
            std::thread t([=]() {
                while(true) {
                    if(this->clear) return;
                    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                    if(this->clear) return;
                    function();
                }
            });
            t.detach();
        };
            
          

    };
    

}
