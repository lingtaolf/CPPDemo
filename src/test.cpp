#include "roaring/roaring.hh"
#include "roaring/roaring64map.hh"
#include <iostream>

int main(int argc, char* argv[])
{
    
    roaring_bitmap_t * rb1 = roaring_bitmap_create();
    roaring_bitmap_t * rb2 = roaring_bitmap_create();
    roaring_bitmap_add(rb1, 1);
    roaring_bitmap_add(rb2, 1);
    roaring_bitmap_add(rb2, 2);
    roaring_bitmap_printf(rb1);
    roaring_bitmap_printf(roaring_bitmap_and(rb2, rb1));
    
    roaring_bitmap_printf(roaring_bitmap_flip(rb1, 0, 1));
    return 0;
}