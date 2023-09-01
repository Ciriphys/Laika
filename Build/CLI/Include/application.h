#pragma once

#include "warnings.h"
#include "converter.h"

// Maybe this should be increased?
#define COMMAND_LENGTH		64
#define COMMAND_COUNT		3
#define EXTENSIONS_COUNT	2

#define COMMAND_SUCCESS				0x0000	
#define COMMAND_MISSING_DATA		0x0001		// Missing data for parameters
#define COMMAND_OVERFLOW			0x0002		// Too many commands passed [Deprecated]
#define COMMAND_INVALID_DATA		0x0003		// Invalid data passed (file not found)
#define COMMAND_INVALID_EXTENSION	0x0004		

#define LOAD_ID 0x0000
#define DROP_ID 0x0001
#define EXIT_ID 0x0002

#define INVALID_ID 0xffff

#define MAX_LOAD_PARAMS 2
#define MAX_DROP_PARAMS 1

#define SUCCESS	 0
#define ERROR	-1

#define TEXT(str) #str

enum __application_mode_t
{
	None = 0,
	Loaded = 1,
};

typedef enum __application_mode_t application_mode_t;

struct __application_t
{
	char* program_path;
	i32_t running;

	application_mode_t mode;
	char* loaded_filepath;
	char* loaded_filename;

	i32_t exit_code;
};

typedef struct __application_t application_t;

application_t* create_application_context(const char* program_path, u32_t buflen);
i32_t	destroy_application_context(application_t* app_ptr);

void    application_evaluate_command(char** params, i32_t count);
i32_t   application_invoke_command(i32_t command, char** params, i32_t count);
void	application_parse_command(char* command);
void	application_run(application_t* context);

void	application_display_error_message(i32_t result);

char*	application_get_mode_text(application_mode_t mode);

i32_t command_load(char** params, i32_t count);
i32_t command_drop(char** params, i32_t count);
i32_t command_exit(i32_t exit_code);

char* extract_filename (char* filepath);
char* extract_extension(char* filename);

i32_t check_extension(char* extension);
