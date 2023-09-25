#
# This program fill the file with 0x00 until it reach the size of a sector
#

import sys

def check_args():
    if len(sys.argv) != 2:
        print("Usage: sign.py <bootsector.bin>")
        sys.exit(1)
    boot_file = sys.argv[1]
    try:
        with open(boot_file, "rb") as f:
            pass
    except FileNotFoundError:
        print("File not found: {}".format(boot_file))
        sys.exit(1)

def main():
    check_args()
    boot_file = sys.argv[1]
    boot_data = None

    with open(boot_file, "rb") as f:
        boot_data = f.read()

    boot_size = len(boot_data)
    size_to_fill = 512 - boot_size % 512
    boot_data += b'\x00' * size_to_fill

    with open(boot_file, "wb") as f:
        f.write(boot_data)

if __name__ == "__main__":
    main()