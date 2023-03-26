#include "base_filters.h"
#include <unistd.h>
#include <iostream>

void Filter::ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const {
    ApplyMatrix(pixel_array);
}

std::string Filter::FilterName() const {
    return "MainFilter";
}

void Filter::ApplyMatrix(std::vector <std::vector <Color> >& pixel_array) const {
    int32_t height = pixel_array.size();
    int32_t width = pixel_array[0].size();
    std::vector <std::vector <Color> > image = pixel_array;
    int8_t dx[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int8_t dy[9] = {-1, 0, 1, -1, 0, 1, -1, 0 ,1};
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            int32_t res_r = 0, res_g = 0, res_b = 0;
            for (size_t pos = 0; pos < 9; pos++) {
                int32_t X = i + dx[pos];
                int32_t Y = j + dy[pos];
                X = std::max(X, 0); X = std::min(X, static_cast<int32_t>(height) - 1);
                Y = std::max(Y, 0); Y = std::min(Y, static_cast<int32_t>(width) - 1);

                res_r += static_cast<int32_t>(image[X][Y].R) * matrix_[dx[pos] + 1][dy[pos] + 1];
                res_g += static_cast<int32_t>(image[X][Y].G) * matrix_[dx[pos] + 1][dy[pos] + 1];
                res_b += static_cast<int32_t>(image[X][Y].B) * matrix_[dx[pos] + 1][dy[pos] + 1];

            }
            res_r = std::min(255, std::max(0, res_r));
            res_g = std::min(255, std::max(0, res_g));
            res_b = std::min(255, std::max(0, res_b));
            pixel_array[i][j].R = res_r;
            pixel_array[i][j].G = res_g;
            pixel_array[i][j].B = res_b;
        }
    }
}

std::string Sharp::FilterName() const {
    return "SharpFilter";
}

Sharp::Sharp() {
    matrix_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
}

std::string Negative::FilterName() const {
    return "NegativeFilter";
}

void Negative::ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const {
    uint32_t height = pixel_array.size();
    uint32_t width = pixel_array[0].size();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            pixel_array[i][j].R = 255 - static_cast<int32_t> (pixel_array[i][j].R);
            pixel_array[i][j].G = 255 - static_cast<int32_t> (pixel_array[i][j].G);
            pixel_array[i][j].B = 255 - static_cast<int32_t> (pixel_array[i][j].B);
        }
    }
}

std::string Grayscale::FilterName() const {
    return "GrayscaleFilter";
}

void Grayscale::ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const {
    uint32_t height = pixel_array.size();
    uint32_t width = pixel_array[0].size();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            int32_t cur = 0.299 * pixel_array[i][j].R + 0.587 * pixel_array[i][j].G + 0.114 * pixel_array[i][j].B;
            pixel_array[i][j].R = cur;
            pixel_array[i][j].G = cur;
            pixel_array[i][j].B = cur;
        }
    }
}

std::string EdgeDetection::FilterName() const {
    return "EdgeDetectionFilter";
}

void EdgeDetection::NewArgs(std::vector <std::string> args) {
    try {
        threshold_ = std::stod(args[0]) * 256;
        matrix_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    } catch (...) {
        throw std::runtime_error("Invalid -edge argument!");
        exit(0);
    }
}

EdgeDetection::EdgeDetection(std::vector <std::string> args) {
    NewArgs(args);
}

void EdgeDetection::ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const {
    int32_t height = pixel_array.size();
    int32_t width = pixel_array[0].size();
    Grayscale gs;
    gs.ApplyFilter(pixel_array);
    ApplyMatrix(pixel_array);
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            if (pixel_array[i][j].R > threshold_) {
                pixel_array[i][j].R = pixel_array[i][j].G = pixel_array[i][j].B = 255;
            } else {
                pixel_array[i][j].R = pixel_array[i][j].G = pixel_array[i][j].B = 0;
            }
        }
    }
}

void Crop::NewArgs(std::vector <std::string> args) {
    try {
        width_ = std::stoi(args[0]);
        height_ = std::stoi(args[1]);
    } catch (...) {
        throw std::runtime_error("Invalid -crop argument!");
        exit(0);
    }
}

Crop::Crop(std::vector <std::string> args) {
    NewArgs(args);
}

std::string Crop::FilterName() const {
    return "CropFilter";
}

void Crop::ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const {
    if (height_ < static_cast<int32_t>(pixel_array.size())) {
        pixel_array.erase(pixel_array.begin() + height_, pixel_array.end());
    }
    if (width_ < static_cast<int32_t>(pixel_array[0].size())) {
        for (auto &u: pixel_array) {
            u.erase(u.begin() + width_, u.end());
        }
    }
}

void Crop::ChangeSize(int32_t& height, int32_t& width) const {
    width = std::min(width, width_);
    height = std::min(height, height_);
}

void GaussianBlur::NewArgs(std::vector <std::string> args) {
    try {
        sigma_ = std::stod(args[0]);
        if (sigma_ < 1e-5) {
            throw std::runtime_error("Invalid -blur argument!");
        }
        matsize_ = sigma_ * 3 + 1;
        if (matsize_ % 2 == 0) {
            ++matsize_;
        }
        matrix_.resize(matsize_);
        for (auto &u: matrix_) {
            u.resize(matsize_);
        }
        int32_t center = matsize_ / 2;
        double pi = 3.1415926;
        double e = 2.71828;
        for (int32_t i = 0; i < matrix_.size(); ++i) {
            for (int32_t j = 0; j < matrix_.size(); ++j) {
                matrix_[i][j] = pow(e, -((i - center) * (i - center) + (j - center) * (j - center)) * 1.0 / (2 * sigma_ * sigma_)) / (2 * pi * sigma_ * sigma_);
                sum_ += matrix_[i][j];
            }
        }
    } catch (...) {
        throw std::runtime_error("Invalid -blur argument!");
        exit(0);
    }
}

