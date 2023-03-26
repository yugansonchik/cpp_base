//
// Created by ugans on 3/26/2023.
//

#include "parser.h"
#include <unistd.h>
#include <iostream>
#include <fstream>

Parser::Parser(int argc, char* argv[]) {
    try {
        for (int i = 1; i < argc; ++i) {
            args_.push_back(argv[i]);
        }
        input_file_ = args_[0];
        output_file_ = args_[1];
    } catch (...) {
        std::cout << "Invalid arguments!\n";
        exit(0);
    }
    CheckFiles();
}

void Parser::CheckFiles() {
    try{
        if (!ExistsFile(static_cast<std::string> (input_file_))) {
            throw std::runtime_error("Input file does not exists!");
        }
        if (ExistsFile(static_cast<std::string> (output_file_))) {
            throw std::runtime_error("Output file already exists!");
        }
        std::ofstream fout(static_cast<std::string> (output_file_));
        if (!fout.good()) {
            throw std::runtime_error("Output file is unaccessible!");
        }
        fout.close();
    } catch (const std::exception& e) {
        std::cerr << e.what();
        exit(0);
    }
}

bool Parser::ExistsFile(const std::string name) const {
    return ( access( name.c_str(), F_OK ) != -1 );
}

std::string Parser::InputFile() {
    return this->input_file_;
}

std::string Parser::OutputFile() {
    return this->output_file_;
}

std::vector <std::string> Parser::GetArgs() {
    return this->args_;
}