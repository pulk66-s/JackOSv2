void kernel_main() {
    unsigned char *vga = (unsigned char *) 0xb8000;
    vga[0] = 'H';
    vga[1] = 0x0f;
}