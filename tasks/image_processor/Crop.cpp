#include "Crop.h"


Crop::Crop(int width, int height) {
    w = width;
    h = height;
}

void over(Image &image) {
    Image copy = image;

    for (int x = 0; x != copy.height_; ++x) {
        image.colors_[x]= copy.colors_[copy.height_ - 1 - x];
    }
}

void Crop::Apply(Image &image)  {
    over(image);
    if (w <= image.width_ and h <= image.height_) {
        image.width_ = w;
        image.height_ = h;
    } else if (w <= image.width_) {
        image.width_ = w;
    } else if (h <= image.height_) {
        image.height_ = h;
    }
    over(image);
}