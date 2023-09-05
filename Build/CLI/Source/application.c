#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "application.h"
#include "command.h"

application_t* application = NULL;

const char* extensions[EXTENSIONS_COUNT] = { "bmp", "dib" };

application_t* create_application_context(const char* program_path, u32_t buflen)
{
    if (application) destroy_application_context(application);

    application = (application_t*)malloc(sizeof(application_t));

    application->program_path = (char*)malloc(buflen + 1);
	application->loaded_filepath = NULL;
	application->loaded_filename = NULL;
    application->data = NULL;
    application->running = 1;
    application->exit_code = -1;
    application->mode = None;
    application->type = NoData;

    strcpy(application->program_path, program_path);
    application->program_path[buflen] = 0;

    // Initialize random_seed
    random_init((u64_t)time(NULL));
    
    return application;
}

i32_t destroy_application_context(application_t* app_ptr)
{
    i32_t exit_code = app_ptr->exit_code;

    free(app_ptr->program_path);
    free(app_ptr->loaded_filepath);
    free(app_ptr->loaded_filename);
    free(app_ptr->data);
    free(app_ptr);

    return exit_code;
}

void load_data(application_t* app_ptr)
{
	switch (app_ptr->type)
	{
	case Bitmap:
        app_ptr->data = load_bitmap_file(app_ptr->loaded_filepath);
        if (!app_ptr->data) command_drop(NULL, 0);
		return;
	case NoData:
		return;
	}
}

void destroy_data(application_t* app_ptr)
{
    switch (app_ptr->type)
    {
    case Bitmap:
        if (app_ptr->data)
        {
            destroy_bitmap_image((bitmap_t*)app_ptr->data);
            app_ptr->data = NULL;
        }
        return;
    case NoData:
        return;
    }
}

void application_run(application_t* context)
{
    while (context->running)
    {
        char command[COMMAND_LENGTH];
        printf("[%s] $ ", application_get_mode_text(context->mode));
        fgets(command, COMMAND_LENGTH, stdin);
        command[strlen(command) - 1] = 0;

        application_parse_command(command);
    }
}

void application_display_error_message(i32_t result)
{
    // TODO : Add message for each error code
    printf("Error code: %#06x\n", result);
}

char* application_get_mode_text(application_mode_t mode)
{
    switch (mode)
    {
    case None:
        return "Laika";
    case Loaded:
        return application->loaded_filename;
    default:
        return "";
    }
}

char* extract_filename(char* filepath)
{
    i32_t length = (i32_t)strlen(filepath);
    i32_t offset = 0;

	for (i32_t i = length - 1; i > 0; i--)
	{
		if (filepath[i] == '\\' || filepath[i] == '/')
		{
			offset = i + 1;
			break;
		}
	}

    char* filename = (char*)malloc(length - offset + 1);
    strncpy(filename, filepath + offset, length - offset);
    filename[length - offset] = 0;

    return filename;
}

char* extract_extension(char* filename)
{
    i32_t length = (i32_t)strlen(filename);
    i32_t offset = 0;

    for (i32_t i = length - 1; i > 0; i--)
    {
        if (filename[i] == '.')
        {
            offset = i + 1;
            break;
        }
    }

	char* extension = (char*)malloc(length - offset + 1);
	strncpy(extension, filename + offset, length - offset);
    extension[length - offset] = 0;

	return extension;
}

i32_t check_extension(char* extension)
{
    for (i32_t i = 0; i < EXTENSIONS_COUNT; i++)
    {
        if (strcmp(extension, extensions[i]) == 0)
        {
            application->type = get_type_from_extension(extension);
            return SUCCESS;
        }
    }

    return ERROR;
}

application_data_type_t get_type_from_extension(char* extension)
{
    if (strcmp(extension, "bmp") == 0 || strcmp(extension, "dib") == 0)
    {
        return Bitmap;
    }
    else
    {
        return NoData;
    }  
}

void application_parse_command(char* command)
{
    i32_t size = 0;
    i32_t capacity = 2;
    char** params = (char**)malloc(capacity * sizeof(char*));

    i32_t previous_length = 0;
    i32_t first = 1;

    // TODO : FIX THIS !
     
    // Parse the command data
	for (i32_t i = 0; i < COMMAND_LENGTH; i++)
	{
        if (command[i] == 32 || command[i] == 0)
        {
            if (size >= capacity)
            {
                capacity += 2;
                params = (char**)realloc(params, capacity * sizeof(char*));
            }

            params[size] = (char*)malloc(i + 1);

            // Move the source pointer and calculate the byte count accordingly
            const char* source = size == 0 ? command : command + previous_length + 1;
            u32_t count = size == 0 ? i : i - (u32_t)previous_length - 1;

            strncpy(params[size], source, count);
            previous_length += count + (first == 0);
            params[size][count] = 0;
            first = 0;
            size++;

            if (command[i] == 0) break;
        }
	}

    evaluate_command(params, size);
}

void load_file_information(char* filepath)
{
    free(application->loaded_filepath);
    free(application->loaded_filename);

    application->mode = Loaded;
    application->loaded_filepath = (char*)malloc(strlen(filepath) + 1);
    strcpy(application->loaded_filepath, filepath);
    application->loaded_filepath[strlen(filepath)] = 0;
    application->loaded_filename = extract_filename(filepath);
}

char* extract_raw_filename(char* filepath)
{
    i32_t length = (i32_t)strlen(filepath);
    i32_t location = -1;
    i32_t offset = 0;

    for (i32_t i = length - 1; i > 0; i--)
    {
        if (filepath[i] == '\\' || filepath[i] == '/')
        {
            offset = i + 1;
            break;
        }
        else if(filepath[i] == '.' && location == -1)
        {
            location = i;
        }
    }

    char* filename = (char*)malloc(length - location + 1);
    strncpy(filename, filepath + offset, length - location);
    filename[length - location] = 0;

    return filename;
}

char* extract_path(char* filepath)
{
    i32_t length = (i32_t)strlen(filepath);
    i32_t offset = 0;

    for (i32_t i = length - 1; i > 0; i--)
    {
        if (filepath[i] == '\\' || filepath[i] == '/')
        {
            offset = i;
            break;
        }
    }

    if(offset)
    {
        char* filename = (char*)malloc(offset + 1);
        strncpy(filename, filepath, offset);
        filename[offset] = 0;
        
        return filename;
    }
    else return NULL;
}
