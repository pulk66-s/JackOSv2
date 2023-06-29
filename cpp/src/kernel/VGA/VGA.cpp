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

/**
 * @brief      Setup the VGA colors
 * a VGA color is a 8 bit number, the first 4 bits are the background color,
 * the last 4 bits are the foreground color.
 * We make it inline because it's a very simple function.
 * So the compiler will replace the function call with the function body.
 * @param[in]  fg    The foreground color
 * @param[in]  bg    The background color
 * @return     The VGA color
*/
inline VGA_entry_color VGA::colorEntry(enum VGA::color fg, enum VGA::color bg)
{
	return fg | bg << 4;
}

/**
 * @brief      Setup the VGA entry
 * a VGA entry is a 16 bit number, the first 8 bits are the character,
 * the last 8 bits are the color.
 * We make it inline because it's a very simple function.
 * So the compiler will replace the function call with the function body.
 * @param[in]  c      The character
 * @param[in]  color  The color
 * @return     The VGA entry
*/
inline VGA_entry VGA::vgaEntry(unsigned char c, VGA_entry_color color)
{
	return (VGA_entry)c | (VGA_entry)color << 8;
}

/**
 * @brief      Put a character on the VGA buffer
 * It print a char on the next available position.
 * @param[in]  c     The character
*/
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
