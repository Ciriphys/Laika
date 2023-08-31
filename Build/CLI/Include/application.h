#pragma once

#include "warnings.h"
#include "converter.h"

// Maybe this should be increased?
#define COMMAND_LENGTH 64
#define COMMAND_COUNT  3

#define COMMAND_SUCCESS 0x0	
#define COMMAND_MISSING_DATA 0x1	// Missing data for parameters
#define COMMAND_OVERFLOW 0x2		// Too many commands passed
#define COMMAND_INVALID_DATA 0x3	// Invalid data passed (file not found)

#define COMMAND_LOAD 0x0
#define COMMAND_DROP 0x1
#define COMMAND_EXIT 0x2

#define MAX_LOAD_PARAMS 2
#define MAX_DROP_PARAMS 1

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
	char* loaded_filename;

	i32_t exit_code;
};

typedef struct __application_t application_t;

application_t* create_application_context(const char* program_path, size_t buflen);
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