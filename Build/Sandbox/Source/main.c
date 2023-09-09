#include <stdio.h>
#include <stdlib.h>

#include "laika.h"

int main(int argc, char** argv)
{
    printf("Hello, World!\n");

    bitmap_t* image = (bitmap_t*)load_bitmap_file("D:\\dev\\C\\Laika\\Assets\\Image\\Bitmap\\sample.bmp");

    bitmap_redscale(image);
    save_bitmap_file("D:\\dev\\C\\Laika\\Assets\\Image\\Bitmap\\red_scale.bmp", image);

    return 0;
}