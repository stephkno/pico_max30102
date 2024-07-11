#include "i2c.hpp"

i2c_bus::i2c_bus(i2c_inst_t * port, uint8_t addr, uint8_t sda, uint8_t scl) 
: _port(port), _addr(addr), _sda(sda), _scl(scl)
{
    // init _i2c with speed
    i2c_init(_port, 400 * 1000);

    // set _i2c pins
    gpio_set_function(_sda, GPIO_FUNC_I2C);
    gpio_set_function(_scl, GPIO_FUNC_I2C);

    // init internal _i2c pullups
    gpio_pull_up(_sda);
    gpio_pull_up(_scl);
    
    bi_decl(bi_2pins_with_func(_sda, _scl, GPIO_FUNC_I2C));
}

i2c_bus::~i2c_bus(){
    delete _port;
}

void i2c_bus::write_byte(uint8_t reg, uint8_t byte){

    uint8_t data[] = {reg, byte};
    int ret = i2c_write_blocking(_port, _addr, data, 2, false);
    
    if(ret<0){
        printf("Error writing to _i2c\n");
        return;
    }

}

uint8_t i2c_bus::read_byte(uint8_t reg){

    uint8_t byte = 0;

    int ret = i2c_write_blocking(_port, _addr, &reg, 1, true);
    if(ret<0){
        printf("Error writing to _i2c: ");
        switch(ret){
            case PICO_ERROR_GENERIC:{
                printf("address not acknowledged\n");
                break;
            }
            case PICO_ERROR_TIMEOUT:{
                printf("timeout\n");
                break;
            }
        }
        return 0;
    }
    
    ret = i2c_read_blocking(i2c0, _addr, &byte, 1, false);
    if(ret<0){
        printf("Error reading from _i2c: %d\n", ret);
        return 0;
    }
    
    return byte;
}

void i2c_bus::read_bytes(uint8_t reg, uint8_t nbytes, uint8_t * bytes){

    int ret = i2c_write_blocking(_port, _addr, &reg, 1, true);
    if(ret<0){
        printf("Error writing to _i2c: ");
        switch(ret){
            case PICO_ERROR_GENERIC:{
                printf("address not acknowledged\n");
                break;
            }
            case PICO_ERROR_TIMEOUT:{
                printf("timeout\n");
                break;
            }
        }
        return;
    }
    
    ret = i2c_read_blocking(i2c0, _addr, bytes, nbytes, false);
    if(ret<0){
        printf("Error reading from _i2c: %d\n", ret);
        return; 
    }
    
}

uint8_t i2c_bus::bitmask(uint8_t reg, uint8_t mask, uint8_t byte){

    uint8_t prev = 0;

    int ret = i2c_write_blocking(_port, _addr, &reg, 1, true);
    if(ret<0){
        printf("Error writing to _i2c: ");
        switch(ret){
            case PICO_ERROR_GENERIC:{
                printf("address not acknowledged\n");
                break;
            }
            case PICO_ERROR_TIMEOUT:{
                printf("timeout\n");
                break;
            }
        }
        return 0;
    }
    
    ret = i2c_read_blocking(i2c0, _addr, &prev, 1, false);
    if(ret<0){
        printf("Error reading from _i2c: %d\n", ret);
        return 0;
    }
    
    prev &= mask;
    prev |= byte;

    ret = i2c_write_blocking(_port, _addr, &prev, 1, false);
    if(ret<0){
        printf("Error writing to _i2c: ");
        switch(ret){
            case PICO_ERROR_GENERIC:{
                printf("address not acknowledged\n");
                break;
            }
            case PICO_ERROR_TIMEOUT:{
                printf("timeout\n");
                break;
            }
        }
        return 0;
    }
    
    return byte;
}
