#include <unistd.h>

#include <iostream>
#include <filesystem>

#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>

#include "src/main/protobuf/worker_protocol.pb.h"

#include "stuff/taskflow/taskflow.hpp"

#include "stuff/cxxopts/cxxopts.hpp"

using namespace google::protobuf::io;

using namespace blaze::worker;

using namespace tf;

struct T1Task {
    const char* message;

    T1Task(const char* message)
      : message {message} {
    }

    void operator()() {
        std::cout << this->message << std::endl;
    }
};

struct T2P1Task {
    const char* message;

    T2P1Task(const char* message)
      : message {message} {
    }

    void operator()() {
        std::cout << this->message << std::endl;
    }
};

struct T2P2Task {
    const char* message;

    T2P2Task(const char* message)
      : message {message} {
    }

    void operator()() {
        std::cout << this->message << std::endl;
    }
};

struct T3Task {
    const char* message;

    T3Task(const char* message)
      : message {message} {
    }

    void operator()() {
        std::cout << this->message << std::endl;
    }
};

struct TFinish {
    void operator()() {
        std::cout << "Finished" << std::endl;
    }
};

/*
int main() {
    Executor executor;
    Taskflow taskflow;

    auto task_1 = taskflow.emplace(T1Task{"Hello, World 1"});
    task_1.name("task_1");

    auto task_2_p1 = taskflow.emplace(T2P1Task{"Hello, World 2"});
    task_2_p1.name("task_2_p1");

    auto task_2_p2 = taskflow.emplace(T2P2Task{"Hello, World 3"});
    task_2_p2.name("task_2_p2");

    auto task_3 = taskflow.emplace(T3Task{"Hello, World 4"});
    task_3.name("task_3");

    task_1.precede(task_2_p1);
    task_1.precede(task_2_p2);
    task_2_p1.precede(task_3);
    task_2_p2.precede(task_3);

    auto future = executor.run(taskflow, TFinish{});

    future.wait();
    return 0;
}
*/

void Process(const std::string& input_file, const std::string& output_file) {
    std::filesystem::copy(input_file, output_file, std::filesystem::copy_options::overwrite_existing);
}

void AddWorkerOptions(cxxopts::Options& options) {
    options.add_option("", "p", "persistent_worker", "Enable worker mode", cxxopts::value<bool>()->default_value("false"), "");
}

void AddExecutionOptions(cxxopts::Options& options) {
    options.add_option("", "s", "source", "Source file", cxxopts::value<std::string>(), "");
    options.add_option("", "d", "destination", "Destination file", cxxopts::value<std::string>(), "");
}

void Loop() {
    auto options = cxxopts::Options {"worker", "Simple worker"};

    AddExecutionOptions(options);

    auto raw_input    = new FileInputStream(STDIN_FILENO);
    auto coded_input  = new CodedInputStream(raw_input);
    auto raw_output   = new FileOutputStream(STDOUT_FILENO);
    auto coded_output = new CodedOutputStream(raw_output);

    while (true) {
        uint32_t message_length = 0;
        coded_input->ReadVarint32(&message_length);

        const void* data = nullptr;
        int         size = 0;
        if (coded_input->GetDirectBufferPointer(&data, &size)) {
            // std::cout << "MY DATA IS AT " << data << " AND THE SIZE IS " << size << std::endl;
            // std::cout << std::endl;
        } else {
            std::cout << "FAIL! FAIL! FAIL! Read buffer pointer." << std::endl;
        }

        if (message_length > size) {
            std::cout << "FAIL! FAIL! FAIL" << std::endl;
        }

        auto message = new WorkRequest();

        message->ParseFromArray(data, message_length);
        coded_input->Skip(message_length);

        for (auto input : message->inputs()) {
            // std::cout << input.path() << " - " << input.digest() << std::endl;
        }

        auto work_id        = message->request_id();
        auto argument_count = message->arguments_size();
        auto arguments      = new const char*[argument_count + 1];

        for (auto index = 0; index < argument_count; index++) {
            arguments[index + 1] = message->arguments(index).c_str();
        }

        argument_count++;

        arguments[0] = "worker";

        auto options_result = options.parse(argument_count, arguments);
        auto source         = options_result["source"].as<std::string>();
        auto destination    = options_result["destination"].as<std::string>();

        Process(source, destination);

        delete[] arguments;
        delete message;

        auto result = new WorkResponse();

        result->set_exit_code(0);
        result->set_request_id(work_id);
        result->set_output("Hello, World\n\n");

        auto result_size = result->ByteSizeLong();
        coded_output->WriteVarint32(result_size);

        void* unconst_data = nullptr;
        if (coded_output->GetDirectBufferPointer(&unconst_data, &size)) {
            // std::cout << "MY DATA IS AT " << data << " AND THE SIZE IS " << size << std::endl;
            // std::cout << std::endl;
        } else {
            std::cout << "FAIL! FAIL! FAIL! Write buffer pointer." << std::endl;
        }

        if (result_size > size) {
            std::cout << "FAIL! FAIL! FAIL" << std::endl;
        }

        result->SerializeToArray(unconst_data, result_size);
        coded_output->Skip(result_size);

        delete result;

        raw_output->Flush();
    }

    delete coded_output;
    delete raw_output;
    delete coded_input;
    delete raw_input;
}

int main(int argument_count, const char** arguments) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    auto options = cxxopts::Options {"worker", "Simple worker"};

    AddWorkerOptions(options);
    AddExecutionOptions(options);

    auto options_result = options.parse(argument_count, arguments);

    const auto is_persistent = options_result["persistent_worker"].as<bool>();
    if (is_persistent == true) {
        Loop();
    } else {
        auto source      = options_result["source"].as<std::string>();
        auto destination = options_result["destination"].as<std::string>();

        Process(source, destination);
    }

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
