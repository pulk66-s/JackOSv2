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

    if len(boot_data) > 510:
        print("Boot sector is too long")
        sys.exit(1)

    magic_bytes = b'\x55\xAA'

    with open(boot_file, "ab") as f:
        f.write(b"\x00" * (510 - len(boot_data)))
        f.write(magic_bytes)

if __name__ == "__main__":
    main()
