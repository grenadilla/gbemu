#include <iostream>
#include <gflags/gflags.h>

#include "gameboy.h"

// Define command line arguments using gflags
DEFINE_bool(debug, false, "Run with command line debugger");
DEFINE_bool(graphics, true, "Run with graphics");
DEFINE_bool(tilemap, false, "Run with tilemap display. This will have a significant performance impact!");
DEFINE_bool(sound, true, "Run with sound");

DEFINE_string(rom, "", "Path to gameboy ROM to run");

int main(int argc, char** argv) {
    gflags::SetUsageMessage("A gameboy emulator");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_rom == "") {
        gflags::ShowUsageWithFlags(argv[0]);
    } else {       
        Gameboy gb(FLAGS_rom);
        gb.run(FLAGS_debug, FLAGS_graphics, FLAGS_tilemap, FLAGS_sound);
    }
}
