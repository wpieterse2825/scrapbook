from tools.idl.compiler.compiler import IDLCompiler

from tools.idl.compiler.structure.protocol_pb2 import Structure

class IDLStructureCompiler(IDLCompiler):
    def __init__(self, compiler_output, compiler_input):
        super().__init__(compiler_output, compiler_input)

        self.output_content = Structure()

    def _read_input(self):
        input_content = self.compiler_input.load()

    def _verify_content(self):
        pass

    def _write_output(self):
        self.compiler_output.save(self.output_content)

    def compile(self):
        self._read_input()
        self._verify_content()
        self._write_output()
