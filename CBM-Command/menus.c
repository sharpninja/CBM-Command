/***************************************************************
Copyright (c) 2010, Payton Byrd
All rights reserved.

Redistribution and use in source and binary forms, with or
without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the following
  disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the following
  disclaimer in the documentation and/or other materials
  provided with the distribution.

* Neither the name of Payton Byrd nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior written
  permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "Configuration.h"
#include "constants.h"
#include "globals.h"
#include "input.h"
#include "menus.h"
#include "screen.h"


// Writes the function menu bar at the bottom of the screen;
// it is scaled to the screen size.
void writeMenuBar(void)
{
	//static const unsigned char bottom = size_y - 1;

	(void)textcolor(color_text_menus);
	//revers(true);

	//cclearxy(0, 0, size_x);

	//cputsxy(   LEFT_MENU_X * size_x / 100, 0, LEFT_MENU);
	//cputsxy(   FILE_MENU_X * size_x / 100, 0, FILE_MENU);
	//cputsxy(COMMAND_MENU_X * size_x / 100, 0, COMMAND_MENU);
	//cputsxy(OPTIONS_MENU_X * size_x / 100, 0, OPTIONS_MENU);
	//cputsxy(  RIGHT_MENU_X * size_x / 100, 0, RIGHT_MENU);

	//revers(false);
#if size_x == 22
	cputsxy(1, size_y - 2, "HELP  DRIV  CPY  MKD\r\n"
		" QUIT  REFR  REN  DEL");

	revers(true);
	//textcolor(color_text_highlight);
	cputcxy(0, size_y - 2, '1');
	gotox(6); cputc('3');
	gotox(12); cputc('5');
	gotox(17); cputc('7');
	cputcxy(0, size_y - 1, '2');
	gotox(6); cputc('4');
	gotox(12); cputc('6');
	gotox(17); cputc('8');
#endif
#if size_x == 40
	cputsxy(1, size_y - 1, "HLP  QUIT  DRV  REF  CPY  REN  MDR  DEL");

	revers(true);
	//(void)textcolor(color_text_highlight);
	cputcxy(0, size_y - 1, '1');
	gotox(5);  cputc('2');
	gotox(11); cputc('3');
	gotox(16); cputc('4');
	gotox(21); cputc('5');
	gotox(26); cputc('6');
	gotox(31); cputc('7');
	gotox(36); cputc('8');
#endif
#if size_x == 80
	cputsxy(2, size_y - 1,
		"HELP     QUIT    DRIVE    REFRESH   COPY    RENAME    MAKE DIRECTORY    DELETE");

	revers(true);
	//(void)textcolor(color_text_highlight);
#ifdef __PET__
	cputcxy(1, size_y - 1, '1');
	gotox(10); cputc('2');
	gotox(18); cputc('3');
	gotox(27); cputc('4');
	gotox(37); cputc('5');
	gotox(45); cputc('6');
	gotox(55); cputc('7');
	gotox(73); cputc('8');
#else
	cputsxy(0, size_y - 1, "F1");
	gotox(9);  cputs("F2");
	gotox(17); cputs("F3");
	gotox(26); cputs("F4");
	gotox(36); cputs("F5");
	gotox(44); cputs("F6");
	gotox(54); cputs("F7");
	gotox(72); cputs("F8");
#endif
#endif

	revers(false);
}
