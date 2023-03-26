#include "image_processor.h"

struct ParserResults {
    std::string input_file_path;
    std::string output_file_path;

    std::vector<FilterDefinition> filter_definitions;
};


class ArgParser {
public:
    ParserResults Parse(int argc, const char *argv[]);
    ParserResults result;
};
