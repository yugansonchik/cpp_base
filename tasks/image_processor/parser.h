#include <vector>
#include <string>

class Parser {
public:
    Parser(int argc, char* argv[]);
    std::string InputFile();
    std::string OutputFile();
    std::vector<std::string>GetArgs();

private:
    std::vector<std::string> args_;
    std::string input_file_;
    std::string output_file_;

    void CheckFiles();
    bool ExistsFile(const std::string name) const;
};