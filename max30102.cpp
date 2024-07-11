#include "max30102.hpp"

// initialize sensor config
max30102::max30102(){

    // init _i2c
    _i2c = new i2c_bus(_port, _addr, _sda, _scl);

    // init max30102
    // Set to SpO2 mode
    _i2c->write_byte(MODE_CTRL_REGISTER, 0x03);

    // Set LED amplitude
    _i2c->write_byte(LED_PULSE_AMPLITUDE_REGISTER_2, 0x1F);

    // Set LED pulse width 411us
    _i2c->write_byte(SPO2_CONFIG_REGISTER, 0x73);

    // Set fifo rollover bit
    _i2c->write_byte(FIFO_CONFIG_REGISTER, 0x10);

    // clear fifo registers
    _i2c->write_byte(FIFO_WRITE_POINTER, 0x0);
    _i2c->write_byte(FIFO_READ_POINTER, 0x0);
    _i2c->write_byte(FIFO_DATA_REGISTER, 0x0);
}

max30102::~max30102(){
    delete _i2c;
}

uint8_t max30102::read_part_id(){
    return _i2c->read_byte(PART_ID_REGISTER);
}

void max30102::read_fifo(){
    // read data from fifo data register
    _i2c->read_bytes(FIFO_DATA_REGISTER, 6, _fifo_data);

    // convert data bytes to 32bit data
    hr = (_fifo_data[0]<<16) | (_fifo_data[1]<<8) | _fifo_data[2];
    spo2 = (_fifo_data[3]<<16) | (_fifo_data[4]<<8) | _fifo_data[5];
}

uint8_t max30102::read_fifo_read_ptr(){
    // read data from fifo data register
    return  _i2c->read_byte(FIFO_READ_POINTER);
}

double max30102::read_temperature(){
    // set die temp read bit
    _i2c->write_byte(DIE_TEMP_CONFIG_REGISTER, 0x01);
    // get temp integer
    uint8_t t_int = _i2c->read_byte(DIE_TEMP_INTEGER_REGISTER);
    // get temp fraction
    uint8_t t_frac = _i2c->read_byte(DIE_TEMP_FRACTION_REGISTER);
    // print temp+frac to double
    return t_int + t_frac*0.0625;
}
