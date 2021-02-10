#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include <iostream>

#include <liburing.h>

typedef void (*OperationCallback)(io_uring* ring, signed int result, void* user_data);

struct Operation {
    OperationCallback callback;
    void* user_data;
};

void OpenReadComplete(io_uring* ring, signed int result, void* user_data) {
    std::cout << "READ : " << result << std::endl;
}

void QueueOpenRead(io_uring* ring, const char* filename) {
    auto entry = io_uring_get_sqe(ring);

    Operation* op = (Operation*)malloc(sizeof(Operation));
    op->callback = OpenReadComplete;
    op->user_data = nullptr;

    io_uring_prep_openat(entry, AT_FDCWD, filename, 0, O_RDONLY);
    io_uring_sqe_set_data(entry, op);
}

void OpenWriteComplete(io_uring* ring, signed int result, void* user_data) {
    std::cout << "WRITE : " << result << std::endl;
}

void QueueOpenWrite(io_uring* ring, const char* filename) {
    auto entry = io_uring_get_sqe(ring);

    Operation* op = (Operation*)malloc(sizeof(Operation));
    op->callback = OpenWriteComplete;
    op->user_data = nullptr;

    io_uring_prep_openat(entry, AT_FDCWD, filename, O_CREAT | O_TRUNC, O_WRONLY);
    io_uring_sqe_set_data(entry, op);
}

void QueueInitialOperations(io_uring* ring) {
    QueueOpenWrite(ring, "output.bin");
    QueueOpenRead(ring, "randoms/wadder/input_1.txt");
    QueueOpenRead(ring, "randoms/wadder/input_2.txt");

    io_uring_submit(ring);
}

int main(int argc, char* argv[]) {
    io_uring ring;

    io_uring_queue_init(64, &ring, 0);

    QueueInitialOperations(&ring);

    while (true) {
        io_uring_cqe* completion        = nullptr;
        int           completion_result = io_uring_wait_cqe(&ring, &completion);

        if(completion_result < 0) {
            perror("io_uring_wait_cqe");
            return 1;
        }

        Operation* op = (Operation*)io_uring_cqe_get_data(completion);
        op->callback(&ring, completion->res, op->user_data);
        free(op);

        io_uring_cqe_seen(&ring, completion);
    }

    io_uring_queue_exit(&ring);
    return 0;
}
