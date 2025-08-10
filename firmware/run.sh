#!/bin/env bash

TOOLCHAIN_FILE="./cmake/gcc-arm-none-eabi.cmake"

helpFunction() {
  echo ""
  echo "Usage: $0 <command>"
  echo -e "\tcommand: Tells the script what to do. Options:"
  echo -e "\t\tflash: Builds and flashes the board"
  echo -e "\t\tbuild: Builds the project"
  echo -e "\t\tserial: Uses tio to connect to the device"
  echo -e "\t\thelp:  Shows this prompt"
}

if [[ $1 == "help" || -z $1 ]]; then
    helpFunction
elif [[ $1 == "flash" ]]; then
    (mkdir -p bin)
    (cmake -DCMAKE_TOOLCHAIN_FILE=./cmake/gcc-arm-none-eabi.cmake -S . -B bin)
    (cd bin; cmake --build .)
    (cp bin/compile_commands.json .)
    (cd bin; openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "program kontroller.elf verify reset exit")
elif [[ $1 == "build" ]]; then
    (mkdir -p bin)
    (cmake -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" -S . -B bin)
    (cd bin; cmake --build .)
    (cp bin/compile_commands.json .)
elif [[ $1 == "serial" ]]; then
    (tio -b 115200 /dev/ttyACM0)
fi
