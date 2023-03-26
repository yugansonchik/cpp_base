#include "EdgeDetection.h"
#include "GrayScale.h"

EdgeDetection::EdgeDetection(float t) {
    threshold = t;
}

void EdgeDetection::Apply(Image &image) {

    GrayScale help;
    help.Apply(image);

    auto copy = image.colors_;
    for (int y = 1; y != image.height_ - 1; ++y) {
        for (int x = 1; x != image.width_ - 1; ++x) {


            image.colors_[x][y].r = std::min(static_cast<float>(1),
                                             std::max(static_cast<float>(0), 4 * copy[x][y].r
                                                                             - 1 * copy[x][y-1].r - 1 * copy[x-1][y].r - 1 * copy[x][y+1].r - 1 * copy[x+1][y].r));

            image.colors_[x][y].b = std::min(static_cast<float>(1),
                                             std::max(static_cast<float>(0), 4 * copy[x][y].b
                                                                             - 1 * copy[x][y-1].b - 1 * copy[x-1][y].b - 1 * copy[x][y+1].b - 1 * copy[x+1][y].b));

            image.colors_[x][y].g = std::min(static_cast<float>(1),
                                             std::max(static_cast<float>(0), 4 * copy[x][y].g
                                                                             - 1 * copy[x][y-1].g - 1 * copy[x-1][y].g - 1 * copy[x][y+1].g - 1 * copy[x+1][y].g));



        }
    }


    for (int y = 1; y != image.height_ - 1; ++y) {
        for (int x = 1; x != image.width_ - 1; ++x) {

            if (image.colors_[x][y].r > threshold) {
                image.colors_[x][y].r = 1;
                image.colors_[x][y].g = 1;
                image.colors_[x][y].b = 1;

            } else {
                image.colors_[x][y].r = 0;
                image.colors_[x][y].g = 0;
                image.colors_[x][y].b = 0;
            }

        }
    }
}