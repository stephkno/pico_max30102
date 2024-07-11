#include "i2c.hpp"

#define INTERRUPT_STATUS_REG_1 0x00
#define INTERRUPT_STATUS_REG_2 0x01
#define INTERRUPT_ENABLE_REG_1 0x02
#define INTERRUPT_ENABLE_REG_2 0x03

#define FIFO_WRITE_POINTER 0x04
#define FIFO_OVERFLOW_COUNTER 0x05
#define FIFO_READ_POINTER 0x06
#define FIFO_DATA_REGISTER 0x07

#define FIFO_CONFIG_REGISTER 0x08
#define MODE_CTRL_REGISTER 0x09
#define SPO2_CONFIG_REGISTER 0x0A
#define LED_PULSE_AMPLITUDE_REGISTER_1 0x0C
#define LED_PULSE_AMPLITUDE_REGISTER_2 0x0D

#define LED_MODE_CTRL_REGISTER_1 0x11
#define LED_MODE_CTRL_REGISTER_2 0x12

#define DIE_TEMP_INTEGER_REGISTER 0x1F
#define DIE_TEMP_FRACTION_REGISTER 0x20
#define DIE_TEMP_CONFIG_REGISTER 0x21

#define PART_REVISION_ID_REGISTER 0xFE
#define PART_ID_REGISTER 0xFF

class max30102{

    // initialize sensor
    uint8_t _addr = 0x57;
    i2c_inst_t * _port = i2c0;
    uint8_t _sda = 4;
    uint8_t _scl = 5;
    i2c_bus * _i2c;
    uint8_t _fifo_data[6] = {0};

public:

    uint32_t hr;
    uint32_t spo2;

    max30102();
    ~max30102();

    uint8_t read_part_id();
    void read_fifo();
    uint8_t read_fifo_read_ptr();
    double read_temperature();
    
};
