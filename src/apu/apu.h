#pragma once

#include <cstdint>

class APU {
    public:
        void set_nr50(uint8_t value);
        uint8_t get_nr50() const;
    
    private:
        uint8_t nr50 = 0;
};