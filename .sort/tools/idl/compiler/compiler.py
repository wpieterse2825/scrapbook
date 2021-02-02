import collections

from tools.idl.shared import *

from tools.idl.parse_error import IDLParseError

from tools.idl.compiler.shared_pb2 import TypeReference
from tools.idl.compiler.shared_pb2 import Type

class IDLCompiler:
    def __init__(self, compiler_output, compiler_input):
        self.compiler_output = compiler_output
        self.compiler_input = compiler_input

    def process_type(self, output_content, input_content):
        parsed_keys = []

        ensure_is_dictionary(input_content, "Type definition must be a valid dictionary.")
        ensure_collection_is_not_empty(input_content, "Type definition is empty.")
        for (key, value) in input_content.items():
            ensure_dictionary_key_is_string(key, "Type definition contains a key that is not a valid string.")

            parsed_keys.append(key)
            if key == "name":
                ensure_dictionary_value_is_string(value, "Type name value must be a valid string.")

                output_content.name = value
            elif key == "reference":
                ensure_dictionary_value_is_string(value, "Type reference value must be a valid string.")

                if value == "native":
                    output_content.reference = TypeReference.NATIVE
                elif value == "handle":
                    output_content.reference = TypeReference.HANDLE
                elif value == "enumeration":
                    output_content.reference = TypeReference.ENUMERATION
                elif value == "structure":
                    output_content.reference = TypeReference.STRUCTURE
                elif value == "function":
                    output_content.reference = TypeReference.FUNCTION
                else:
                    raise IDLParseError("Type requires unknown type reference '%s'." % value)
            else:
                raise IDLParseError("Type definition contains unknown key '%s' with value '%s'." % (key, value))

        ensure_key_was_processed(parsed_keys, "reference", "Type definition requires a reference parameter.")
        ensure_key_was_processed(parsed_keys, "name", "Type definition requires a name parameter.")
        if output_content.name[0].isnumeric():
            raise IDLParseError("Type name can't start with numerals.")

    def process_documentation(self, output_content, input_content):
        if input_content == None:
            return

        ensure_is_dictionary(input_content, "Documentation definition must be a valid dictionary.")
        if len(input_content.items()) == 0:
            return

        for (key, value) in input_content.items():
            ensure_dictionary_key_is_string(key, "Documentation definition contains a key that is not a valid string.")
            ensure_dictionary_value_is_string(value, "Documentation definition contains a value that is not a valid string.")

            output_content[key] = value

    def compile(self):
        raise NotImplementedError
