#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
#include <map>
#pragma once

const std::string ENQUIRY =
        "The first two launch parameters must be the names of the file to be read and to be written\n"
        "Available commands: \n"
        "1. To apply Crop filter: -crop width(arg_1) height(arg_2) \n"
        "2. To apple GrayScale filter: -gs \n"
        "3. To apply Negative filter: -neg \n"
        "4. To apply Sharpening filter: -sharp \n"
        "5. To apply Edge Detection filter: -edge threshold(arg_1) \n"
        "6. To apply Gaussian Blur filter: -blur sigma(arg_1) \n"
        "7. To apply Jitter filter: -jit";


const std::map<std::string, float> filters = {{"-gs", 0}, {"-blur", 1},
                                              {"-crop", 2}, {"-neg", 0},
                                              {"-sharp", 0}, {"-edge", 1},
                                              {"-jit", 0}, {"-circle", 0}};
struct Color {
    float r, g, b;

    Color(): r(0), g(0), b(0)  {}
    Color(float r1, float g1, float b1) {
        r = r1;
        g = g1;
        b = b1;
    }
};


class Image {
public:
    Image(int width, int height) : width_(width), height_(height) {}

    int width_;
    int height_;
    std::vector<std::vector<Color>> colors_;
};


struct FilterDefinition {
    std::string name;
    std::vector<std::string> params;

    void Clear() {
        name = "";
        params = {};
    }

};

class Filter {
public:

    virtual void Apply(Image &image) = 0;
};



