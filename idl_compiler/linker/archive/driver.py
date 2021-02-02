import sys

from idl_compiler.driver import IDLDriver
from idl_compiler.driver_binary_input import IDLDriverBinaryInput
from idl_compiler.driver_binary_output import IDLDriverBinaryOutput
from idl_compiler.linker.archive.linker import IDLArchiveLinker

class IDLArchiveLinkerProcessor:
    def __init__(self):
        pass

    def _process_input_list(self, raw_list):
        result = []

        for raw_item in raw_list:
            wrapper_item = IDLDriverBinaryInput(raw_item)

            result.append(wrapper_item)

        return result

    def process(self, parsed_arguments):
        output_name = parsed_arguments.output

        input_handles_raw = parsed_arguments.input_handle
        input_enumerations_raw = parsed_arguments.input_enumeration
        input_structures_raw = parsed_arguments.input_structure
        input_functions_raw = parsed_arguments.input_function

        binary_inputs = {
            "handles": self._process_input_list(input_handles_raw),
            "enumerations": self._process_input_list(input_enumerations_raw),
            "structures": self._process_input_list(input_structures_raw),
            "functions": self._process_input_list(input_functions_raw),
        }

        binary_output = IDLDriverBinaryOutput(output_name)
        linker = IDLArchiveLinker(binary_output, binary_inputs)

        linker.link()

if __name__ == "__main__":
    processor = IDLArchiveLinkerProcessor()
    driver = IDLDriver(processor)

    driver.arguments.add_argument(
        "--input_handle",
        action="append",
        help="File to read a handle object from for linking into archive.",
    )

    driver.arguments.add_argument(
        "--input_enumeration",
        action="append",
        help="File to read a enumeration object from for linking into archive.",
    )

    driver.arguments.add_argument(
        "--input_structure",
        action="append",
        help="File to read a structure object from for linking into archive.",
    )

    driver.arguments.add_argument(
        "--input_function",
        action="append",
        help="File to read a function object from for linking into archive.",
    )

    status = driver.run()
    if status == False:
        sys.exit(1)

    sys.exit(0)
