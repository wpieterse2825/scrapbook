import unittest

from tools.idl.compiler.tests.shared import TestCompilerBinaryOutput
from tools.idl.compiler.tests.shared import TestCompilerTextInput

from tools.idl.compiler.shared_pb2 import TypeReference

from tools.idl.compiler.enumeration.protocol_pb2 import Enumeration

from tools.idl.compiler.enumeration.compiler import IDLEnumerationCompiler

class TestCompiler(unittest.TestCase):
    TEST_NAME_AND_TYPE_ONLY={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_name_and_type_only(self):
        output_content = self._compile(self.TEST_NAME_AND_TYPE_ONLY)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("unsigned_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_NAME_CAN_CONTAINER_NUMBERS={
        "name": "S123",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_name_can_contain_numbers(self):
        output_content = self._compile(self.TEST_NAME_CAN_CONTAINER_NUMBERS)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("S123", output_content.name)
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("unsigned_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_NAME_WITH_DOCUMENTATION={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
        "documentation": {
            "english": "Hello, World",
        },
    }

    def test_name_with_documentation(self):
        output_content = self._compile(self.TEST_NAME_WITH_DOCUMENTATION)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("unsigned_8", output_content.type.name)
        self.assertEqual(1, len(output_content.documentation.items()))

    TEST_ITEM_PREFIX_CAN_BE_EMPTY={
        "name": "SurfaceFormat",
        "item_prefix": "",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_item_prefix_can_be_empty(self):
        output_content = self._compile(self.TEST_ITEM_PREFIX_CAN_BE_EMPTY)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual("", output_content.item_prefix)
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("unsigned_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_NONE_ITEMS_ACCEPTED={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": None,
    }

    def test_none_items_accepted(self):
        output_content = self._compile(self.TEST_NONE_ITEMS_ACCEPTED)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual("", output_content.item_prefix)
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("signed_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_EMPTY_ITEMS_ACCEPTED={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [],
    }

    def test_empty_items_accepted(self):
        output_content = self._compile(self.TEST_EMPTY_ITEMS_ACCEPTED)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual("", output_content.item_prefix)
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("signed_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_CAN_PARSE_SINGLE_ITEM_SIGNED={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "RGBA8",
                "value": "-1",
                "documentation": {
                    "english": "Hello, World",
                },
            },
        ]
    }

    def test_can_parse_single_item_signed(self):
        output_content = self._compile(self.TEST_CAN_PARSE_SINGLE_ITEM_SIGNED)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual("", output_content.item_prefix)
        self.assertEqual(1, len(output_content.items))
        self.assertEqual("RGBA8", output_content.items[0].name)
        self.assertEqual("-1", output_content.items[0].value)
        self.assertEqual(1, len(output_content.items[0].documentation))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("signed_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_CAN_PARSE_SINGLE_ITEM_UNSIGNED={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
        "items": [
            {
                "name": "RGBA8",
                "value": "1",
                "documentation": {
                    "english": "Hello, World",
                },
            },
        ]
    }

    def test_can_parse_single_item_unsigned(self):
        output_content = self._compile(self.TEST_CAN_PARSE_SINGLE_ITEM_UNSIGNED)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual("", output_content.item_prefix)
        self.assertEqual(1, len(output_content.items))
        self.assertEqual("RGBA8", output_content.items[0].name)
        self.assertEqual("1", output_content.items[0].value)
        self.assertEqual(1, len(output_content.items[0].documentation))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("unsigned_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_CAN_PARSE_MULTIPLE_ITEMS_SIGNED={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "UP",
                "value": "-1",
                "documentation": {
                    "english": "Hello, World",
                },
            },
            {
                "name": "UNKNOWN",
                "value": "0",
            },
            {
                "name": "DOWN",
                "value": "1",
            },
        ]
    }

    def test_can_parse_multiple_items_signed(self):
        output_content = self._compile(self.TEST_CAN_PARSE_MULTIPLE_ITEMS_SIGNED)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual("", output_content.item_prefix)
        self.assertEqual(3, len(output_content.items))
        self.assertEqual("UP", output_content.items[0].name)
        self.assertEqual("-1", output_content.items[0].value)
        self.assertEqual(1, len(output_content.items[0].documentation.items()))
        self.assertEqual("UNKNOWN", output_content.items[1].name)
        self.assertEqual("0", output_content.items[1].value)
        self.assertEqual(0, len(output_content.items[1].documentation.items()))
        self.assertEqual("DOWN", output_content.items[2].name)
        self.assertEqual("1", output_content.items[2].value)
        self.assertEqual(0, len(output_content.items[2].documentation.items()))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("signed_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_CAN_PARSE_MULTIPLE_ITEMS_UNSIGNED={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
        "items": [
            {
                "name": "UNKNOWN",
                "value": "0",
                "documentation": {
                    "english": "Hello, World",
                },
            },
            {
                "name": "FORWARD",
                "value": "1",
            },
            {
                "name": "BACKWARD",
                "value": "2",
            },
        ]
    }

    def test_can_parse_multiple_items_unsigned(self):
        output_content = self._compile(self.TEST_CAN_PARSE_MULTIPLE_ITEMS_UNSIGNED)

        self.assertEqual(0, len(errors), errors)
        self.assertEqual("SurfaceFormat", output_content.name)
        self.assertEqual("", output_content.item_prefix)
        self.assertEqual(3, len(output_content.items))
        self.assertEqual("UNKNOWN", output_content.items[0].name)
        self.assertEqual("0", output_content.items[0].value)
        self.assertEqual(1, len(output_content.items[0].documentation.items()))
        self.assertEqual("FORWARD", output_content.items[1].name)
        self.assertEqual("1", output_content.items[1].value)
        self.assertEqual(0, len(output_content.items[1].documentation.items()))
        self.assertEqual("BACKWARD", output_content.items[2].name)
        self.assertEqual("2", output_content.items[2].value)
        self.assertEqual(0, len(output_content.items[2].documentation.items()))
        self.assertEqual(TypeReference.NATIVE, output_content.type.reference)
        self.assertEqual("unsigned_8", output_content.type.name)
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_INPUT_MUST_NOT_BE_NONE=None

    def test_fail_input_must_not_be_none(self):
        output_content = self._compile(self.TEST_FAIL_INPUT_MUST_NOT_BE_NONE)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition must be a valid dictionary.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_INTEGER=1234

    def test_fail_input_must_be_dictionary_integer(self):
        output_content = self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_INTEGER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition must be a valid dictionary.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_STRING="beeb"

    def test_fail_input_must_be_dictionary_string(self):
        output_content = self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_STRING)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition must be a valid dictionary.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_INPUT_MUST_BE_DICTIONARY_LIST=[
        "a",
        "b",
    ]

    def test_fail_input_must_be_dictionary_list(self):
        output_content = self._compile(self.TEST_FAIL_INPUT_MUST_BE_DICTIONARY_LIST)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition must be a valid dictionary.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_INPUT_MUST_CONTAIN_ITEMS={}

    def test_fail_input_must_contain_items(self):
        output_content = self._compile(self.TEST_FAIL_INPUT_MUST_CONTAIN_ITEMS)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition is empty.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_KEY_MUST_BE_STRING={
        123: "SurfaceFormat",
    }

    def test_fail_key_must_be_string(self):
        output_content = self._compile(self.TEST_FAIL_KEY_MUST_BE_STRING)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition contains a key that is not a string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_KEY_MUST_NOT_BE_EMPTY_STRING={
        "": "SurfaceFormat",
    }

    def test_fail_key_must_not_be_empty_string(self):
        output_content = self._compile(self.TEST_FAIL_KEY_MUST_NOT_BE_EMPTY_STRING)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition contains a key that is an empty string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_WITH_UNKNOWN_KEY={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
        "beeb": "boob",
    }

    def test_fail_with_unknown_key(self):
        output_content = self._compile(self.TEST_FAIL_WITH_UNKNOWN_KEY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition contains unknown key 'beeb' with value 'boob'.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_NAME_IS_REQUIRED={
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
        "documentation": {
            "english": "Hello, World",
        },
    }

    def test_fail_name_is_required(self):
        output_content = self._compile(self.TEST_FAIL_NAME_IS_REQUIRED)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition requires a name parameter.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_NAME_MUST_NOT_BE_EMPTY={
        "name": "",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_fail_name_must_not_be_empty(self):
        output_content = self._compile(self.TEST_FAIL_NAME_MUST_NOT_BE_EMPTY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration name is an empty string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_NAME_MUST_BE_STRING_INTEGER={
        "name": 1234,
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_fail_name_must_be_string_integer(self):
        output_content = self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_INTEGER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration name value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_NAME_MUST_BE_STRING_LIST={
        "name": [
            "a",
            "b",
        ],
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_fail_name_must_be_string_list(self):
        output_content = self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_LIST)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration name value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_NAME_MUST_BE_STRING_DICTIONARY={
        "name": {
            "beeb": "boob",
        },
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_fail_name_must_be_string_dictionary(self):
        output_content = self._compile(self.TEST_FAIL_NAME_MUST_BE_STRING_DICTIONARY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration name value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_NAME_CAN_NOT_START_WITH_NUMBER={
        "name": "1SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_fail_name_can_not_start_with_number(self):
        output_content = self._compile(self.TEST_FAIL_NAME_CAN_NOT_START_WITH_NUMBER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration name can't start with numerals.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_TYPE_IS_REQUIRED={
        "name": "SurfaceFormat",
    }

    def test_faile_type_is_required(self):
        output_content = self._compile(self.TEST_FAIL_TYPE_IS_REQUIRED)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration definition requires a type parameter.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_PREFIX_MUST_BE_STRING_INTEGER={
        "name": "SurfaceFormat",
        "item_prefix": 1234,
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_fail_item_prefix_must_be_string_integer(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_PREFIX_MUST_BE_STRING_INTEGER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item prefix value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_PREFIX_MUST_BE_STRING_LIST={
        "name": "SurfaceFormat",
        "item_prefix": [
            "a",
            "b",
        ],
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_fail_item_prefix_must_be_string_list(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_PREFIX_MUST_BE_STRING_LIST)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item prefix value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_PREFIX_MUST_BE_STRING_DICTIONARY={
        "name": "SurfaceFormat",
        "item_prefix": {
            "beeb": "boob",
        },
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
    }

    def test_fail_item_prefix_must_be_string_dictionary(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_PREFIX_MUST_BE_STRING_DICTIONARY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item prefix value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEMS_MUST_BE_LIST_INTEGER={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": 123,
    }

    def test_fail_items_must_be_list_integer(self):
        output_content = self._compile(self.TEST_FAIL_ITEMS_MUST_BE_LIST_INTEGER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration items content must be a valid list.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEMS_MUST_BE_LIST_STRING={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": "Hello",
    }

    def test_fail_items_must_be_list_string(self):
        output_content = self._compile(self.TEST_FAIL_ITEMS_MUST_BE_LIST_STRING)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration items content must be a valid list.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEMS_MUST_BE_LIST_DICTIONARY={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": {
            "beeb": "boob",
        },
    }

    def test_fail_items_must_be_list_dictionary(self):
        output_content = self._compile(self.TEST_FAIL_ITEMS_MUST_BE_LIST_DICTIONARY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration items content must be a valid list.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEMS_CONTENT_MUST_BE_DICTIONARY_INTEGER={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            123,
            456,
            789,
        ],
    }

    def test_fail_items_content_must_be_dictionary_integer(self):
        output_content = self._compile(self.TEST_FAIL_ITEMS_CONTENT_MUST_BE_DICTIONARY_INTEGER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item definition must be a valid dictionary.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEMS_CONTENT_MUST_BE_DICTIONARY_STRING={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            "Hello",
            "World",
        ],
    }

    def test_fail_items_content_must_be_dictionary_string(self):
        output_content = self._compile(self.TEST_FAIL_ITEMS_CONTENT_MUST_BE_DICTIONARY_STRING)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item definition must be a valid dictionary.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEMS_CONTENT_MUST_BE_DICTIONARY_LIST={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            ["a", "b", "c"],
            ["d", "e", "f"],
            ["g", "h", "i"],
        ],
    }

    def test_fail_items_content_must_be_dictionary_list(self):
        output_content = self._compile(self.TEST_FAIL_ITEMS_CONTENT_MUST_BE_DICTIONARY_LIST)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item definition must be a valid dictionary.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_KEY_MUST_BE_STRING={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                123: "SurfaceFormat",
            },
        ],
    }

    def test_fail_item_key_must_be_string(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_KEY_MUST_BE_STRING)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item definition contains a key that is not a string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_KEY_MUST_NOT_BE_EMPTY_STRING={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "": "SurfaceFormat",
            },
        ],
    }

    def test_fail_item_key_must_not_be_empty_string(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_KEY_MUST_NOT_BE_EMPTY_STRING)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item definition contains a key that is an empty string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_WITH_UNKNOWN_KEY={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "SurfaceFormat",
                "beeb": "boob",
            },
        ],
    }

    def test_fail_item_with_unknown_key(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_WITH_UNKNOWN_KEY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item definition contains unknown key 'beeb' with value 'boob'.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_NAME_IS_REQUIRED={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "value": "0",
            },
        ],
    }

    def test_fail_item_name_is_required(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_NAME_IS_REQUIRED)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item definition requires a name parameter.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_NAME_MUST_NOT_BE_EMPTY={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "",
            },
        ],
    }

    def test_fail_item_name_must_not_be_empty(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_NAME_MUST_NOT_BE_EMPTY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item name is an empty string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_NAME_MUST_BE_STRING_INTEGER={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": 1234,
            },
        ],
    }

    def test_fail_item_name_must_be_string_integer(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_NAME_MUST_BE_STRING_INTEGER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item name value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_NAME_MUST_BE_STRING_LIST={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": [
                    "a",
                    "b",
                ],
            },
        ],
    }

    def test_fail_item_name_must_be_string_list(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_NAME_MUST_BE_STRING_LIST)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item name value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_NAME_MUST_BE_STRING_DICTIONARY={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": {
                    "beeb": "boob",
                },
            },
        ],
    }

    def test_fail_item_name_must_be_string_dictionary(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_NAME_MUST_BE_STRING_DICTIONARY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item name value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_VALUE_IS_REQUIRED={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "UNKNOWN",
            },
        ],
    }

    def test_fail_item_value_is_required(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_VALUE_IS_REQUIRED)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item definition requires a value parameter.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_VALUE_MUST_NOT_BE_EMPTY={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "UNKNOWN",
                "value": "",
            },
        ],
    }

    def test_fail_item_value_must_not_be_empty(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_VALUE_MUST_NOT_BE_EMPTY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item value is an empty string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_VALUE_MUST_BE_STRING_INTEGER={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "UNKNOWN",
                "value": 1234,
            },
        ],
    }

    def test_fail_item_value_must_be_string_integer(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_VALUE_MUST_BE_STRING_INTEGER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item value value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_VALUE_MUST_BE_STRING_LIST={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "UNKNOWN",
                "value": [
                    "a",
                    "b",
                ],
            },
        ],
    }

    def test_fail_item_value_must_be_string_list(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_VALUE_MUST_BE_STRING_LIST)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item value value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_VALUE_MUST_BE_STRING_DICTIONARY={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "UNKNOWN",
                "value": {
                    "beeb": "boob",
                },
            },
        ],
    }

    def test_fail_item_value_must_be_string_dictionary(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_VALUE_MUST_BE_STRING_DICTIONARY)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item value value must be a valid string.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_VALUE_MUST_BE_INTEGER={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "signed_8",
        },
        "items": [
            {
                "name": "UNKNOWN",
                "value": "bob",
            },
        ],
    }

    def test_fail_item_value_must_be_integer(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_VALUE_MUST_BE_INTEGER)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item value is not an integer.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_ITEM_VALUE_MUST_MATCH_TYPE={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "unsigned_8",
        },
        "items": [
            {
                "name": "UNKNOWN",
                "value": "-1",
            },
        ],
    }

    def test_fail_item_value_must_match_type(self):
        output_content = self._compile(self.TEST_FAIL_ITEM_VALUE_MUST_MATCH_TYPE)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration item value is signed, while the enumeration only allows unsigned values.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    TEST_FAIL_UNSUPPORTED_TYPE_NAME={
        "name": "SurfaceFormat",
        "type": {
            "reference": "native",
            "name": "giggabomb",
        },
        "items": [
            {
                "name": "UNKNOWN",
                "value": "0",
            },
        ],
    }

    def test_fail_unsupported_type_name(self):
        output_content = self._compile(self.TEST_FAIL_UNSUPPORTED_TYPE_NAME)

        self.assertEqual(1, len(errors), errors)
        self.assertEqual("Enumeration type name is not supported.", errors[0])
        self.assertEqual(0, len(output_content.name))
        self.assertEqual(0, len(output_content.item_prefix))
        self.assertEqual(0, len(output_content.items))
        self.assertEqual(TypeReference.UNKNOWN, output_content.type.reference)
        self.assertEqual(0, len(output_content.type.name))
        self.assertEqual(0, len(output_content.documentation.items()))

    def _compile(self, input_content):
        input_content = input_content
        output_processor = TestCompilerBinaryOutput(Enumeration())
        input_processor = TestCompilerTextInput(input_content)
        compiler = IDLEnumerationCompiler(output_processor, input_processor)

        compiler.compile()

        return output_processor.content

if __name__ == "__main__":
    unittest.main()
