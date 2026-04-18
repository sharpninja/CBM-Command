/***************************************************************
Copyright (c) 2012, Payton Byrd
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

//#include <stdlib.h>
//#include <stdio.h>
#include <string.h>
//#include <conio.h>
//#include <errno.h>
#include <device.h>
#ifdef __CBM__
#include <cbm.h>
#include "Configuration-CBM.h"
#endif

#include "Configuration.h"
#include "globalInput.h"
#include "globals.h"
#include "screen.h"

struct ConfigurationState g_configstate;

#undef defaultLeftDrive
#undef defaultRightDrive
#undef defaultLeftDisk
#undef defaultRightDisk
#undef color_background
#undef color_border
#undef color_selector
#undef color_text_borders
#undef color_text_menus
#undef color_text_files
#undef color_text_status
#undef color_text_highlight
#undef color_text_other
#undef keyMap
#undef screenOrientation
#undef isDoubleBuffered
#undef fileBuffer

void initializeDefaults(void)
{
    g_configstate.config.defaultLeftDrive = 8;
    g_configstate.config.defaultRightDrive = 9;
    g_configstate.config.defaultLeftDisk[0] = '0';
    g_configstate.config.defaultLeftDisk[1] = '\0';
    g_configstate.config.defaultRightDisk[0] = '0';
    g_configstate.config.defaultRightDisk[1] = '\0';

    g_configstate.keyMap[KM_COPY]             = HK_COPY;
    g_configstate.keyMap[KM_CREATE_D64]       = HK_CREATE_D64;
    g_configstate.keyMap[KM_WRITE_D64]        = HK_WRITE_D64;
    g_configstate.keyMap[KM_DELETE]           = HK_DELETE;
    g_configstate.keyMap[KM_DRIVE_LEFT]       = HK_DRIVE_LEFT;
    g_configstate.keyMap[KM_DRIVE_RIGHT]      = HK_DRIVE_RIGHT;
    g_configstate.keyMap[KM_DRIVE_CURRENT]    = HK_DRIVE_CURRENT;
    g_configstate.keyMap[KM_DRIVE_COMMAND]    = HK_DRIVE_COMMAND;
    g_configstate.keyMap[KM_HELP]             = HK_HELP;
    g_configstate.keyMap[KM_MAKE_DIRECTORY]   = HK_MAKE_DIRECTORY;
    g_configstate.keyMap[KM_ENTER_DIRECTORY]  = HK_ENTER_DIRECTORY;
    g_configstate.keyMap[KM_LEAVE_DIRECTORY]  = HK_LEAVE_DIRECTORY;
    g_configstate.keyMap[KM_PAGE_UP]          = HK_PAGE_UP;
    g_configstate.keyMap[KM_PAGE_DOWN]        = HK_PAGE_DOWN;
    g_configstate.keyMap[KM_QUIT]             = HK_QUIT;
    g_configstate.keyMap[KM_RENAME]           = HK_RENAME;
    g_configstate.keyMap[KM_REREAD_LEFT]      = HK_REREAD_LEFT;
    g_configstate.keyMap[KM_REREAD_RIGHT]     = HK_REREAD_RIGHT;
    g_configstate.keyMap[KM_REREAD_SELECTED]  = HK_REREAD_SELECTED;
    g_configstate.keyMap[KM_SELECT]           = HK_SELECT;
    g_configstate.keyMap[KM_SELECT_ALL]       = HK_SELECT_ALL;
    g_configstate.keyMap[KM_DESELECT_ALL]     = HK_DESELECT_ALL;
    g_configstate.keyMap[KM_TO_TOP]           = HK_TO_TOP;
    g_configstate.keyMap[KM_TO_BOTTOM]        = HK_TO_BOTTOM;
    g_configstate.keyMap[KM_EXECUTE_SELECTED] = HK_EXECUTE_SELECTED;
    g_configstate.keyMap[KM_COPY_DISK]        = HK_COPY_DISK;
    g_configstate.keyMap[KM_BATCH_CREATE_D64] = HK_BATCH_CREATE_D64;
    g_configstate.keyMap[KM_PATH]             = HK_PATH;
    g_configstate.keyMap[KM_ORIENTATION]      = HK_ORIENTATION;

    /* Color Configuration */

    // Choose useful default colors for each model.
#if defined(__C128__)
    g_configstate.config.color_background     = COLOR_BLACK;
    g_configstate.config.color_border         = COLOR_BLACK;
    g_configstate.config.color_selector       = COLOR_WHITE;
    g_configstate.config.color_text_borders   = COLOR_GRAY3;
    g_configstate.config.color_text_menus     = COLOR_WHITE;
    g_configstate.config.color_text_files     = COLOR_YELLOW;
    g_configstate.config.color_text_status    = COLOR_GRAY3;
    g_configstate.config.color_text_other     = COLOR_WHITE;
    g_configstate.config.color_text_highlight = COLOR_YELLOW;
