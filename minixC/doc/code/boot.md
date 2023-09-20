# Boot explanation

## Introduction <a name="introduction"></a>

This file explains the theory and the implementations behind the bootloader.

## Table of contents <a name="table-of-contents"></a>

- [Introduction](#introduction)
- [Table of contents](#table-of-contents)
- [Theory](#theory)
    - [Boot sequence](#boot-sequence)
    - [The boot sector](#boot-sector)
    - [Bios code](#bios-code)
- [Code implementation](#code)

## Theory <a name="theory"></a>

The bootloader is the first program that is executed by the CPU. It's starting the OS in 16 bits mode and then switch to 32 bits mode. It's also loading the kernel in memory and then jump to it.

---
### Boot sequence <a name="boot-sequence"></a>

The boot sequence is the following:
- The CPU is starting in 16 bits mode
- Cleaning all the [BIOS shit](#bios-code)
- [Enable A20](#enable-a20)

---
### The boot sector <a name="boot-sector"></a>

A sector is a part of a disk. A sector is 512 bytes long. The boot sector is the first sector of a disk. It's the first sector that is loaded by the BIOS. The boot sector is 512 bytes long. The first 446 bytes are the bootloader. The last 2 bytes are the magic number. The magic number is `0xAA55`. The magic number is used by the BIOS to check if the sector is a boot sector.

---
### Bios code <a name="bios-code"></a>

The bootloader is run right after the bios routine, the bios can do whatever he wants without cleaning everything, so we need to pay attention to some unwanted values in the registers, the interrupt table, the direction flag, etc...

You must use thoses lines right after the bootloader to clean everything:
```asm
    cli
    cld

    xorw ax, ax
    movw ds, ax
    movw es, ax
    movw ss, ax
    movw sp, 0x7c00
```

### Enable A20 <a name="enable-a20"></a>

A20 is something from old computers, when the IBM-AT (Intel 286) was introduced, it was
able to access up to 16 MB of memory, (the 8086 was only doing 1 MB). The 8086
chip was only able to access 1 MB of memory, when it's trying to access more than 1 MB, it's wrapping around to zero. Some developpers decided to use this as a functionnalities
to access more memories instead of using the proper address. In order to support this era
this wraparound has been emlated. This was by achived by setting the default A20 line to zero.
Later the A20 pin control was added to disable this wraparound.

To enable the A20 in a clean way we need to test and set the A20 line from the most
safe way to the most unsafe way.

#### 1. Test the A20 line

The first thing to do is to test the A20 line, to do this we need to see if the memory
is wraping arround to zero. To do this we need to set some data in a memory address
greater than 1 MB and then try to read it from an address lower than 1 MB. If the data
is the same then the A20 line is not set, if the data is different then the A20 line is set.

#### 2. Test the BIOS function gate

The BIOS is giving an interrupt to enable the A20 line, we can use this interrupt to
enable the A20 line. To do this we need to call the interrupt 0x15 with the function
0x2403. If the A20 line is not set then the interrupt will return with the carry flag
set to 1, if the A20 line is set then the interrupt will return with the carry flag
set to 0.

#### 3. Test the keyboard controller

#### 4. Fast A20 gate

On most newer computers starting with IBM PS/2, the fast A20 gate is available. This
method is the fastest way to enable the A20 line. To do this we need to do three
simples steps:
```asm
in $0x92, %al
or $0x02, %al
out %al, $0x92
```

## Code implementation <a name="code"></a>

The bootloader is written in C and assembly, the source code is in the `src/boot` directory.

Here is the actual file architecture of the bootloader:
```
- src/boot
    - boot16.S
    - main.c
    - sign.py
```
