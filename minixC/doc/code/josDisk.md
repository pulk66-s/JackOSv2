# JOS Disk

Here is the explanation of the JOS disk image structure. You will find the location of everything in the disk image built by the Makefiles.

## Disk image structure

```
+------------------+ <- 0x00000000
|      Booting     | 
+------------------+ <- 0x00000200
|      Kernel      |
+------------------+ <- 0x????
```
