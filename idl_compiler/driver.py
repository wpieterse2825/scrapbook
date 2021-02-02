import sys
from os import write

from argparse import ArgumentParser

from google.protobuf.internal.decoder import _DecodeVarint32
from google.protobuf.internal.encoder import _VarintBytes

from third_party.bazel.worker_protocol_pb2 import WorkRequest
from third_party.bazel.worker_protocol_pb2 import WorkResponse

from idl_compiler.parse_error import IDLParseError

class IDLDriver:
    processor = None
    arguments = None

    def __init__(self, processor):
        self.processor = processor

        self.arguments = ArgumentParser(
            fromfile_prefix_chars='@',
        )

        self.arguments.add_argument(
            "--persistent_worker",
            action="store_true",
            help="If passed, the driver will continue running, accepting work request from the standard input."
        )

        self.arguments.add_argument(
            "--log_level",
            help="Defines the logging level to run the driver at.",
        )

        self.arguments.add_argument(
            "--output",
            help="The location of a file where to write the processed content.",
        )

    def _worker_loop(self):
        while True:
            message_length_raw = sys.stdin.buffer.read(2)
            message_length, message_read = _DecodeVarint32(message_length_raw, 0)

            work_request = WorkRequest()
            work_response = WorkResponse()

            work_request_content = sys.stdin.buffer.read(message_length)
            work_request.ParseFromString(work_request_content)

            parsed_arguments = self.arguments.parse_args(work_request.arguments)

            try:
                self.processor.process(parsed_arguments)
            except IDLParseError as parse_error:
                work_response.output = "Error while processing %s: %s" % (
                    parsed_arguments.output,
                    str(parse_error),
                )

            response_serialized = work_response.SerializeToString()
            response_size = work_response.ByteSize()

            write(1, _VarintBytes(response_size))
            write(1, response_serialized)

    def run(self):
        parsed_arguments = self.arguments.parse_args()
        if parsed_arguments.persistent_worker:
            self._worker_loop()
        else:
            try:
                self.processor.process(parsed_arguments)
            except IDLParseError as parse_error:
                work_response.output = "Error while processing %s: %s" % (
                    parsed_arguments.output,
                    str(parse_error),
                )

        return True
