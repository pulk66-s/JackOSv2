#
# This program sign the boot sector with the right key
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

    magic_bytes = b'\x55\xAA'

    first_sector = boot_data[:510]
    first_sector += magic_bytes
    boot_data = first_sector + boot_data[512:]

    with open(boot_file, "wb") as f:
        f.write(boot_data)

if __name__ == "__main__":
    main()
