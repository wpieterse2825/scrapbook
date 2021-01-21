import sys

from tools.idl.driver import IDLDriver
from tools.idl.driver_text_input import IDLDriverTextInput
from tools.idl.driver_binary_output import IDLDriverBinaryOutput
from tools.idl.compiler.handle.compiler import IDLHandleCompiler

class IDLHandleCompilerProcessor:
    def __init__(self):
        pass

    def process(self, parsed_arguments):
        output_name = parsed_arguments.output
        input_name = parsed_arguments.input

        binary_output = IDLDriverBinaryOutput(output_name)
        text_input = IDLDriverTextInput(input_name)
        compiler = IDLHandleCompiler(binary_output, text_input)

        compiler.compile()

if __name__ == "__main__":
    processor = IDLHandleCompilerProcessor()
    driver = IDLDriver(processor)

    driver.arguments.add_argument(
        "--input",
        help="The file containing the content for the tool to process.",
    )

    status = driver.run()
    if status == False:
        sys.exit(1)

    sys.exit(0)
