#include "reader.h"

Reader::Reader(const std::string &path, Image image) : image_(image) {

    std::ifstream in;
    in.open(path, std::ios::in | std::ios::binary);

    if (!in.is_open()) {
        throw std::invalid_argument(std::string("File: ") + path + " could not be opened.");
    }


    const int file_header_size = 14;
    const int info_header_size = 40;

    unsigned char file_header[file_header_size];
    in.read(reinterpret_cast<char*>(file_header), file_header_size);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::invalid_argument(std::string("Path: ") + path + " is not a bitmap image.");
    }

    unsigned char info_header[info_header_size];
    in.read(reinterpret_cast<char*>(info_header), info_header_size);

    //int file_size = file_header[2] + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);

    int w = info_header[4] + (info_header[5] << 8) + (info_header[6] << 16) + (info_header[7] << 24);
    int h = info_header[8] + (info_header[9] << 8) + (info_header[10] << 16) + (info_header[11] << 24);
    image_.width_ = w;
    image_.height_ = h;

    int bits_per_pixel = info_header[14] + (info_header[15] << 15);

    if (bits_per_pixel != 24) {
        throw std::invalid_argument("Incorrect file format");
    }

    Color color;
    for (int i = 0; i != h; ++ i) {
        std::vector<Color> help;
        for (int j = 0; j != w; ++ j) {
            help.push_back(color);
        }
        image_.colors_.push_back(help);
    }

    const int padding = ((4 - (w * 3) % 4) % 4);

    //unsigned char buffer[padding];

    for (int y = 0; y != h; ++ y) {
        for (int x = 0; x != w; ++x) {

            unsigned char new_color[3];
            in.read(reinterpret_cast<char*>(new_color), 3);
            image_.colors_[y][x].r = static_cast<float>(new_color[2]) / 255.0f;
            image_.colors_[y][x].g = static_cast<float>(new_color[1]) / 255.0f;
            image_.colors_[y][x].b = static_cast<float>(new_color[0]) / 255.0f;
        }

        in.ignore(padding);
    }

    in.close();

}