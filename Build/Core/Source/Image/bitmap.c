#include <stdlib.h>
#include <math.h>

#include "Image/bitmap.h"

LKA_API void* load_bitmap_file(char* filepath)
{
	// Checks if the file exists; it should be, but you never know!
	FILE* file = fopen(filepath, "rb");
	if (!file) return NULL;

	// Make sure that the file is not empty!
	fseek(file, 0, SEEK_END);
	if (ftell(file) == 0) return NULL;

	// Rewind file pointer
	fseek(file, 0, SEEK_SET);

	// Initialize the image pointer
	bitmap_t* image = (bitmap_t*)malloc(sizeof(bitmap_t));

	image->header	   = (bitmap_file_header_t*)		malloc(sizeof(bitmap_file_header_t));
	image->information = (bitmap_information_header_t*) malloc(sizeof(bitmap_information_header_t));
	image->color_table = (bitmap_color_table_t*)	    malloc(sizeof(bitmap_color_table_t));
	image->pixel_array = (bitmap_pixel_array_t*)		malloc(sizeof(bitmap_pixel_array_t));

    image->color_table->colors = NULL;
    
	// Load bitmap data
	load_bitmap_file_header(image, file);
	load_bitmap_information_header(image, file);

	if (image->information->colors > 0)
		load_bitmap_color_table(image, file);

	load_bitmap_image_data(image, file);

	// TODO : Read ICC Profiles if V5 header.
	if (image->information->header_size > 108);

	fclose(file);

	return (void*)image;
}

LKA_API void destroy_bitmap_image(bitmap_t* image)
{
    if(image)
    {
        free(image->header);
        free(image->information);
        
        if(image->color_table->colors)
            free(image->color_table->colors);
        
        free(image->color_table);
        free(image->pixel_array->pixels);
        free(image->pixel_array);
		free(image);
    }
}

void load_bitmap_file_header(bitmap_t* image, FILE* file)
{
	fread(image->header->header_field,	sizeof(byte_t), 2, file);
	fread(&image->header->size,			sizeof(i32_t),	1, file);
	fread(image->header->reserved1,		sizeof(byte_t), 2, file);
	fread(image->header->reserved2,		sizeof(byte_t), 2, file);
	fread(&image->header->offset,		sizeof(i32_t),	1, file);
}

void load_bitmap_information_header(bitmap_t* image, FILE* file)
{
	fread(&image->information->header_size,	sizeof(i32_t), 1, file);
	fread(&image->information->width,		sizeof(u32_t), 1, file);
	fread(&image->information->height,		sizeof(u32_t), 1, file);
	fread(&image->information->planes,		sizeof(i16_t), 1, file);
	fread(&image->information->bpp,			sizeof(i16_t), 1, file);
	fread(&image->information->compression,	sizeof(i32_t), 1, file);
	fread(&image->information->image_size,	sizeof(i32_t), 1, file);
	fread(&image->information->x_ppm,		sizeof(i32_t), 1, file);
	fread(&image->information->y_ppm,		sizeof(i32_t), 1, file);
	fread(&image->information->colors,		sizeof(i32_t), 1, file);
	fread(&image->information->color_count,	sizeof(i32_t), 1, file);

	if (image->information->header_size > 40) // from V2 to V5
	{
		fread(&image->information->red_bitmask,			sizeof(i32_t), 1, file);
		fread(&image->information->green_bitmask,		sizeof(i32_t), 1, file);
		fread(&image->information->blue_bitmask,		sizeof(i32_t), 1, file);
	}

	if (image->information->header_size > 52) // from V3 to V5
	{
		fread(&image->information->alpha_bitmask,	sizeof(i32_t), 1, file);
	}

	if (image->information->header_size > 56) // from V4 to V5
	{
		fread(&image->information->color_space_type,		sizeof(i32_t),  1,	file);
		fread( image->information->color_space_endpoints,	sizeof(byte_t), 36, file);
		fread(&image->information->red_gamma,				sizeof(i32_t),	1,	file);
		fread(&image->information->green_gamma,				sizeof(i32_t),	1,	file);
		fread(&image->information->blue_gamma,				sizeof(i32_t),	1,	file);
	}

	if (image->information->header_size > 108) // V5
	{
		fread(&image->information->intent,	 sizeof(i32_t),  1, file);
		fread(&image->information->icc_data, sizeof(i32_t),  1, file);
		fread(&image->information->icc_size, sizeof(i32_t),	 1, file);
		fread( image->information->reserved, sizeof(byte_t), 4, file);
	}
}

void load_bitmap_color_table(bitmap_t* image, FILE* file)
{
}

void load_bitmap_image_data(bitmap_t* image, FILE* file)
{
	i64_t size = ceil(image->information->bpp * image->information->width / 32) * 4 * image->information->height;
	image->pixel_array->pixels = (byte_t*)malloc(size * sizeof(byte_t));

	fread(image->pixel_array->pixels, sizeof(byte_t), size, file);
}
