# 
# This file sign the boot sector with 0x55AA
# It checks if the file is too large and if not, it adds 0x00 until the 510th byte
# and then adds 0x55AA
# 

import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 sign.py <filename>")
        sys.exit(1)
    filename = sys.argv[1]
    l = 0
    with open(filename, "rb") as f:
        l = len(f.read())
        if l > 510:
            print("File too large")
            sys.exit(1)
    with open(filename, "ab") as f:
        f.write(b"\x00" * (510 - l))
        f.write(b"\x55\xAA")

if __name__ == "__main__":
    main()
