#pragma once

#include "warnings.h"
#include "laika.h"

#include "Image/bitmap.h"

#define EXTENSIONS_COUNT	2

#define SUCCESS	 0
#define ERROR	-1

#define TEXT(str) #str

enum __application_mode_t
{
	None = 0,
	Loaded = 1
};

enum __application_data_type_t
{
	NoData = 0,
	Bitmap = 1
};

typedef enum __application_mode_t application_mode_t;
typedef enum __application_data_type_t application_data_type_t;

struct __application_t
{
	char* program_path;
	i32_t running;

	application_mode_t mode;
	application_data_type_t type;

	char* loaded_filepath;
	char* loaded_filename;

	void* data;

	i32_t exit_code;
};

typedef struct __application_t application_t;

extern application_t* application;

application_t* create_application_context(const char* program_path, u32_t buflen);
i32_t	destroy_application_context(application_t* app_ptr);

// Wrappers for loading and destroying image data.
void load_data(application_t* app_ptr);
void destroy_data(application_t* app_ptr);

void	application_parse_command(char* command);
void	application_run(application_t* context);
void	application_display_error_message(i32_t result);
char*	application_get_mode_text(application_mode_t mode);

void	load_file_information(char* filepath);

char* extract_filename (char* filepath);
char* extract_extension(char* filename);

i32_t check_extension(char* extension);

application_data_type_t get_type_from_extension(char* extension);
