# Copyright (c) 2020 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

add_library(mbed-stm32u585vi INTERFACE)

target_sources(mbed-stm32u585vi
    INTERFACE
        PeripheralPins.c
)

target_include_directories(mbed-stm32u585vi
    INTERFACE
        .
)

target_link_libraries(mbed-stm32u585vi INTERFACE mbed-stm32u585xi)
