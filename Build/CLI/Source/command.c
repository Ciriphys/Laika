#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "laika.h"
#include "command.h"

const char* commands[COMMAND_COUNT] = { "load", "rand", "quit" };
const char* bitmap_commands[COMMAND_BITMAP_COUNT] = { "edit", "save", "drop" };

int invoke_command(char* command, char** params, i32_t count)
{
	if (strcmp(command, "load") == 0) return command_load(params, count);
	if (strcmp(command, "edit") == 0) return command_bitmap_edit(params, count);
	if (strcmp(command, "rand") == 0) return command_rand();
	if (strcmp(command, "drop") == 0) return command_drop();
	if (strcmp(command, "quit") == 0) return command_quit(0);
    if (strcmp(command, "save") == 0) return command_bitmap_save(params, count);
    
    return ERROR;
}

void evaluate_command(char** params, i32_t count)
{
	if (count == 0) return;

	switch (application->type)
	{
		case NoData: evaluate_specific(params, count, commands, COMMAND_COUNT); break;
		case Bitmap: evaluate_specific(params, count, bitmap_commands, COMMAND_BITMAP_COUNT); break;
	}

	// Destroy the parameters information
	for (i32_t i = 0; i < count; i++)
	{
		free(params[i]);
	}

	free(params);
}

void evaluate_specific(char** params, i32_t count, const char** command_list, i32_t size)
{
	i32_t valid = 0;
	char* command = params[0];

	for (i32_t i = 0; i < size; i++)
	{
		if (strcmp(command, command_list[i]) == 0)
		{
			i32_t result = invoke_command(command, params, count);
			if (result) application_display_error_message(result);

			valid = 1;
			break;
		}
	}

	if (!valid) application_display_error_message(COMMAND_UNKNOWN);
}

i32_t command_load(char** params, i32_t count)
{
	if (count == 1) return COMMAND_MISSING_DATA;

	char* filepath = params[1];
	char* extension = extract_extension(filepath);

	if (check_extension(extension)) return COMMAND_INVALID_EXTENSION;

	FILE* file = fopen(filepath, "rb");
	if (!file) return COMMAND_INVALID_DATA;
	fclose(file);

	load_file_information(filepath);

	destroy_data(application);
	load_data(application);

	if (!application->data) return COMMAND_LOAD_ERROR;

	printf("Loaded filename: %s\n", application->loaded_filename);
	printf("Filename extension: %s\n", extension);

	free(extension);

	return COMMAND_SUCCESS;
}

i32_t command_bitmap_edit(char** params, i32_t count)
{
	const char* subcommands[] = { "invert", "grayscale", "set" };

	i32_t command = -1;
	i32_t set_value = -1;
	i32_t red = 0, green = 0, blue = 0;

	for (i32_t i = 1; i < count; i++)
	{
		printf("params[%d]: %s\n", i, params[i]);

		i32_t can_skip = 0;

		for (i32_t j = 0; j < 2 && command == -1; j++)
		{
			if (strcmp(params[i], subcommands[j]) == 0)
			{
				command = j;
				can_skip = 1;
				break;
			}
		}

		if (can_skip) continue;

		if (command == 1 && set_value == -1)
		{
			set_value = (i32_t)(byte_t)atoi(params[i]);
			continue;
		}

		i32_t length = strlen(params[i]);

		if (length == 1)
		{
			switch (params[i][0])
			{
				case 'r': red	= 1; break;
				case 'g': green = 1; break;
				case 'b': blue	= 1; break;
				default: break;
			}
		}
	}

	switch (command)
	{
		case 0: 
			bitmap_invert((bitmap_t*)application->data, red, green, blue);
			return COMMAND_SUCCESS;
		case 1:
			bitmap_grayscale((bitmap_t*)application->data);
			return COMMAND_SUCCESS;
		case 2: 
			bitmap_set((bitmap_t*)application->data, (byte_t)set_value, red, green, blue);
			return COMMAND_SUCCESS; 
		default: 
			return COMMAND_INVALID_SUBCOMMAND;
	}
}

i32_t command_bitmap_save(char** params, i32_t count)
{
    if(count == 1) return COMMAND_MISSING_DATA;
    
    char* filename = NULL;
    
    for(i32_t i = 1; i < count; i++)
    {
        if(strcmp(params[i], "!") == 0)
        {
            filename = extract_raw_filename(application->loaded_filename);
            break;
        }
        else if(!filename)
        {
            filename = extract_raw_filename(params[i]);
            break;
        }
    }
    

    char* extension = extract_extension(application->loaded_filename);
    char* path = extract_path(application->loaded_filepath);
    
    i32_t path_len = (i32_t)strlen(path);
    i32_t filename_len = (i32_t)strlen(filename);
    i32_t extension_len = (i32_t)strlen(extension);
    
    char* filepath = (char*)malloc(path_len + filename_len + extension_len + 3);
    strcpy(filepath, path);

#ifdef CLI_WIN
	strcat(filepath, "\\");
#else
	strcat(filepath, "/");
#endif

    strcat(filepath, filename);
	strcat(filepath, ".");
    strcat(filepath, extension);
    filepath[path_len + filename_len + extension_len + 2] = 0;
    
	i32_t result = save_bitmap_file(filepath, (bitmap_t*)application->data);

	free(filepath);
    free(filename);
    free(extension);
    free(path);
    
	return result;
}

i32_t command_drop()
{
	free(application->loaded_filepath);
	free(application->loaded_filename);

	destroy_data(application);

	application->mode = None;
	application->type = NoData;
	application->loaded_filepath = NULL;
	application->loaded_filename = NULL;

	return COMMAND_SUCCESS;
}

i32_t command_rand()
{
	printf("Random i32_t: %d\n",	random_i32());
	printf("Random u32_t: %u\n",	random_u32());
	printf("Random i64_t: %lld\n",	random_i64());
	printf("Random u64_t: %llu\n",	random_u64());
	printf("Random f32_t: %ff\n",	random_f32());
	printf("Random f64_t: %lf\n",	random_f64());

	return 0;
}

i32_t command_quit(i32_t exit_code)
{
	application->exit_code = exit_code;
	application->running = 0;
	application->running = 0;

	return exit_code;
}
