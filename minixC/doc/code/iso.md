# ISO Description

## Introduction <a name="introduction"></a>

This file contains the explanation of the JackOS iso file, with the schema of the sectors

## Table of Contents <a name="table-of-contents"></a>

- [Introduction](#introduction)
- [Table of Contents](#table-of-contents)
- [Schema](#schema)

## Schema <a name="schema"></a>

```
+-------------+ <- 0x00, (C, H, S) = (0, 0, 0)
| BOOT Loader |
+-------------+ <- 0x400, (C, H, S) = (0, 0, 3)
| Kernel Code |
+-------------+
```
