#include "image_processor.h"

class Reader {
public:
    Reader(const std::string &path, Image image);
    Image image_;
};