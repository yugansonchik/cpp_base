#include "image_processor.h"

class Sharpening : public Filter {
public:
    void Apply(Image &image) override;
};