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
