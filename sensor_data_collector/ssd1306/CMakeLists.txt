# CMakeLists.txt for SSD1306 library

# Create a library target for the SSD1306 display driver
add_library(ssd1306 STATIC
    ssd1306.c
)

# Include the Pico SDK hardware_i2c dependency
target_link_libraries(ssd1306
    pico_stdlib
    hardware_i2c
)

# Make the header file available to anything that links against this library
target_include_directories(ssd1306 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)