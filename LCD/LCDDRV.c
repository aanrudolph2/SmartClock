#include "../LCD/LCDDRV.h"

#define RS		PD4
#define E		PD5
#define CS		PD6
#define RES		PD7

#define LOW		0
#define HIGH	1

/* INTERNAL USE ONLY */

void command(uint8_t cmd)
{
	PORTD &= ~(1 << CS);
	PORTD &= ~(1 << RS);

	// Write high byte

	PORTD |= (1 << E);
	PORTD |= cmd >> 4;
	PORTD &= ~(1 << E);

	PORTD &= ~(0x0F);

	// Write low byte

	PORTD |= (1 << E);
	PORTD |= cmd & 0x0F;
	PORTD &= ~(1 << E);

	PORTD &= ~(0x0F);

	PORTD |= (1 << CS);

}
void data(uint8_t data)
{
	PORTD &= ~(1 << CS);
	PORTD |= (1 << RS);

	// Write high byte

	PORTD |= (1 << E);
	PORTD |= ((data >> 4) & 0x0F);
	PORTD &= ~(1 << E);

	PORTD &= ~(0x0F);

	// Write low byte

	PORTD |= (1 << E);
	PORTD |= (data & 0x0F);
	PORTD &= ~(1 << E);

	PORTD &= ~(0x0F);

	PORTD |= (1 << CS);
}

void Str(uint8_t * buf)
{
	int i = 0;
	while(buf[i] != 0)
	{
		data(buf[i]);
		i ++;
	}
}

/* PUBLIC INIT ROUTINE */

void Init()
{
	DDRD = 0xFF;
	DDRC = 0xFF;

	PORTD = 0x00;
	PORTD = (1 << RES);

	command(0x2A);  //function set (extended command set)
	command(0x71);  //function selection A, disable internal Vdd regualtor
	data(0x00);
	command(0x28);  //function set (fundamental command set)
	command(0x08);  //display off, cursor off, blink off
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xD5);  //set display clock divide ratio/oscillator frequency
	command(0x70);  //set display clock divide ratio/oscillator frequency
	command(0x78);  //OLED command set disabled
	command(0x09);  //extended function set (4 lines) - Wraps at char 19 instead of 39.
	command(0x06);  //COM SEG direction (Visual flipping of characters and lines)
	command(0x72);  //function selection B, disable internal Vdd regualtor
	data(0x00);     //ROM CGRAM selection - Table A (Standard/Latin Characters)
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xDA);  //set SEG pins hardware configuration
	command(0x10);  //set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)
	command(0xDC);  //function selection C
	command(0x00);  //function selection C
	command(0x81);  //set contrast control
	command(0x00);  //set contrast control (0-255)
	command(0xD9);  //set phase length
	command(0xF1);  //set phase length
	command(0xDB);  //set VCOMH deselect level
	command(0x40);  //set VCOMH deselect level
	command(0x78);  //OLED command set disabled
	command(0x28);  //function set (fundamental command set)
	command(0x01);  //clear display
	command(0x80);  //set DDRAM address to 0x00

	command(0x0C);  //display ON
}

DisplayPage CreatePage(uint8_t * str)
{
	DisplayPage page = malloc(sizeof(DisplayPage));

	uint8_t * line1 = malloc(20*sizeof(uint8_t));
	uint8_t * line2 = malloc(20*sizeof(uint8_t));

	sprintf(line1, "                    ");
	sprintf(line2, "                    ");

	int strc = 0;
	int cnt = 0;

	while(str[strc] != 0 && str[strc] != '\n' && cnt < LINE_LENGTH)
	{
		line1[cnt] = str[strc];
		strc ++;
		cnt ++;
	}

	if(str[strc] == '\n')
	{
		strc ++;
	}
	cnt = 0;

	while(str[strc] != 0 && cnt < LINE_LENGTH)
	{
		line2[cnt] = str[strc];
		strc ++;
		cnt ++;
	}

	page->line1 = line1;
	page->line2 = line2;

	return page;
}
void DeletePage(DisplayPage page)
{
	free(page);
}
void WritePage(DisplayPage page)
{
	command(0x02);
	Str(page->line1);
	Str(page->line2);
}
