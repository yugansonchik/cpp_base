#include "GrayScale.h"

void GrayScale::Apply(Image &image)  {
    for (int y = 0; y != image.height_; ++y) {
        for (int x = 0; x != image.width_; ++x) {


            auto a = (0.299 * image.colors_[y][x].r
                      + 0.587 * image.colors_[y][x].g
                      + 0.114 * image.colors_[y][x].b);

            image.colors_[y][x].r = a;
            image.colors_[y][x].g = a;
            image.colors_[y][x].b = a;


        }
    }
}