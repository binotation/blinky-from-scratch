# Blinky From Scratch
This is a learning project to understand:
1. The C start-up routine and linking in Arm Cortex-M devices
2. Accessing MCU peripheral registers by direct access

The device used was an STM32L432KC.

## Vector Table
- Arm Cortex-M4 requires a vector table at address 0x0000_0000 (Cortex-M4 Generic User Guide p.37)
- The first entry is the _Initial Stack Pointer Value_
- The second entry is the reset vector which points to the first subroutine to be excuted
- The vector table is a section defined in `startup_ARMCM4.S:71`
- The vector table's location in flash is given by `gcc.ld:50` - it is at the beginning of the .text section which sits in flash memory

## Stack and Heap
- The stack and heap sections are defined at the beginning of the startup routine `startup_ARMCM4.S:71`
- The stack grows into lower memory addresses and is at the end of RAM (`gcc.ld:86`)
- The heap grows into higher memory addresses and is next to the .bss section

## Reset Vector/Handler
- Copies data from flash to ram for the .data section (`startup_ARMCM4.S:139`) based on defined macro
- Zeroes memory in .bss section (`startup_ARMCM4.S:198`) based on defined macro
- Performs a branch with link to _start (entrypoint)

## Default handler
- Defines an infinite looping default handler for all exception handlers