GaussianBlur::GaussianBlur(std::vector <std::string> args) {
    NewArgs(args);
}

void GaussianBlur::ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const {
    int32_t center = matsize_ / 2;
    std::vector <std::vector <Color> > image = pixel_array;
    for (int32_t i = 0; i < pixel_array.size(); ++i) {
        for (int32_t j = 0; j < pixel_array[0].size(); ++j) {
            double res_r = 0;
            double res_g = 0;
            double res_b = 0;
            for (int32_t m_i = 0; m_i < matsize_; ++m_i) {
                for (int32_t m_j = 0; m_j < matsize_; ++m_j) {
                    int delta_x = m_i - center;
                    int delta_y = m_j - center;
                    int X = std::min(static_cast <int32_t> (pixel_array.size()) - 1, std::max(i + delta_x, 0));
                    int Y = std::min(static_cast <int32_t> (pixel_array[0].size()) - 1, std::max(j + delta_y, 0));
                    res_r += static_cast <double> (image[X][Y].R) / 255.0 * matrix_[m_i][m_j];
                    res_g += static_cast <double> (image[X][Y].G) / 255.0 * matrix_[m_i][m_j];
                    res_b += static_cast <double> (image[X][Y].B) / 255.0 * matrix_[m_i][m_j];
                    //std::cout << static_cast <double> (image[X][Y].R) << " : " << matrix_[m_i][m_j] << " " << static_cast <double> (image[X][Y].R) / 255.0 * matrix_[m_i][m_j] << "\n";
                }
            }
            //std::cerr << res_r << " " << res_g << " " << res_b << " : " << sum_ << "\n";
            res_r /= sum_;
            res_g /= sum_;
            res_b /= sum_;
            pixel_array[i][j].R = res_r * 255.0;
            pixel_array[i][j].G = res_g * 255.0;
            pixel_array[i][j].B = res_b * 255.0;
        }
    }
}

void FastGaussianBlur::NewArgs(std::vector <std::string> args) {
    try {
        sigma_ = std::stod(args[0]);
        if (sigma_ < 1e-5) {
            throw std::runtime_error("Invalid -blur argument!");
        }
        matsize_ = sigma_ * 3 * 2 + 1;
        if (matsize_ % 2 == 0) {
            ++matsize_;
        }
        matrix_.resize(matsize_);
        int32_t center = matsize_ / 2;
        double pi = 3.1415926;
        double e = 2.71828;
        for (int32_t i = 0; i < matsize_; ++i) {
            matrix_[i] = pow(e, -(i - center) * (i - center) * 1.0 / (2 * sigma_ * sigma_)) / sqrt(2 * pi * sigma_ * sigma_);
            sum_ += matrix_[i];
        }
    } catch (...) {
        throw std::runtime_error("Invalid -blur argument!");
        exit(0);
    }
}

FastGaussianBlur::FastGaussianBlur(std::vector <std::string> args) {
    NewArgs(args);
}

void FastGaussianBlur::ApplyFilter(std::vector <std::vector <Color> >& pixel_array) const {
    int32_t center = matsize_ / 2;
    std::vector <std::vector <Color> > image = pixel_array;
    for (int32_t i = 0; i < pixel_array.size(); ++i) {
        for (int32_t j = 0; j < pixel_array[i].size(); ++j) {
            double res_r = 0;
            double res_g = 0;
            double res_b = 0;
            for (int32_t k = 0; k < matrix_.size(); ++k) {
                int X = i + (k - center);
                X = std::min(static_cast <int32_t> (pixel_array.size()) - 1, std::max(X, 0));
                res_r += static_cast <double> (image[X][j].R) / 255.0 * matrix_[k];
                res_g += static_cast <double> (image[X][j].G) / 255.0 * matrix_[k];
                res_b += static_cast <double> (image[X][j].B) / 255.0 * matrix_[k];
            }
            res_r /= sum_;
            res_g /= sum_;
            res_b /= sum_;
            pixel_array[i][j].R = res_r * 255.0;
            pixel_array[i][j].G = res_g * 255.0;
            pixel_array[i][j].B = res_b * 255.0;
        }
    }
    image = pixel_array;
    for (int32_t i = 0; i < pixel_array.size(); ++i) {
        for (int32_t j = 0; j < pixel_array[i].size(); ++j) {
            double res_r = 0;
            double res_g = 0;
            double res_b = 0;
            for (int32_t k = 0; k < matrix_.size(); ++k) {
                int Y = j + (k - center);
                Y = std::min(static_cast <int32_t> (pixel_array[0].size()) - 1, std::max(Y, 0));
                res_r += static_cast <double> (image[i][Y].R) / 255.0 * matrix_[k];
                res_g += static_cast <double> (image[i][Y].G) / 255.0 * matrix_[k];
                res_b += static_cast <double> (image[i][Y].B) / 255.0 * matrix_[k];
            }
            res_r /= sum_;
            res_g /= sum_;
            res_b /= sum_;
            pixel_array[i][j].R = res_r * 255.0;
            pixel_array[i][j].G = res_g * 255.0;
            pixel_array[i][j].B = res_b * 255.0;
        }
    }
}