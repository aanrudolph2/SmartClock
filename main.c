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
	Str("February 4, 2017");
	while(1);
}
