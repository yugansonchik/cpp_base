//
// Created by ugans on 3/26/2023.
//

#include "image_processor.h"

class Negative : public Filter {
public:
    void Apply(Image &image) override;
};
