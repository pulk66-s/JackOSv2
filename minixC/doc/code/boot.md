# Boot explanation

## Introduction <a name="introduction"></a>

This file explains the theory and the implementations behind the bootloader.

## Table of contents <a name="table-of-contents"></a>

- [Introduction](#introduction)
- [Table of contents](#table-of-contents)
- [Theory](#theory)
    - [Boot sequence](#boot-sequence)
    - [The boot sector](#boot-sector)
- [Code implementation](#code)

## Theory <a name="theory"></a>

The bootloader is the first program that is executed by the CPU. It's starting the OS in 16 bits mode and then switch to 32 bits mode. It's also loading the kernel in memory and then jump to it.

---
### Boot sequence <a name="boot-sequence"></a>

The boot sequence is the following:
- The CPU is starting in 16 bits mode
- The BIOS is loading the bootloader in memory
- The bootloader is starting in 16 bits mode
- The bootloader is switching to 32 bits mode
- The bootloader is loading the kernel in memory
- The bootloader is jumping to the kernel

---
### The boot sector <a name="boot-sector"></a>

A sector is a part of a disk. A sector is 512 bytes long. The boot sector is the first sector of a disk. It's the first sector that is loaded by the BIOS. The boot sector is 512 bytes long. The first 446 bytes are the bootloader. The last 2 bytes are the magic number. The magic number is `0xAA55`. The magic number is used by the BIOS to check if the sector is a boot sector.

## Code implementation <a name="code"></a>

The bootloader is written in C and assembly, the source code is in the `src/boot` directory.

Here is the actual file architecture of the bootloader:
```
- src/boot
    - boot16.S
    - main.c
    - sign.py
```
