import unittest

from idl_compiler.parse_error import IDLParseError

from idl_compiler.compiler.shared_pb2 import TypeReference
from idl_compiler.compiler.shared_pb2 import Type

from idl_compiler.compiler.compiler import IDLCompiler

class TestCompilerType(unittest.TestCase):
    TEST_PARSE_NAME_CORRECT={
        "reference": "native",
        "name": "NativeType",
    }

    def test_parse_name_correct(self):
        output_content = self._compile(self.TEST_PARSE_NAME_CORRECT)

        self.assertEqual("NativeType", output_content.name)

    TEST_PARSE_NATIVE_REFERENCE={
        "reference": "native",
        "name": "TestType",
    }

    def test_parse_native_reference(self):
        output_content = self._compile(self.TEST_PARSE_NATIVE_REFERENCE)

        self.assertEqual("TestType", output_content.name)
        self.assertEqual(TypeReference.NATIVE, output_content.reference)

    TEST_PARSE_HANDLE_REFERENCE={
        "reference": "handle",
        "name": "TestType",
    }

    def test_parse_handle_reference(self):
        output_content = self._compile(self.TEST_PARSE_HANDLE_REFERENCE)

        self.assertEqual("TestType", output_content.name)
        self.assertEqual(TypeReference.HANDLE, output_content.reference)

    TEST_PARSE_ENUMERATION_REFERENCE={
        "reference": "enumeration",
        "name": "TestType",
    }

    def test_parse_enumeration_reference(self):
        output_content = self._compile(self.TEST_PARSE_ENUMERATION_REFERENCE)

        self.assertEqual("TestType", output_content.name)
        self.assertEqual(TypeReference.ENUMERATION, output_content.reference)

    TEST_PARSE_STRUCTURE_REFERENCE={
        "reference": "structure",
        "name": "TestType",
    }

    def test_parse_structure_reference(self):
        output_content = self._compile(self.TEST_PARSE_STRUCTURE_REFERENCE)

        self.assertEqual("TestType", output_content.name)
        self.assertEqual(TypeReference.STRUCTURE, output_content.reference)

    TEST_PARSE_FUNCTION_REFERENCE={
        "reference": "function",
        "name": "TestType",
    }

    def test_parse_function_reference(self):
        output_content = self._compile(self.TEST_PARSE_FUNCTION_REFERENCE)

        self.assertEqual("TestType", output_content.name)
        self.assertEqual(TypeReference.FUNCTION, output_content.reference)

    TEST_FAIL_INPUT_MUST_NOT_BE_NONE=None

    def test_fail_input_must_not_be_none(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_NOT_BE_NONE)

        self.assertEqual("Type definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_INTEGER=1234

    def test_fail_input_must_be_dictionary_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_INTEGER)

        self.assertEqual("Type definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_STRING="bob"

    def test_fail_input_must_be_dictionary_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_STRING)

        self.assertEqual("Type definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_LIST=[
        "a",
        "b",
    ]

    def test_fail_input_must_be_dictionary_list(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_LIST)

        self.assertEqual("Type definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_CONTAIN_ITEMS={}

    def test_fail_input_must_contain_items(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_CONTAIN_ITEMS)

        self.assertEqual("Type definition is empty.", str(context.exception))

    TEST_FAIL_KEY_MUST_BE_STRING={
        "reference": "native",
        123: "TestType",
    }

    def test_fail_key_must_be_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_KEY_MUST_BE_STRING)

        self.assertEqual("Type definition contains a key that is not a valid string.", str(context.exception))

    TEST_FAIL_KEY_MUST_NOT_BE_EMPTY_STRING={
        "reference": "native",
        "": "TestType",
    }

    def test_fail_key_must_not_be_empty_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_KEY_MUST_NOT_BE_EMPTY_STRING)

        self.assertEqual("Type definition contains a key that is not a valid string.", str(context.exception))

    TEST_FAIL_WITH_UNKNOWN_KEY={
        "reference": "native",
        "name": "TestType",
        "beeb": "boob",
    }

    def test_fail_with_unknown_key(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_WITH_UNKNOWN_KEY)

        self.assertEqual("Type definition contains unknown key 'beeb' with value 'boob'.", str(context.exception))

    TEST_FAIL_REFERENCE_IS_REQUIRED={
        "name": "TestType",
    }

    def test_fail_reference_is_required(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_REFERENCE_IS_REQUIRED)

        self.assertEqual("Type definition requires a reference parameter.", str(context.exception))

    TEST_FAIL_REFERENCE_STRING_MUST_NOT_BE_EMPTY={
        "reference": "",
        "name": "TestType",
    }

    def test_fail_reference_string_must_not_be_empty(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_REFERENCE_STRING_MUST_NOT_BE_EMPTY)

        self.assertEqual("Type reference value must be a valid string.", str(context.exception))

    TEST_FAIL_REFERENCE_MUST_BE_STRING_INTEGER={
        "reference": 123,
        "name": "TestType",
    }

    def test_fail_reference_must_be_string_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_REFERENCE_MUST_BE_STRING_INTEGER)

        self.assertEqual("Type reference value must be a valid string.", str(context.exception))

    TEST_FAIL_REFERENCE_MUST_BE_STRING_LIST={
        "reference": [
            "a",
            "b",
        ],
        "name": "TestType",
    }

    def test_fail_reference_must_be_string_list(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_REFERENCE_MUST_BE_STRING_LIST)

        self.assertEqual("Type reference value must be a valid string.", str(context.exception))

    TEST_FAIL_REFERENCE_MUST_BE_STRING_DICTIONARY={
        "reference": {
            "beeb": "boob",
        },
        "name": "TestType",
    }

    def test_fail_reference_must_be_string_dictionary(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_REFERENCE_MUST_BE_STRING_DICTIONARY)

        self.assertEqual("Type reference value must be a valid string.", str(context.exception))

    TEST_FAIL_WITH_UNKNOWN_REFERENCE={
        "reference": "thingamabob",
        "name": "TestType",
    }

    def test_fail_with_unknown_reference(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_WITH_UNKNOWN_REFERENCE)

        self.assertEqual("Type requires unknown type reference 'thingamabob'.", str(context.exception))

    TEST_FAIL_NAME_IS_REQUIRED={
        "reference": "native",
    }

    def test_fail_name_is_required(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_IS_REQUIRED)

        self.assertEqual("Type definition requires a name parameter.", str(context.exception))

    TEST_FAIL_NAME_STRING_MUST_NOT_BE_EMPTY={
        "reference": "native",
        "name": "",
    }

    def test_fail_name_string_must_not_be_empty(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_STRING_MUST_NOT_BE_EMPTY)

        self.assertEqual("Type name value must be a valid string.", str(context.exception))

    TEST_FAIL_NAME_MUST_BE_STRING_INTEGER={
        "reference": "native",
        "name": "1234",
    }

    def test_fail_name_must_be_string_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_INTEGER)

        self.assertEqual("Type name can't start with numerals.", str(context.exception))

    TEST_FAIL_NAME_MUST_BE_STRING_LIST={
        "reference": "native",
        "name": [
            "a",
            "b",
        ],
    }

    def test_fail_name_must_be_string_list(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_LIST)

        self.assertEqual("Type name value must be a valid string.", str(context.exception))

    TEST_FAIL_NAME_MUST_BE_STRING_DICTIONARY={
        "reference": "native",
        "name": {
            "beeb": "boob",
        },
    }

    def test_fail_name_must_be_string_dictionary(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_DICTIONARY)

        self.assertEqual("Type name value must be a valid string.", str(context.exception))

    TEST_FAIL_NAME_CAN_NOT_START_WITH_INTEGER={
        "reference": "native",
        "name": "1TestType",
    }

    def test_fail_name_can_not_start_with_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_CAN_NOT_START_WITH_INTEGER)

        self.assertEqual("Type name can't start with numerals.", str(context.exception))

    def _compile(self, input_content):
        compiler = IDLCompiler("output", "input")
        output_content = Type()

        compiler.process_type(output_content, input_content)

        return output_content

if __name__ == "__main__":
    unittest.main()
