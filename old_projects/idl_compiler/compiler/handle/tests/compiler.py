import unittest

from idl_compiler.parse_error import IDLParseError

from idl_compiler.compiler.tests.shared import TestCompilerBinaryOutput
from idl_compiler.compiler.tests.shared import TestCompilerTextInput

from idl_compiler.compiler.handle.protocol_pb2 import Handle

from idl_compiler.compiler.handle.compiler import IDLHandleCompiler

class TestCompiler(unittest.TestCase):
    TEST_NAME_ONLY={
        "name": "Device",
    }

    def test_name_only(self):
        output_content = self._compile(self.TEST_NAME_ONLY)

        self.assertEqual("Device", output_content.name)

    TEST_NAME_CAN_CONTAINER_NUMBERS={
        "name": "D123",
    }

    def test_name_can_contain_numbers(self):
        output_content = self._compile(self.TEST_NAME_CAN_CONTAINER_NUMBERS)

        self.assertEqual("D123", output_content.name)

    TEST_NAME_WITH_DOCUMENTATION={
        "name": "Device",
        "documentation": {
            "english": "Hello, World",
        },
    }

    def test_name_with_documentation(self):
        output_content = self._compile(self.TEST_NAME_WITH_DOCUMENTATION)

        self.assertEqual("Device", output_content.name)
        self.assertEqual(1, len(output_content.documentation.items()))

    TEST_FAIL_INPUT_MUST_NOT_BE_NONE=None

    def test_fail_input_must_not_be_none(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_NOT_BE_NONE)

        self.assertEqual("Handle definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_INTEGER=1234

    def test_fail_input_must_be_dictionary_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_INTEGER)

        self.assertEqual("Handle definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_STRING="beeb"

    def test_fail_input_must_be_dictionary_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_STRING)

        self.assertEqual("Handle definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_LIST=[
        "a",
        "b",
    ]

    def test_fail_input_must_be_dictionary_list(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_LIST)

        self.assertEqual("Handle definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_CONTAIN_ITEMS={}

    def test_fail_input_must_contain_items(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_CONTAIN_ITEMS)

        self.assertEqual("Handle definition is empty.", str(context.exception))

    TEST_FAIL_KEY_MUST_BE_STRING={
        123: "Device",
    }

    def test_fail_key_must_be_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_KEY_MUST_BE_STRING)

        self.assertEqual("Handle definition contains a key that is not a valid string.", str(context.exception))

    TEST_FAIL_KEY_MUST_NOT_BE_EMPTY_STRING={
        "": "Device",
    }

    def test_fail_key_must_not_be_empty_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_KEY_MUST_NOT_BE_EMPTY_STRING)

        self.assertEqual("Handle definition contains a key that is not a valid string.", str(context.exception))

    TEST_FAIL_WITH_UNKNOWN_KEY={
        "name": "Device",
        "beeb": "boob",
    }

    def test_fail_with_unknown_key(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_WITH_UNKNOWN_KEY)

        self.assertEqual("Handle definition contains unknown key 'beeb' with value 'boob'.", str(context.exception))

    TEST_FAIL_NAME_IS_REQUIRED={
        "documentation": {
            "english": "Hello, World",
        },
    }

    def test_fail_name_is_required(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_IS_REQUIRED)

        self.assertEqual("Handle definition requires a name parameter.", str(context.exception))

    TEST_FAIL_NAME_MUST_NOT_BE_EMPTY={
        "name": "",
    }

    def test_fail_name_must_not_be_empty(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_MUST_NOT_BE_EMPTY)

        self.assertEqual("Handle name value must be a valid string.", str(context.exception))

    TEST_FAIL_NAME_MUST_BE_STRING_INTEGER={
        "name": 1234,
    }

    def test_fail_name_must_be_string_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_INTEGER)

        self.assertEqual("Handle name value must be a valid string.", str(context.exception))

    TEST_FAIL_NAME_MUST_BE_STRING_LIST={
        "name": [
            "a",
            "b",
        ],
    }

    def test_fail_name_must_be_string_list(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_LIST)

        self.assertEqual("Handle name value must be a valid string.", str(context.exception))

    TEST_FAIL_NAME_MUST_BE_STRING_DICTIONARY={
        "name": {
            "beeb": "boob",
        },
    }

    def test_fail_name_must_be_string_dictionary(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_DICTIONARY)

        self.assertEqual("Handle name value must be a valid string.", str(context.exception))

    TEST_FAIL_NAME_CAN_NOT_START_WITH_NUMBER={
        "name": "1Device",
    }

    def test_fail_name_can_not_start_with_number(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_NAME_CAN_NOT_START_WITH_NUMBER)

        self.assertEqual("Handle name can't start with numerals.", str(context.exception))

    def _compile(self, input_content):
        input_content = input_content
        output_processor = TestCompilerBinaryOutput(Handle())
        input_processor = TestCompilerTextInput(input_content)
        compiler = IDLHandleCompiler(output_processor, input_processor)

        compiler.compile()

        return output_processor.content

if __name__ == "__main__":
    unittest.main()
