#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Memory maps
unsigned char __at(0x6000) input0;
unsigned char __at(0x7000) joystick[24];
unsigned char __at(0x7100) analog[24];
unsigned char __at(0x8000) chram[2048];
unsigned char __at(0x8800) colram[2048];

// Character map
const unsigned char chram_cols = 64;
const unsigned char chram_rows = 32;
unsigned int chram_size;

unsigned char hsync;
unsigned char hsync_last;
unsigned char vsync;
unsigned char vsync_last;

void clear_chars()
{
	for (unsigned int p = 0; p < chram_size; p++)
	{
		chram[p] = 0;
	}
}

void write_string(const char *string, char color, unsigned int x, unsigned int y)
{
	unsigned int p = (y * chram_cols) + x;
	unsigned char l = strlen(string);
	for (char c = 0; c < l; c++)
	{
		chram[p] = string[c];
		colram[p] = color;
		p++;
	}
}

void write_char(unsigned char c, char color, unsigned int x, unsigned int y)
{
	unsigned int p = (y * chram_cols) + x;
	chram[p] = c;
	colram[p] = color;
}

void page_border(char color)
{
	write_char(128, color, 0, 0);
	write_char(130, color, 39, 0);
	write_char(133, color, 0, 29);
	write_char(132, color, 39, 29);
	for (char x = 1; x < 39; x++)
	{
		write_char(129, color, x, 0);
		write_char(129, color, x, 29);
	}
	for (char y = 1; y < 29; y++)
	{
		write_char(131, color, 0, y);
		write_char(131, color, 39, y);
	}
}

void page_inputs()
{
	clear_chars();
	page_border(0b00000111);
	write_string("UDLRABCXYZLRSs", 0xFF, 7, 3);
	write_string("AX  AY", 0xFF, 25, 3);

	char label[5];
	for (unsigned char j = 0; j < 6; j++)
	{
		sprintf(label, "JOY%d", j + 1);
		write_string(label, 0xFF - (j*2), 2, 4 + j);
	}
}

char asc_0 = 48;
char asc_1 = 49;

void main()
{
	chram_size = chram_cols * chram_rows;
	char color = 0xAB;
	page_inputs();

	while (1)
	{
		hsync = input0 & 0x80;
		vsync = input0 & 0x40;

		// if(hsync && !hsync_last){
		// }

		if (vsync && !vsync_last)
		{
			color++;
			write_string("--- MiSTer Input Tester ---", color, 6, 1);
			int y = 4;
			for (char b = 0; b < 2; b++)
			{
				char m = 0b00000001;
				for (char i = 0; i < 8; i++)
				{
					char x = 7 + i + (b * 8);
					for (char j = 0; j < 6; j++)
					{
						write_char((joystick[(b * 8) + (j * 32)] & m) ? asc_1 : asc_0, 0xFF, x, 4 + j);
					}
					m <<= 1;
				}
			}

			y = 4;

			char m = 0b00000001;
			char str1[4];
			char str2[4];
			for (char j = 0; j < 6; j++)
			{
				signed char jx = analog[(j * 16)];
				signed char jy = analog[(j * 16) + 8];
				
				sprintf(str1, "%4d", jx);
				write_string(str1, 0xFF, 23, y + j);
				sprintf(str2, "%-4d", jy);
				write_string(str2, 0xFF, 28, y + j);
				m <<= 1;
			}


// ADD THE PADDLES AND SPINNERS HERE

		}
		hsync_last = hsync;
		vsync_last = vsync;
	}
}