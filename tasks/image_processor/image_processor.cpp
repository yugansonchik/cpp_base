#include "parser.h"
#include "reader.h"
#include "writer.h"
#include "filters_factory.h"

int main(int argc, const char *argv[]) {
    try {
        ArgParser input;
        input.ArgParser::Parse(argc, argv);
        Reader information = Reader(input.result.input_file_path, Image(0, 0));
        Image image = information.image_;

        auto vec = CreateFilters(input.result.filter_definitions);
        for (auto filter : vec) {
            Filter& fil = *filter.get();
            fil.Apply(image);
        }

        Writer(input.result.output_file_path, image);

    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}