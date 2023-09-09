#include <stdio.h>

#include "laika.h"

int main(int argc, char** argv)
{
    printf("Hello, World!\n");

    bitmap_t* image = (bitmap_t*)load_bitmap_file("D:\\dev\\C\\Laika\\Assets\\Image\\Bitmap\\rb_inverted.bmp");

    image = bitmap_grayscale(image);
    save_bitmap_file("D:\\dev\\C\\Laika\\Assets\\Image\\Bitmap\\rb_inverted.bmp", image);

    return 0;
}