# ELF File

## Introduction <a name="introduction"></a>

ELF is a format of file that's really common in the UNIX/LINUX environnement, it permits to split a binary between many parts and to describe the context of execution. It stored the binary code, the binary data, and others.

It's really usefull to work with ELF files because you can link them and have many advantages to use them because it's cross platform, it supports endiannesses.

## Table of contents <a name="table-of-contents"></a>

- [Introduction](#introduction)
- [Table of contents](#table-of-contents)
- [ELF categories](#elf-cat)

## ELF categories <a name="elf-cat"></a>

An ELF file has many categories, here is the list of them:

- [ELF header](#elf-header)
- Program Header table
- Text
- Rodata
- Data
- Section Header Table

### ELF header <a name="elf-header"></a>

The ELF header is describing if you must use 32 or 64 bit addresses. It contains 3 fields that are affected by the header settings and the offset of the other fields that follow them.

The ELF header is 52 or 64 bytes long depending of the 32 or 64 bits binaries

#### ELF header schema

```
+-------------+ <- 0x00
| Magic Bytes | 0x7F, 'E', 'L', 'F'. It's to define if the file is an ELF or not
+-------------+ <- 0x04
| Bin byte    | 1: 32 bits, 2: 64 bits
+-------------+ <- 0x05
| Endianness  | 1: little endian, 2: big endian
+-------------+ <- 0x06
| Version     | 1: original and current version of ELF (TODO: meaning ??)
+-------------+ <- 0x07
| Target OS   | many values... see here: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
+-------------+ <- 0x08
| ...         | Other.. Will discuss about it later
+-------------+
```