import collections

from idl_compiler.shared import *

from idl_compiler.parse_error import IDLParseError

from idl_compiler.compiler.compiler import IDLCompiler

from idl_compiler.compiler.handle.protocol_pb2 import Handle

class IDLHandleCompiler(IDLCompiler):
    def __init__(self, compiler_output, compiler_input):
        super().__init__(compiler_output, compiler_input)

        self.compiler_output_content = Handle()

    def _read_input(self):
        parsed_keys = []

        compiler_input_content = self.compiler_input.load()

        ensure_is_dictionary(compiler_input_content, "Handle definition must be a valid dictionary.")
        ensure_collection_is_not_empty(compiler_input_content, "Handle definition is empty.")
        for (key, value) in compiler_input_content.items():
            ensure_dictionary_key_is_string(key, "Handle definition contains a key that is not a valid string.")

            parsed_keys.append(key)
            if key == "name":
                ensure_dictionary_value_is_string(value, "Handle name value must be a valid string.")

                self.compiler_output_content.name = value
            elif key == "documentation":
                self.process_documentation(self.compiler_output_content.documentation, value)
            else:
                raise IDLParseError("Handle definition contains unknown key '%s' with value '%s'." % (key, value))

        ensure_key_was_processed(parsed_keys, "name", "Handle definition requires a name parameter.")
        if self.compiler_output_content.name[0].isnumeric():
            raise IDLParseError("Handle name can't start with numerals.")

    def _write_output(self):
        self.compiler_output.save(self.compiler_output_content)

    def compile(self):
        self._read_input()
        self._write_output()
