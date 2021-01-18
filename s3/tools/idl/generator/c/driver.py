import sys

from tools.idl.driver import IDLDriver
from tools.idl.driver_binary_input import IDLDriverBinaryInput
from tools.idl.driver_text_output import IDLDriverTextOutput
from tools.idl.generator.c.generator import IDLCGenerator

class IDLCGeneratorProcessor:
    def __init__(self):
        pass

    def process(self, parsed_arguments):
        output_name = parsed_arguments.output
        input_name = parsed_arguments.input

        text_output = IDLDriverTextOutput(output_name)
        binary_input = IDLDriverBinaryInput(input_name)
        generator = IDLCGenerator(text_output, binary_input)

        generator.generate()

if __name__ == "__main__":
    processor = IDLCGeneratorProcessor()
    driver = IDLDriver(processor)

    driver.arguments.add_argument(
        "--input",
        help="The file containing the content for the tool to process.",
    )

    driver.arguments.add_argument(
        "--handle_prefix",
        help="The file containing the content for the tool to process.",
    )

    driver.arguments.add_argument(
        "--enumeration_prefix",
        help="The file containing the content for the tool to process.",
    )

    driver.arguments.add_argument(
        "--enumeration_item_prefix",
        help="The file containing the content for the tool to process.",
    )

    driver.arguments.add_argument(
        "--structure_prefix",
        help="The file containing the content for the tool to process.",
    )

    driver.arguments.add_argument(
        "--function_prefix",
        help="The file containing the content for the tool to process.",
    )

    status = driver.run()
    if status == False:
        sys.exit(1)

    sys.exit(0)
