#include <iostream>

#include "parser.h"
#include "bmp.h"
#include "processor.h"
//#include "filter.h"

void get_filter(const Filter& fl) {
    fl.FilterName();
}

int main(int argc, char* argv[]) {
    Parser p(argc, argv);
    BMP bmp(p.InputFile());
    Processor proc(p.GetArgs(), bmp);
    bmp.Write(p.OutputFile());
    return 0;
}
