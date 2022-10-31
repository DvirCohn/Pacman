#ifndef IO_UTILS_H
#define IO_UTILS_H
// you must have a config file, both for windows and for compiling on Linux (MAMA)
// BUT, you need to change the content of the config!
#include "config.h"
//#include "Color.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "color.h"

void gotoxy(int x, int y);
void setTextColor(Color);
void hideCursor();
void clear_screen();

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#endif

#endif
