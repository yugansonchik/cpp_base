#include "image_processor.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection(float t);
    void Apply(Image &image) override;
    float threshold;

};