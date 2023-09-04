#pragma once

#include "application.h"
#include "types.h"

// Maybe this should be increased?
#define COMMAND_LENGTH			64
#define COMMAND_COUNT			3
#define COMMAND_BITMAP_COUNT	2	

#define MAX_LOAD_PARAMS 2
#define MAX_DROP_PARAMS 1

#define COMMAND_SUCCESS				0x0000	
#define COMMAND_MISSING_DATA		0x0001		// Missing data for parameters
#define COMMAND_OVERFLOW			0x0002		// Too many commands passed [Deprecated]
#define COMMAND_INVALID_DATA		0x0003		// Invalid data passed (file not found)
#define COMMAND_INVALID_EXTENSION	0x0004		
#define COMMAND_INVALID_MODE		0x0005		
#define COMMAND_LOAD_ERROR			0x0006		// Caused when the object loading function returns NULL
#define COMMAND_UNKNOWN				0x0007		

extern application_t* application;

i32_t invoke_command(char* command, char** params, i32_t count);
void  evaluate_command(char** params, i32_t count);
void  evaluate_specific(char** params, i32_t count, const char** command_list, i32_t size);

i32_t command_load(char** params, i32_t count);
i32_t command_bitmap_edit(char** params, i32_t count);
i32_t command_bitmap_save(char** params, i32_t count);
i32_t command_drop();
i32_t command_rand();
i32_t command_quit(i32_t exit_code);
