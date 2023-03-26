#include <stdint.h>
#pragma once
#pragma pack(push, 1)
class BMPHeader {  // https://en.wikipedia.org/wiki/BMP_file_format#Example_1
public:
    uint16_t file_type;
    uint32_t file_size;
    uint16_t trash1;
    uint16_t trash2;
    uint32_t offset_data;
};

class DIBHeader { // https://en.wikipedia.org/wiki/BMP_file_format#Example_1
public:
    uint32_t size;
    int32_t width;  // bmp could has width < 0
    int32_t height;

    uint16_t planes;
    uint16_t bits_per_pixel;

    uint32_t compression;  // should be 0 always
    uint32_t resolution_horizontal;
    uint32_t resolution_vertical;
    uint32_t colors_in_palette;
    uint32_t important_colors;
};

class Color {
public:
    uint8_t R;
    uint8_t B;
    uint8_t G;
};
#pragma pack(pop)