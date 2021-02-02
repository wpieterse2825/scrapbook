import unittest

from idl_compiler.parse_error import IDLParseError

from idl_compiler.compiler.compiler import IDLCompiler

class TestCompilerDocumentation(unittest.TestCase):
    TEST_PARSE_SINGLE_DOCUMENTATION={
        "english": "Hello, World",
    }

    def test_parse_single_documentation(self):
        output_content = self._compile(self.TEST_PARSE_SINGLE_DOCUMENTATION)

        self.assertEqual(1, len(output_content.items()))
        self.assertEqual(True, "english" in output_content)
        self.assertEqual("Hello, World", output_content.get("english"))

    TEST_PARSE_MULTIPLE_DOCUMENTATION={
        "english": "Hello, World",
        "french": "Bonjour le monde",
        "spanish": "Hola Mundo",
    }

    def test_parse_multiple_documentation(self):
        output_content = self._compile(self.TEST_PARSE_MULTIPLE_DOCUMENTATION)

        self.assertEqual(3, len(output_content.items()))
        self.assertEqual(True, "english" in output_content)
        self.assertEqual(True, "french" in output_content)
        self.assertEqual(True, "spanish" in output_content)
        self.assertEqual("Hello, World", output_content.get("english"))
        self.assertEqual("Bonjour le monde", output_content.get("french"))
        self.assertEqual("Hola Mundo", output_content.get("spanish"))

    TEST_ACCEPT_NONE_DOCUMENTATION=None

    def test_accept_none_documentation(self):
        output_content = self._compile(self.TEST_ACCEPT_NONE_DOCUMENTATION)

        self.assertEqual(0, len(output_content.items()))

    TEST_ACCEPT_EMPTY_DOCUMENTATION={}

    def test_accept_empty_documentation(self):
        output_content = self._compile(self.TEST_ACCEPT_EMPTY_DOCUMENTATION)

        self.assertEqual(0, len(output_content.items()))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_INTEGER=1234

    def test_fail_input_must_be_dictionary_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_INTEGER)

        self.assertEqual("Documentation definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_STRING="beeb"

    def test_fail_input_must_be_dictionary_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_STRING)

        self.assertEqual("Documentation definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_LIST=[
        "a",
        "b",
    ]

    def test_fail_input_must_be_dictionary_list(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_LIST)

        self.assertEqual("Documentation definition must be a valid dictionary.", str(context.exception))

    TEST_FAIL_KEY_MUST_NOT_BE_AN_EMPTY_STRING={
        "" : "Hello, World",
    }

    def test_fail_key_must_not_be_an_empty_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_KEY_MUST_NOT_BE_AN_EMPTY_STRING)

        self.assertEqual("Documentation definition contains a key that is not a valid string.", str(context.exception))

    TEST_FAIL_KEY_MUST_BE_A_VALID_STRING={
        123 : "Hello, World",
    }

    def test_fail_key_must_be_a_valid_string(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_KEY_MUST_BE_A_VALID_STRING)

        self.assertEqual("Documentation definition contains a key that is not a valid string.", str(context.exception))

    TEST_FAIL_VALUE_MUST_BE_VALID_STRING={
        "english" : "",
    }

    def test_fail_value_must_be_a_valid_string_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_VALUE_MUST_BE_VALID_STRING)

        self.assertEqual("Documentation definition contains a value that is not a valid string.", str(context.exception))

    TEST_FAIL_VALUE_MUST_BE_VALID_STRING_INTEGER={
        "english" : 123,
    }

    def test_fail_value_must_be_a_valid_string_integer(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_VALUE_MUST_BE_VALID_STRING_INTEGER)

        self.assertEqual("Documentation definition contains a value that is not a valid string.", str(context.exception))

    TEST_FAIL_VALUE_MUST_BE_VALID_STRING_LIST={
        "english" : [
            "a",
            "b",
        ],
    }

    def test_fail_value_must_be_a_valid_string_list(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_VALUE_MUST_BE_VALID_STRING_LIST)

        self.assertEqual("Documentation definition contains a value that is not a valid string.", str(context.exception))

    TEST_FAIL_VALUE_MUST_BE_VALID_STRING_DICTIONARY={
        "english" : {
            "beeb": "boob",
        },
    }

    def test_fail_value_must_be_a_valid_string_dictionary(self):
        with self.assertRaises(IDLParseError) as context:
            self._compile(self.TEST_FAIL_VALUE_MUST_BE_VALID_STRING_DICTIONARY)

        self.assertEqual("Documentation definition contains a value that is not a valid string.", str(context.exception))

    def _compile(self, input_content):
        compiler = IDLCompiler("output", "input")
        output_content = {}

        compiler.process_documentation(output_content, input_content)

        return output_content

if __name__ == "__main__":
    unittest.main()
