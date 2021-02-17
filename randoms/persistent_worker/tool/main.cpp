#include <unistd.h>

#include <iostream>
#include <filesystem>

#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>

#include "src/main/protobuf/worker_protocol.pb.h"

#include "cxxopts.hpp"

using namespace google::protobuf::io;

using namespace blaze::worker;

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

uint32_t ParseMessageLength(CodedInputStream* stream) {
    uint32_t message_length = 0;

    stream->ReadVarint32(&message_length);
    return message_length;
}

WorkRequest* ParseWorkRequest(CodedInputStream* stream, uint32_t length) {
    auto buffer  = new uint8_t[length];
    auto message = new WorkRequest();

    stream->ReadRaw(buffer, length);
    message->ParseFromArray(buffer, length);

    delete[] buffer;
    return message;
}

void Loop() {
    auto options = cxxopts::Options {"worker", "Simple worker"};

    AddExecutionOptions(options);

    while (true) {
        auto raw_input   = new FileInputStream(STDIN_FILENO);
        auto coded_input = new CodedInputStream(raw_input);

        auto message_length = ParseMessageLength(coded_input);
        auto message        = ParseWorkRequest(coded_input, message_length);

        auto work_id        = message->request_id();
        auto argument_count = message->arguments_size();
        auto arguments      = new const char*[argument_count + 1];

        for (auto index = 0; index < argument_count; index++) {
            arguments[index + 1] = message->arguments(index).c_str();
        }

        argument_count++;

        arguments[0] = "worker";

        auto options_result = options.parse(argument_count, arguments);

        auto source      = options_result["source"].as<std::string>();
        auto destination = options_result["destination"].as<std::string>();

        Process(source, destination);

        delete[] arguments;

        delete message;
        delete coded_input;
        delete raw_input;

        auto raw_output   = new FileOutputStream(STDOUT_FILENO);
        auto coded_output = new CodedOutputStream(raw_output);
        auto result       = new WorkResponse();

        result->set_exit_code(0);
        result->set_request_id(work_id);

        auto result_size   = result->ByteSizeLong();
        auto result_buffer = new uint8_t[result_size];

        result->SerializeToArray(result_buffer, result_size);

        coded_output->WriteVarint32(result_size);
        result->SerializeToCodedStream(coded_output);

        delete[] result_buffer;
        delete result;
        delete coded_output;
        delete raw_output;
    }
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
