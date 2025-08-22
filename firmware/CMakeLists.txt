cmake_minimum_required(VERSION 3.20)
project(kontroller C ASM)

set(CMAKE_C_STANDARD 11)

# Select the tools we will use to compile our program
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Required as we use a cross-compiling toolchain that cannot link
# without a custom link script
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Generate the compile_commands.json file that is used by the LSP
# in editors such as VSCode and VIM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set required options for cortex m4
set(MCPU cortex-m4)
add_compile_options(-mcpu=${MCPU} -mthumb)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
# Compile with debug symbols
add_compile_options(-ggdb)

# Add our C and assembly files
file(GLOB_RECURSE SOURCES
    "src/*.*"
    "hal/src/*.*"
    "${CMAKE_SOURCE_DIR}/startup.s"
)

# Set the linker script to use
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Linker.ld)

# Select the linker script and make sure we don't use the system startup files
# and libraries for linking
add_link_options(-T ${LINKER_SCRIPT} -nostdlib)

include_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/hal/inc)
# Create our executable
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

# Copy compile_commands.json to our root directory
file(COPY
    ${CMAKE_SOURCE_DIR}/build/compile_commands.json
    DESTINATION ${CMAKE_SOURCE_DIR}
)
