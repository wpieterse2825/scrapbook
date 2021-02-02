import collections

from idl_compiler.shared import *

from idl_compiler.parse_error import IDLParseError

from idl_compiler.compiler.shared_pb2 import TypeReference
from idl_compiler.compiler.shared_pb2 import Type

from idl_compiler.compiler.enumeration.protocol_pb2 import Enumeration
from idl_compiler.compiler.enumeration.protocol_pb2 import EnumerationItem

from idl_compiler.compiler.compiler import IDLCompiler

class IDLEnumerationCompiler(IDLCompiler):
    def __init__(self, compiler_output, compiler_input):
        super().__init__(compiler_output, compiler_input)

        self.compiler_output_content = Enumeration()

    def _process_item(self, output_content, input_content):
        parsed_keys = []

        ensure_is_dictionary(input_content, "Enumeration item definition must be a valid dictionary.")
        ensure_collection_is_not_empty(input_content, "Enumeration item definition is empty.")
        for (key, value) in input_content.items():
            ensure_dictionary_key_is_string(key, "Enumeration item definition contains a key that is not a valid string.")

            parsed_keys.append(key)
            if key == "name":
                ensure_dictionary_value_is_string(value, "Enumeration item name value must be a valid string.")

                output_content.name = value
            elif key == "value":
                ensure_dictionary_value_is_string(value, "Enumeration item value must be a valid string.")

                output_content.value = value
            elif key == "documentation":
                self.process_documentation(output_content.documentation, value)
            else:
                raise IDLParseError("Enumeration item definition contains unknown key '%s' with value '%s'." % (key, value))

        ensure_key_was_processed(parsed_keys, "name", "Enumeration item definition requires a name parameter.")
        ensure_key_was_processed(parsed_keys, "value", "Enumeration item definition requires a value parameter.")

    def _process_item_list(self, output_content, input_content):
        if input_content == None:
            return

        ensure_is_list(input_content, "Enumeration items content must be a valid list.")
        if len(input_content) == 0:
            return

        for input_item in input_content:
            output_item = output_content.add()

            self._process_item(output_item, input_item)

    def _read_input(self):
        parsed_keys = []

        compiler_input_content = self.compiler_input.load()

        ensure_is_dictionary(compiler_input_content, "Enumeration definition must be a valid dictionary.")
        ensure_collection_is_not_empty(compiler_input_content, "Enumeration definition is empty.")
        for (key, value) in compiler_input_content.items():
            ensure_dictionary_key_is_string(key, "Enumeration definition contains a key that is not a valid string.")

            parsed_keys.append(key)
            if key == "name":
                ensure_dictionary_value_is_string(value, "Enumeration name value must be a valid string.")

                self.compiler_output_content.name = value
            elif key == "item_prefix":
                ensure_dictionary_value_is_string(value, "Enumeration item prefix value must be a valid string.")

                self.compiler_output_content.item_prefix = value
            elif key == "items":
                self._process_item_list(self.compiler_output_content.items, value)
            elif key == "type":
                self.process_type(self.compiler_output_content.type, value)
            elif key == "documentation":
                self.process_documentation(self.compiler_output_content.documentation, value)
            else:
                raise IDLParseError("Enumeration definition contains unknown key '%s' with value '%s'." % (key, value))

        ensure_key_was_processed(parsed_keys, "name", "Enumeration definition requires a name parameter.")
        ensure_key_was_processed(parsed_keys, "type", "Enumeration definition requires a type parameter.")

        if self.compiler_output_content.name[0].isnumeric():
            raise IDLParseError("Enumeration name can't start with numerals.")

        if len(self.compiler_output_content.items) > 0:
            enumeration_type_name = self.compiler_output_content.type.name

            for item in self.compiler_output_content.items:
                item_value = item.value

                ensure_native_type_value_is_valid(enumeration_type_name, item_value)

    def _write_output(self):
        self.compiler_output.save(self.compiler_output_content)

    def compile(self):
        self._read_input()
        self._write_output()
