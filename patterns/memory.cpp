#include <string.h>
#include <sys/mman.h>

#include <iostream>

void* Allocate(size_t blob_size) {
    return mmap(nullptr, blob_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void Deallocate(void* blob, size_t blob_size) {
    munmap(blob, blob_size);
}

/// The actual place where data will be stored.
struct ActualData {
    /// Contains the message to print.
    char message[256];

    /// @brief A simple free standing message to test.
    ///
    /// That it really works.
    ///
    /// @param[in] value_1 The first value to add.
    /// @param[in] value_2 The second value to add.
    ///
    /// @returns The result of having \a value_1 added to \a value_2.
    ///
    static uint8_t BuildMessage(const uint8_t value_1, const uint8_t value_2) {
        return value_1 + value_2;
    }
};

int main() {
    auto blob_size = size_t {1ULL << 30} * 16;
    auto blob_1    = Allocate(blob_size);
    auto blob_2    = Allocate(blob_size);
    auto blob_3    = Allocate(blob_size);
    auto blob_4    = Allocate(blob_size);

    auto actual_1 = (ActualData*)blob_1;
    strcpy(actual_1->message, "Hello, World");
    std::cout << blob_1 << " - " << actual_1->message << std::endl;

    auto actual_2 = (ActualData*)blob_2;
    strcpy(actual_2->message, "Hello, World");
    std::cout << blob_2 << " - " << actual_2->message << std::endl;

    auto actual_3 = (ActualData*)blob_3;
    strcpy(actual_3->message, "Hello, World");
    std::cout << blob_3 << " - " << actual_3->message << std::endl;

    auto actual_4 = (ActualData*)blob_4;
    strcpy(actual_4->message, "Hello, World");
    std::cout << blob_4 << " - " << actual_4->message << std::endl;

    auto bb_size = size_t {1ULL << 30} * 256;
    auto bb      = (uint8_t*)mmap(nullptr, bb_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    std::cout << (void*)bb << std::endl;

    mprotect(bb, 4096, PROT_READ | PROT_WRITE);
    auto actual_bb_1 = (ActualData*)bb;
    strcpy(actual_bb_1->message, "It Works");
    std::cout << actual_bb_1->message << std::endl;

    mprotect(bb + 8192, 4096, PROT_READ | PROT_WRITE);
    auto actual_bb_2 = (ActualData*)(bb + 8192);
    strcpy(actual_bb_2->message, "It Works Again");
    std::cout << actual_bb_2->message << std::endl;

    // while(true);

    Deallocate(blob_4, blob_size);
    Deallocate(blob_3, blob_size);
    Deallocate(blob_2, blob_size);
    Deallocate(blob_1, blob_size);

    munmap(bb, bb_size);

    return 0;
}

// 1Gbps = 1000000000 bits
//       = 125000000 bytes
//       = 119 megabytes p/s
//
// Buffer for 60 seconds
//  = 7 gigabytes
//
