ENTRY(reset_handler)

MEMORY {
    flash(rx) : ORIGIN = 0x08000000, LENGTH = 256K
    sram(rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

/* The base address of the stack, reminder that the stack grows downwards */
_estack = ORIGIN(sram) + LENGTH(sram);

SECTIONS {
    .vector_table : {
        . = ALIGN(8);
        KEEP(*(.vector_table))
        . = ALIGN(8);
    } > flash

    .text : {
        . = ALIGN(8);
        *(.text)
        *(.text*)
        . = ALIGN(8);
    } > flash

    .rodata : {
        . = ALIGN(8);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(8);
    } > flash

    _sidata = LOADADDR(.data);
    .data : {
        . = ALIGN(8);
        _sdata = .;
        *(.data)
        *(.data*)
        FILL(0xAB)
        . += 1;
        FILL(0xCD)
        . += 1;
        FILL(0xEF)
        . += 1;
        FILL(0x00)
        . = ALIGN(8);
        _edata = .;
    } > sram AT> flash

    .bss : {
        . = ALIGN(8);
        _sbss = .;
        *(.bss)
        *(.bss*)
        FILL(0xFF)
        . += 8;
        . = ALIGN(8);
        _ebss = .;
    } > sram
}
