#include "parser.h"


bool IsInt(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

bool IsFloat(const std::string& str)
{
    char* ptr;
    strtof(str.c_str(), &ptr);
    return (*ptr) == '\0';
}

ParserResults ArgParser::Parse(int argc, const char *argv[]) {


    if (argc == 1) {
        throw std::invalid_argument("Please enter names of files to be read from and to be written to.");
    } else if (argc == 2) {
        throw std::invalid_argument("Please enter the name of file to be written to.");
    }

    result.input_file_path = argv[1];
    result.output_file_path = argv[2];

    FilterDefinition new_filter;
    if (argc > 3) {
        for (int i = 3; i != argc; ++i) {
            if (filters.find(argv[i]) != filters.end() and i == 3) {
                new_filter.name = argv[i];
            } else if (filters.find(argv[i]) != filters.end()) {
                result.filter_definitions.push_back(new_filter);
                new_filter.Clear();
                new_filter.name = argv[i];
            } else if (!IsInt(argv[i]) and !IsFloat(argv[i])) {
                throw std::invalid_argument(std::string("There is no such filter: ") +
                                            argv[i] + ", please try again \n" + ENQUIRY);
            } else {
                new_filter.params.push_back(argv[i]);
            }
        }
        result.filter_definitions.push_back(new_filter);

        for (auto filter : result.filter_definitions) {
            if (filters.at(filter.name) != filter.params.size()) {
                throw std::invalid_argument(std::string("Impossible number of arguments for the filter: ")
                                            + filter.name + ", please try again \n" + ENQUIRY);
            }
        }

        for (auto filter : result.filter_definitions) {
            if (filter.name == "-crop") {
                if (!IsInt(filter.params[0]) or !IsInt(filter.params[1])) {
                    throw std::invalid_argument("Only integer arguments can be entered"
                                                " for the filter -crop, please try again \n" + ENQUIRY);
                }
            }
        }

    }

    return result;
}