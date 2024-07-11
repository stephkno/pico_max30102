#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

class i2c_bus{

    uint8_t _addr;
    uint8_t _sda;
    uint8_t _scl;
    i2c_inst_t * _port;

public:

    i2c_bus(i2c_inst_t * port, uint8_t addr, uint8_t sda, uint8_t scl);
    ~i2c_bus();

    void write_byte(uint8_t reg, uint8_t byte);
    uint8_t read_byte(uint8_t reg);
    void read_bytes(uint8_t reg, uint8_t nbytes, uint8_t * bytes);
    uint8_t bitmask(uint8_t reg, uint8_t mask, uint8_t byte);
};