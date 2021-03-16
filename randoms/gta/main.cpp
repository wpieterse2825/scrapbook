#include <stdint.h>
#include <stdio.h>

#include <iostream>

int main() {
    FILE* common = fopen("common.rpf", "rb");
    if (common == nullptr) {
        std::cout << "ERROR: Failed to open file." << std::endl;

        return 1;
    }

    uint32_t version      = 0;
    uint32_t entry_count  = 0;
    uint32_t names_length = 0;
    uint32_t encryption   = 0;

    fread(&version, sizeof(uint32_t), 1, common);
    fread(&entry_count, sizeof(uint32_t), 1, common);
    fread(&names_length, sizeof(uint32_t), 1, common);
    fread(&encryption, sizeof(uint32_t), 1, common);

    std::cout << "Version      : 0x" << std::hex << version << std::dec << std::endl;
    std::cout << "Entry Count  : " << entry_count << std::endl;
    std::cout << "Names Length : " << names_length << std::endl;
    std::cout << "Encryption   : " << encryption << std::endl;

    fclose(common);

    return 0;
}
