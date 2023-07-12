#include "Jitter.h"
#include <experimental/random>

int Rand(int x, int y) {
    return std::experimental::randint(x, y);
}


void Jitter::Apply(Image &image) {

    Image copy = image;

    for (int y = 0; y != image.height_; ++y) {
        for (int x = 0; x != image.width_; ++x) {

            int x1 = Rand(std::max(0, x - 20), std::min(x + 20, copy.width_ - 1));
            int y1 = Rand(std::max(0, y - 20), std::min(y + 20, copy.height_ - 1));

            image.colors_[y][x] = copy.colors_[y1][x1];

        }
    }
}