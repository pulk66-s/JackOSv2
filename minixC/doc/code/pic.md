# PIC

## Introduction <a name="introduction"></a>

The 8259 PIC (Programmable Interrupt Controller) is a chip that is used to manage hardware interrupts. It is used in the IBM PC and compatibles. It has two main functions:

- It manages the interrupts from the programmable interrupt devices (PICs) on the motherboard and other devices.
- It provides an interrupt request line (IRQ) to the processor.

For now we will only use few functions of the PIC, everything can be see in the [Table of Contents](#table-of-contents).

## Table of contents <a name="table-of-contents"></a>

- [Introduction](#introduction)
- [Table of contents](#table-of-contents)
- [Disk](#disk)
  - [Read](#read)
  - [Wait until ready](#wait)
- [PIC port description](#pic-port-description)
  - [in 0x1F0](#inb-1F0)
  - [in 0x1F7](#inb-1F7)
  - [out 0x1F2](#outb-1F2)
  - [out 0x1F3](#outb-1F3)
  - [out 0x1F4](#outb-1F4)
  - [out 0x1F5](#outb-1F5)
  - [out 0x1F6](#outb-1F6)

## Disk <a name="disk"></a>

### Read <a name="read"></a>

### Wait until ready <a name="wait"></a>

To wait until the disk is ready we need to use the PIC port [`0x1F7`](#inb-1F7).

Here is the procedure for waiting until the disk has finished the last command:

- Receive the byte from the PIC at port `0x1F7` and apply the and mask `0xC0` (11000000) to it. While the result is not equal to `0x40` (01000000)

## PIC port description <a name="pic-port-description"></a>

## in 0x1F0 <a name="inb-1F0"></a>

TODO

### in 0x1F7 <a name="inb-1F7"></a>

Here is the description of the input port `0x1F7`:

| Bit | Description     | Bit | Description     |
| --- | --------------- | --- | --------------- |
| 0   | Error           | 4   | Seek complete   |
| 1   | Index           | 5   | Write fault     |
| 2   | Corrected data  | 6   | Ready           |
| 3   | Data request    | 7   | Busy            |

### out 0x1F2 <a name="outb-1F2"></a>

The port `0x1F2` is used to set the number of sectors to read/write. The number must be between 1 and 128.

### out 0x1F3 <a name="outb-1F3"></a>

The port `0x1F3` is used to set the bits 0-7 of the LBA (Logical Block Address).

### out 0x1F4 <a name="outb-1F4"></a>

The port `0x1F4` is used to set the bits 8-15 of the LBA (Logical Block Address).

### out 0x1F5 <a name="outb-1F5"></a>

The port `0x1F5` is used to set the bits 16-23 of the LBA (Logical Block Address).

### out 0x1F6 <a name="outb-1F6"></a>

The port `0x1F6` is used to set the bits 24-27 of the LBA (Logical Block Address).

### out 0x1F7 <a name="outb-1F7"></a>

The port `0x1F7` is used to send commands to the disk. Here is the list of commands:

| Command | Description             |
| ------- | ----------------------- |
| 0x20    | Read sectors with retry |
| Others  | Not used, we don't care |
