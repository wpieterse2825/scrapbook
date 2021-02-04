#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

int main(int argument_count, char** arguments) {
    std::string               runfiles_error {""};
    std::unique_ptr<Runfiles> runfiles {Runfiles::Create(arguments[0], &runfiles_error)};

    std::cout << "DOOM WAD Information:" << std::endl;

    if (runfiles == nullptr) {
        std::cout << "ERROR: Failed to initialize run-files : " << runfiles_error << std::endl;
        return 1;
    }

    std::cout << runfiles->Rlocation("scrapbook/game_tools/data/doom/DOOM.WAD") << std::endl;

    return 0;
}
