#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

#define WAIT_FOR_COMPLETION 1

static int exec_prog(const char** argv) {
    pid_t my_pid;
    int   status, timeout /* unused ifdef WAIT_FOR_COMPLETION */;

    if (0 == (my_pid = fork())) {
        if (-1 == execve(argv[0], (char**)argv, nullptr)) {
            perror("child process execve failed [%m]");
            return -1;
        }
    }

#ifdef WAIT_FOR_COMPLETION
    timeout = 1000;

    while (0 == waitpid(my_pid, &status, WNOHANG)) {
        if (--timeout < 0) {
            perror("timeout");
            return -1;
        }
        sleep(1);
    }

    // printf("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n", argv[0], WEXITSTATUS(status), WIFEXITED(status), status);

    if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
        perror("%s failed, halt system");
        return -1;
    }

#endif
    return 0;
}

int main(int argc, char** argv) {
    bool server = false;

    for (auto index = 0; index < argc; index++) {
        if (!strcmp(argv[index], "--server")) {
            server = true;
        }

        std::cout << argv[index] << std::endl;
    }

    if (server == false) {
        const char* my_argv[64] = {argv[0], "--server", nullptr};

        int rc = exec_prog(my_argv);
    } else {
        std::cout << "Running as server" << std::endl;
    }

    std::cout << std::endl;
    return 0;
}
