#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "command.h"

const char* commands[COMMAND_COUNT] = { "load", "rand", "quit" };
const char* bitmap_commands[COMMAND_BITMAP_COUNT] = { "edit", "drop" };

int invoke_command(char* command, char** params, i32_t count)
{
	if (strcmp(command, "load") == 0) return command_load(params, count);
	if (strcmp(command, "edit") == 0) return command_bitmap_edit(params, count);
	if (strcmp(command, "rand") == 0) return command_rand();
	if (strcmp(command, "drop") == 0) return command_drop();
	if (strcmp(command, "quit") == 0) return command_quit(0);
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
	printf("Not yet implemented!\n");
	return SUCCESS;
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