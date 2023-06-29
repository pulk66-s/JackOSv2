#include "kernel/VGA/VGA.hpp"

VGA::VGA(void)
{
	this->row = 0;
	this->col = 0;
	this->buffer = (VGA_buffer)VGA_BUFFER;
	this->color = this->colorEntry(
		VGA::color::LIGHT_GREY,
		VGA::color::BLACK
	);
}

VGA_entry_color VGA::colorEntry(enum VGA::color fg, enum VGA::color bg)
{
	return fg | bg << 4;
}

VGA_entry VGA::vgaEntry(unsigned char c, VGA_entry_color color)
{
	return (VGA_entry)c | (VGA_entry)color << 8;
}

void VGA::putc(unsigned char c)
{
	if (c == '\n') {
		this->row++;
		this->col = 0;
		return;
	}

	size_t index = this->row * VGA_WIDTH + this->col;

	this->buffer[index] = this->vgaEntry(c, this->color);
	this->col++;
}
