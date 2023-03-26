#include "image_processor.h"

class GrayScale : public Filter {
public:
    void Apply(Image &image) override;
};