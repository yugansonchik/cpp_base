//
// Created by ugans on 3/26/2023.
//

#ifndef CPP_HSE_PARSER_H
#define CPP_HSE_PARSER_H

#endif  // CPP_HSE_PARSER_H




#include <vector>
#include <string>

class Parser {
public:
    Parser(int argc, char* argv[]);
    std::string InputFile();
    std::string OutputFile();
    std::vector <std::string> GetArgs();

private:
    std::vector <std::string> args_;
    std::string input_file_;
    std::string output_file_;

    void CheckFiles();
    bool ExistsFile (const std::string name) const;
};