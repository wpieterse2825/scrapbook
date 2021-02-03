from idl_compiler.shared import *

class IDLDriverBinaryInput:
    input_name = None

    def __init__(self, input_name):
        self.input_name = input_name

    def load(self):
        ensure_file(self.input_name, "Could not open input file %s." % self.input_name)

        with open(self.input_name) as input_file:
            return input_file.read()