#elif defined(__C64__) || defined(__CBM510__)
    g_configstate.config.color_background     = COLOR_BLUE;
    g_configstate.config.color_border         = COLOR_BLUE;
    g_configstate.config.color_selector       = COLOR_WHITE;
    g_configstate.config.color_text_borders   = COLOR_GRAY2;
    g_configstate.config.color_text_menus     = COLOR_GRAY3;
    g_configstate.config.color_text_files     = COLOR_GRAY3;
    g_configstate.config.color_text_status    = COLOR_GRAY2;
    g_configstate.config.color_text_other     = COLOR_GRAY3;
    g_configstate.config.color_text_highlight = COLOR_WHITE;
#elif defined(__VIC20__)
    g_configstate.config.color_background     = COLOR_WHITE;
    g_configstate.config.color_border         = COLOR_CYAN;
    g_configstate.config.color_selector       = COLOR_RED;
    g_configstate.config.color_text_borders   = COLOR_CYAN;
    g_configstate.config.color_text_menus     = COLOR_BLUE;
    g_configstate.config.color_text_files     = COLOR_BLUE;
    g_configstate.config.color_text_status    = COLOR_BLUE;
    g_configstate.config.color_text_other     = COLOR_BLACK;
    g_configstate.config.color_text_highlight = COLOR_YELLOW;
#elif defined(__PLUS4__)
    g_configstate.config.color_background     = COLOR_WHITE;
    g_configstate.config.color_border         = (BCOLOR_BLUE | CATTR_LUMA6);
    g_configstate.config.color_selector       = BCOLOR_RED;
    g_configstate.config.color_text_borders   = (BCOLOR_BLUE | CATTR_LUMA6);
    g_configstate.config.color_text_menus     = BCOLOR_BLUE;
    g_configstate.config.color_text_files     = BCOLOR_BLUE;
    g_configstate.config.color_text_status    = BCOLOR_BLUE;
    g_configstate.config.color_text_other     = BCOLOR_BLACK;
    g_configstate.config.color_text_highlight = BCOLOR_YELLOW;
#else
    g_configstate.config.color_text_borders   = 0;
#endif
}

/*
unsigned char color_background;
unsigned char color_border;
unsigned char color_selector;
unsigned char color_text_borders;
unsigned char color_text_menus;
unsigned char color_text_files;
unsigned char color_text_status;
unsigned char color_text_other;
unsigned char color_text_highlight;
unsigned char color_text_borders;
*/

/* Load configuration
 * --------------------------
 * - Payton Byrd
 * --------------------------
 * Loads the configuration
 * from disk.
 */
void load(void)
{
#if defined(__CBM__)
	loadCBM();
#endif
}

#if defined(__CBM__)
void loadCBM(void)
{
	if (cbm_open(1,
		// Get the drive from which the program was loaded.
		defaultLeftDrive = defaultRightDrive = getcurrentdevice(), 2,
#ifdef __PET__
		// We assume that IEEE systems have dual-drives.
		"cbmcmd22cfg."
#else
		// We assume that IEC systems have single-drives.
		":cbmcmd22cfg."
#endif

	// We use different filenames for the various
	// models, so that different versions can be
	// on the same disk, and not have to share
	// the same configuration.
#ifdef __C64__
		"c64"
#endif
#ifdef __C128__
		"c128"
#endif
#ifdef __PET__
		"pet"
#endif
#ifdef __VIC20__
		"vc20"
#endif
#ifdef __PLUS4__
		"plus4"
#endif
		) == 0)
	{
		// Change from the default settings only
		// if the configuration file can be read.
		if (cbm_read(1, buffer,
#ifdef COLOR_RED
			// expecting drives, keys, and colors on color systems
			19 + sizeof keyMap) == 19 + sizeof keyMap
#else
			// expecting only drives and keys on monochrome systems
			10 + sizeof keyMap) == 10 + sizeof keyMap
#endif
		   )
		{
			// Set the values from the configuration bytes.

			/* Drive Settings */
			defaultLeftDrive	= buffer[0];
			strcpy(defaultLeftDisk, &buffer[1]);
			defaultRightDrive	= buffer[5];
			strcpy(defaultRightDisk, &buffer[6]);

// The CBM/PET clan (except the CBM510) doesn't support color.
// Don't change colors if only black and white are defined.
#ifdef COLOR_RED
			/* Color settings */
			color_background	= buffer[10];
			color_border		= buffer[11];
			color_selector		= buffer[12];
			color_text_borders	= buffer[13];
			color_text_menus	= buffer[14];
			color_text_files	= buffer[15];
			color_text_status	= buffer[16];
			color_text_other	= buffer[17];
			color_text_highlight= buffer[18];

			memcpy(keyMap, buffer + 19, sizeof keyMap);
#else
			memcpy(keyMap, buffer + 10, sizeof keyMap);
#endif
		}
	}
	else
	{
		// The configuration drive couldn't be reached;
		// tell the user about that unusual condition.
		writeStatusBar("Config. drive failed");
		waitForEnterEsc();
	}

	// Close the channels
	cbm_close(1);
	//cbm_close(15);
}
#endif
