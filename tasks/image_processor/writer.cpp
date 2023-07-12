#include "writer.h"

Writer::Writer(const std::string &path, Image image) : image_(image) {

    std::ofstream out;
    out.open(path, std::ios::out | std::ios::binary);

    if (!out.is_open()) {
        throw std::invalid_argument(std::string("File: ") + path + "could not be opened.");
    }


    unsigned char bmp_pad[3] = {0, 0, 0};

    const int padding = (4 - ((image.width_ * 3) % 4)) % 4;

    const int file_header_size = 14;
    const int info_header_size = 40;
    const int file_size = 14 + 40 + image_.width_ * image_.height_ * 3 + padding * image_.width_;



    unsigned char file_header[file_header_size] = {'B', 'M', 0, 0, 0, 0, 0,
                                                   0, 0, 0, 0, 0, 0, 0};


    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    file_header[10] = 54;

    unsigned char info_header[info_header_size];

    info_header[0] = info_header_size;
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;

    info_header[4] = image_.width_;
    info_header[5] = image_.width_ >> 8;
    info_header[6] = image_.width_ >> 16;
    info_header[7] = image_.width_ >> 24;

    info_header[8] = image_.height_;
    info_header[9] = image_.height_ >> 8;
    info_header[10] = image_.height_ >> 16;
    info_header[11] = image_.height_ >> 24;

    info_header[12] = 1;
    info_header[13] = 0;

    info_header[14] = 24;
    info_header[15] = 0;

    for (int i = 16; i != 40; ++ i) {
        info_header[i] = 0;
    }


    out.write(reinterpret_cast<char*>(file_header), file_header_size);
    out.write(reinterpret_cast<char*>(info_header), info_header_size);



    for (int y = 0; y != image_.height_; ++y) {
        for (int x = 0; x != image_.width_; ++ x) {

            unsigned char r = static_cast<unsigned char>(image_.colors_[y][x].r * 255.0f);
            unsigned char g = static_cast<unsigned char>(image_.colors_[y][x].g * 255.0f);
            unsigned char b = static_cast<unsigned char>(image_.colors_[y][x].b * 255.0f);

            unsigned char color[] = {b, g, r};

            out.write(reinterpret_cast<char*>(color), 3);
        }

        out.write(reinterpret_cast<char*>(bmp_pad), padding);
    }
    out.close();
}