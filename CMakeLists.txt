cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(custom_charlieplex C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(charlieplex charlieplex.c)

# pull in common dependencies
target_link_libraries(charlieplex pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(charlieplex 1)
pico_enable_stdio_uart(charlieplex 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(charlieplex)

# add url via pico_set_program_url