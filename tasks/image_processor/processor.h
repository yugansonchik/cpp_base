//
// Created by ugans on 3/26/2023.
//

#ifndef CPP_HSE_PROCESSOR_H
#define CPP_HSE_PROCESSOR_H

#endif  // CPP_HSE_PROCESSOR_H







#pragma once
#include <vector>
#include <unordered_map>

#include "base_filters.h"
#include "bmp.h"

class Processor {
public:
    Processor(std::vector <std::string> args, BMP& bmp) {
        try{
            Filter *crop = new Crop(); filter_["-crop"] = crop; arg_count_["-crop"] = 2;
            Filter *grayscale = new Grayscale(); filter_["-gs"] = grayscale;  arg_count_["-gs"] = 0;
            Filter *neg = new Negative(); filter_["-neg"] = neg;  arg_count_["-neg"] = 0;
            Filter *sharp = new Sharp(); filter_["-sharp"] = sharp;   arg_count_["-sharp"] = 0;
            Filter *edge = new EdgeDetection(); filter_["-edge"] = edge; arg_count_["-edge"] = 1;
            Filter *blur = new FastGaussianBlur(); filter_["-blur"] = blur;  arg_count_["-blur"] = 1;
            for (size_t i = 2; i < args.size(); ++i) {
                if (!filter_.count(args[i])) {
                    throw std::runtime_error("Invalid arguments1!");
                }
                std::string filter_name = args[i];
                int32_t cnt = arg_count_[filter_name];
                std::vector <std::string> curr_args;
                while (cnt--) {
                    ++i;
                    if (i >= args.size()) {
                        throw std::runtime_error("Invalid arguments!");
                    }
                    curr_args.push_back(args[i]);
                }
                if (arg_count_[filter_name]) {
                    filter_[filter_name]->NewArgs(curr_args);
                }
                bmp.ApplyFilter(*filter_[filter_name]);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what();
            exit(0);
        }
    }
private:
    std::unordered_map <std::string, Filter*> filter_;
    std::unordered_map <std::string, int32_t> arg_count_;
};