from tools.idl.linker.archive.protocol_pb2 import Archive

from tools.idl.generator.generator import IDLGenerator

class IDLCPPGenerator(IDLGenerator):
    def __init__(self, generator_output, generator_input):
        super().__init__(generator_output, generator_input)

        self.output_content = ""

    def _read_inputs(self):
        input_content = self.generator_input.load()

    def _verify_content(self):
        pass

    def _write_output(self):
        self.generator_output.save(self.output_content)

    def generate(self):
        self._read_inputs()
        self._verify_content()
        self._write_output()
