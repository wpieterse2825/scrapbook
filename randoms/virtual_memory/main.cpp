#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <iostream>

void* AllocateBlob(size_t blob_size) {
    return mmap(nullptr, blob_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void DeallocateBlob(void* blob, size_t blob_size) {
    munmap(blob, blob_size);
}

constexpr auto Gigabyte      = size_t {1024 * 1024 * 1024};
constexpr auto LargeBlobSize = size_t {16} * Gigabyte;

struct ActualData {
    char message[256];
};

void MultipleLargeAllocations() {
    auto blob_1 = reinterpret_cast<ActualData*>(AllocateBlob(LargeBlobSize));
    auto blob_2 = reinterpret_cast<ActualData*>(AllocateBlob(LargeBlobSize));
    auto blob_3 = reinterpret_cast<ActualData*>(AllocateBlob(LargeBlobSize));
    auto blob_4 = reinterpret_cast<ActualData*>(AllocateBlob(LargeBlobSize));

    strcpy(blob_1->message, "Blob - 1");
    strcpy(blob_2->message, "Blob - 2");
    strcpy(blob_3->message, "Blob - 3");
    strcpy(blob_4->message, "Blob - 4");

    std::cout << " - " << reinterpret_cast<void*>(blob_1) << " - " << blob_1->message << std::endl;
    std::cout << " - " << reinterpret_cast<void*>(blob_2) << " - " << blob_2->message << std::endl;
    std::cout << " - " << reinterpret_cast<void*>(blob_3) << " - " << blob_3->message << std::endl;
    std::cout << " - " << reinterpret_cast<void*>(blob_4) << " - " << blob_4->message << std::endl;

    DeallocateBlob(blob_4, LargeBlobSize);
    DeallocateBlob(blob_3, LargeBlobSize);
    DeallocateBlob(blob_2, LargeBlobSize);
    DeallocateBlob(blob_1, LargeBlobSize);
}

void MapUnmapRegions() {
    auto blob = reinterpret_cast<uint8_t*>(mmap(nullptr, LargeBlobSize, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));

    std::cout << " - " << reinterpret_cast<void*>(blob) << std::endl;

    mprotect(blob, 4096, PROT_READ | PROT_WRITE);
    auto blob_block_1 = reinterpret_cast<ActualData*>(blob + 0);
    strcpy(blob_block_1->message, "Blob Block 1");
    std::cout << " - " << reinterpret_cast<void*>(blob_block_1) << " - " << blob_block_1->message << std::endl;

    mprotect(blob + 8192, 4096, PROT_READ | PROT_WRITE);
    auto blob_block_2 = reinterpret_cast<ActualData*>(blob + 8192);
    strcpy(blob_block_2->message, "Blob Block 2");
    std::cout << " - " << reinterpret_cast<void*>(blob_block_2) << " - " << blob_block_2->message << std::endl;

    munmap(blob, LargeBlobSize);
}

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "Virtual Memory (Large Allocations):" << std::endl;
    MultipleLargeAllocations();
    std::cout << "==================================================" << std::endl;

    std::cout << std::endl;

    std::cout << "==================================================" << std::endl;
    std::cout << "Virtual Memory (Sparse Regions):" << std::endl;
    MapUnmapRegions();
    std::cout << "==================================================" << std::endl;

    return 0;
}
