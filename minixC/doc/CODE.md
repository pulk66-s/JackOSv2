# Code documentation

## Table of contents

- [Introduction](#introduction)
- [Makefile](#makefile)

## Introduction <a name="introduction"></a>

This document describes everything you need to know about the code in this repository.
It's splitted in many parts that are necessary to understand the code.

## Makefile <a name="makefile"></a>

The Makefile is used to build everything in this repository.
Here is the Makefile architecture

```
- /
    - Makefile
    - src/
        - Makefile
        - boot/
            - Makefrag
        - kernel/
            - Makefrag
    - mk/
        config.mk
```

You have two types of files:
- Makefile: It's the starting point of your compilation
- Makefrag: It's utility files that are included in the Makefile

The `mk/` folder contains all the configurations files.

---
### Current commands

#### ROOT folder

- `make`: default cmd: Build everything
- `make build_everything`: Clean everything

#### SRC folder

- `make`: default rule: Build all the OS
- `make os_build`: Build all the OS
