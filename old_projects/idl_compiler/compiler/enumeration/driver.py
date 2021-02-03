import sys

from idl_compiler.driver import IDLDriver
from idl_compiler.driver_text_input import IDLDriverTextInput
from idl_compiler.driver_binary_output import IDLDriverBinaryOutput
from idl_compiler.compiler.enumeration.compiler import IDLEnumerationCompiler

class IDLEnumerationCompilerProcessor:
    def __init__(self):
        pass

    def process(self, parsed_arguments):
        output_name = parsed_arguments.output
        input_name = parsed_arguments.input

        binary_output = IDLDriverBinaryOutput(output_name)
        text_input = IDLDriverTextInput(input_name)
        compiler = IDLEnumerationCompiler(binary_output, text_input)

        compiler.compile()

if __name__ == "__main__":
    processor = IDLEnumerationCompilerProcessor()
    driver = IDLDriver(processor)

    driver.arguments.add_argument(
        "--input",
        help="The file containing the content for the tool to process.",
    )

    status = driver.run()
    if status == False:
        sys.exit(1)

    sys.exit(0)
