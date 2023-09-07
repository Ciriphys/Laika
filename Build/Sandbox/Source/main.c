#include <stdio.h>

#include "laika.h"

int main(int argc, char** argv)
{
    printf("Hello, World!\n");

    bitmap_t* image = (bitmap_t*)load_bitmap_file("D:\\dev\\C\\Laika\\Assets\\Image\\Bitmap\\small.bmp");

    image = bitmap_invert(image, 1, 0, 1);
    save_bitmap_file("D:\\dev\\C\\Laika\\Assets\\Image\\Bitmap\\rb_sample.bmp", image);

    return 0;
}