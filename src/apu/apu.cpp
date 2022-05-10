#include "apu.h"

void APU::set_audio_device(SDL_AudioDeviceID id) {
    audio_device = id;
}

void APU::run(unsigned cycles) {
    for (unsigned i = 0; i < cycles; i++) {
        tick();
    }
}

void APU::tick() {

}

void APU::set_nr50(uint8_t value) {
    nr50 = value;
}

uint8_t APU::get_nr50() const {
    return nr50;
}