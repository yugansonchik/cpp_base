#include "image_processor.h"


class Writer {
public:
    Writer(const std::string &path, Image image);
    Image image_;
};