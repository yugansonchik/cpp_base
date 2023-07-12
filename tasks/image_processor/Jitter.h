#include "image_processor.h"

class Jitter : public Filter {
public:
    void Apply(Image &image) override;
};