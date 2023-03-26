#pragma once
#include <vector>
#include "bmp_headers.h"
#include "math.h"
#include <string>

class Filter {
public:
    virtual void ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const;
    virtual std::string FilterName() const;
    virtual void ChangeSize(int32_t& height, int32_t& width) const {};
    virtual void NewArgs(std::vector <std::string> args) {};

protected:
    void ApplyMatrix(std::vector <std::vector <Color> >& pixel_array) const;

    std::vector <int32_t> args_;
    std::vector <std::vector <int32_t> > matrix_;
};

class Sharp : public Filter {
public:
    std::string FilterName() const override;
    Sharp();
};

class Negative : public Filter {
public:
    std::string FilterName() const override;
    void ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const override;
};

class Grayscale : public Filter {
public:
    std::string FilterName() const override;
    void ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const override;
};

class EdgeDetection : public Filter {
public:
    std::string FilterName() const override;
    void NewArgs(std::vector <std::string> args) override;
    EdgeDetection(std::vector <std::string> args);
    EdgeDetection() {};
    void ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const override;
private:
    int32_t threshold_;
};

class Crop : public Filter{
public:
    std::string FilterName() const override;
    Crop(std::vector <std::string> args);
    Crop() {};
    void NewArgs(std::vector <std::string> args) override;
    void ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const override;
    void ChangeSize(int32_t& height, int32_t& width) const override;
private:
    int32_t width_;
    int32_t height_;
};

class GaussianBlur : public Filter {
public:
    GaussianBlur(std::vector <std::string> args);
    GaussianBlur() {};
    void NewArgs(std::vector <std::string> args) override;
    void ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const override;
private:
    double sigma_;
    int32_t matsize_;
    double sum_;
    std::vector <std::vector <double> > matrix_;
};

class FastGaussianBlur : public Filter {
public:
    FastGaussianBlur(std::vector <std::string> args);
    FastGaussianBlur() {};
    void NewArgs(std::vector <std::string> args) override;
    void ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const override;
private:
    double sigma_;
    int32_t matsize_;
    double sum_;
    std::vector <double> matrix_;
};