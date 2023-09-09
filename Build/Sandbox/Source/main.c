#include <stdio.h>
#include <stdlib.h>

#include "laika.h"

int main(int argc, char** argv)
{
    printf("Hello, World!\n");

    bitmap_t* image = (bitmap_t*)load_bitmap_file("D:\\dev\\C\\Laika\\Assets\\Image\\Bitmap\\sample.bmp");

    bitmap_invert(image, 1, 1, 1);
    save_bitmap_file("D:\\dev\\C\\Laika\\Assets\\Image\\Bitmap\\inverted.bmp", image);

    return 0;
}