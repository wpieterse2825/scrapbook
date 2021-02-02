from tools.idl.linker.linker import IDLLinker

from tools.idl.linker.archive.protocol_pb2 import Archive

class IDLArchiveLinker(IDLLinker):
    def __init__(self, linker_output, linker_inputs):
        super().__init__(linker_output, linker_inputs)

        self.output_content = Archive()

    def _read_inputs(self):
        for (input_type, input_items) in self.linker_inputs.items():
            for input_item in input_items:
                input_content = input_item.load()

    def _verify_content(self):
        pass

    def _write_output(self):
        self.linker_output.save(self.output_content)

    def link(self):
        self._read_inputs()
        self._verify_content()
        self._write_output()
