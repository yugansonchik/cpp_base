//
// Created by ugans on 3/26/2023.
//

#include "Negative.h"

void Negative::Apply(Image &image) {
    for (int y = 0; y != image.height_; ++y) {
        for (int x = 0; x != image.width_; ++ x) {


            auto r1 = image.colors_[y][x].r;
            auto g1 = image.colors_[y][x].g;
            auto b1 = image.colors_[y][x].b;

            image.colors_[y][x].r = 1 - r1;
            image.colors_[y][x].g = 1 - g1;
            image.colors_[y][x].b = 1 - b1;

        }
    }
}

