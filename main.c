/*
 * main.c
 *
 *  Created on: Jan 30, 2017
 *      Author: Aaron
 */

#include "LCD/LCDDRV.h"

int main()
{
	Init();
	DisplayPage page1 = CreatePage("Test Message Blargh!\nWhat do you mean?");
	DisplayPage page2 = CreatePage("Hello World");

	WritePage(page1);
	_delay_ms(5000);
	WritePage(page2);

	while(1);
}
