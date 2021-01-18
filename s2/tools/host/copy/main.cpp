#include <filesystem>

#include "absl/flags/parse.h"
#include "absl/flags/flag.h"

ABSL_FLAG(std::string, input, "", "Path to input file");
ABSL_FLAG(std::string, output, "", "Path to output file");

int main(int argument_count, char** arguments) {
    auto extra_arguments = absl::ParseCommandLine(argument_count, arguments);
    auto input_file      = absl::GetFlag(FLAGS_input);
    auto output_file      = absl::GetFlag(FLAGS_output);

    std::filesystem::copy(input_file, output_file, std::filesystem::copy_options::overwrite_existing);

    return 0;
}
