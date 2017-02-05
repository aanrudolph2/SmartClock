#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 20

typedef struct
{
	uint8_t * line1;
	uint8_t * line2;

} *DisplayPage;

DisplayPage CreatePage();
void WritePage(DisplayPage page);
void DeletePage(DisplayPage page);

void Init();
