#include <string>
#include <vector>
#include <cstdint>

class Memory {
    public:
        Memory(const std::string rom_path);
        uint8_t read(const uint8_t address) const;
        void write(const uint8_t address, uint8_t value);
    private:
        std::vector<uint8_t> rom_data;
};
