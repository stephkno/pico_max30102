cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(max30102)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

if (TARGET tinyusb_device)
# rest of your project
add_executable(max30102
	main.cpp
    i2c.cpp
    max30102.cpp
)

target_link_libraries(max30102 pico_stdlib hardware_i2c)


pico_enable_stdio_usb(max30102 1)
pico_enable_stdio_uart(max30102 0)
pico_add_extra_outputs(max30102)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()