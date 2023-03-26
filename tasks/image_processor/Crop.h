#include "image_processor.h"

class Crop : public Filter {
public:
    Crop(int width, int height);
    void Apply(Image &image) override;
    int w;
    int h;
};
