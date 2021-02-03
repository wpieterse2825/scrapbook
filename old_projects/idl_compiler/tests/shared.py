import unittest

from idl_compiler.shared import *

from idl_compiler.parse_error import IDLParseError

class TestCompiler(unittest.TestCase):
    def test_is_correct_type_integer(self):
        try:
            test_value = 1234
            ensure_correct_type(test_value, int, "Should not fail.")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_is_correct_type_string(self):
        try:
            test_value = "Bob"
            ensure_correct_type(test_value, str, "Should not fail.")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_is_correct_type_list(self):
        try:
            test_value = [
                "a",
                "b",
                "c",
            ]

            ensure_correct_type(test_value, list, "Should not fail.")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_is_correct_type_dictionary(self):
        try:
            test_value = {
                "beeb": "boob",
            }

            ensure_correct_type(test_value, dict, "Should not fail.")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_is_correct_type_with_integer_string(self):
        with self.assertRaises(IDLParseError) as context:
            test_value = 1234

            ensure_correct_type(test_value, str, "Test exception.")

        self.assertEqual("Test exception.", str(context.exception))

    def test_convert_to_signed_to_string_is_valid(self):
        try:
            converted_value = convert_string_to_integer("-1")

            self.assertEqual(True, isinstance(converted_value, int))
            self.assertEqual(-1, converted_value)
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_convert_to_unsigned_to_string_is_valid(self):
        try:
            converted_value = convert_string_to_integer("1")

            self.assertEqual(True, isinstance(converted_value, int))
            self.assertEqual(1, converted_value)
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_convert_to_string_fails_with_non_integer(self):
        with self.assertRaises(IDLParseError) as context:
            convert_string_to_integer("Hello")

        self.assertEqual("Value is not an integer.", str(context.exception))

    def test_fail_native_type_with_invalid_type_name(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("thingamabob", "128")

        self.assertEqual("Value type references unknown native type 'thingamabob'.", str(context.exception))

    def test_native_type_is_valid_signed_8_lower(self):
        try:
            ensure_native_type_value_is_valid("signed_8", "-127")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_native_type_is_valid_signed_8_upper(self):
        try:
            ensure_native_type_value_is_valid("signed_8", "128")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_native_type_is_valid_signed_8_underflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("signed_8", "-128")

        self.assertEqual("Value is too little for requested type.", str(context.exception))

    def test_fail_native_type_is_valid_signed_8_overflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("signed_8", "129")

        self.assertEqual("Value is too large for requested type.", str(context.exception))

    def test_native_type_is_valid_signed_16_lower(self):
        try:
            ensure_native_type_value_is_valid("signed_16", "-32767")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_native_type_is_valid_signed_16_upper(self):
        try:
            ensure_native_type_value_is_valid("signed_16", "32767")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_native_type_is_valid_signed_16_underflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("signed_16", "-32768")

        self.assertEqual("Value is too little for requested type.", str(context.exception))

    def test_fail_native_type_is_valid_signed_16_overflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("signed_16", "32768")

        self.assertEqual("Value is too large for requested type.", str(context.exception))

    def test_native_type_is_valid_signed_32_lower(self):
        try:
            ensure_native_type_value_is_valid("signed_32", "-2147483647")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_native_type_is_valid_signed_32_upper(self):
        try:
            ensure_native_type_value_is_valid("signed_32", "2147483647")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_native_type_is_valid_signed_32_underflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("signed_32", "-2147483648")

        self.assertEqual("Value is too little for requested type.", str(context.exception))

    def test_fail_native_type_is_valid_signed_32_overflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("signed_32", "2147483648")

        self.assertEqual("Value is too large for requested type.", str(context.exception))

    def test_native_type_is_valid_signed_64_lower(self):
        try:
            ensure_native_type_value_is_valid("signed_64", "-9223372036854775807")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_native_type_is_valid_signed_64_upper(self):
        try:
            ensure_native_type_value_is_valid("signed_64", "9223372036854775807")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_native_type_is_valid_signed_64_underflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("signed_64", "-9223372036854775808")

        self.assertEqual("Value is too little for requested type.", str(context.exception))

    def test_fail_native_type_is_valid_signed_64_overflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("signed_64", "9223372036854775808")

        self.assertEqual("Value is too large for requested type.", str(context.exception))

    def test_native_type_is_valid_unsigned_8_lower(self):
        try:
            ensure_native_type_value_is_valid("unsigned_8", "0")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_native_type_is_valid_unsigned_8_upper(self):
        try:
            ensure_native_type_value_is_valid("unsigned_8", "255")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_native_type_is_valid_unsigned_8_underflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("unsigned_8", "-1")

        self.assertEqual("Value is signed, while the value type only allows unsigned values.", str(context.exception))

    def test_fail_native_type_is_valid_unsigned_8_overflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("unsigned_8", "256")

        self.assertEqual("Value is too large for requested type.", str(context.exception))

    def test_native_type_is_valid_unsigned_16_lower(self):
        try:
            ensure_native_type_value_is_valid("unsigned_16", "0")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_native_type_is_valid_unsigned_16_upper(self):
        try:
            ensure_native_type_value_is_valid("unsigned_16", "65535")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_native_type_is_valid_unsigned_16_underflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("unsigned_16", "-1")

        self.assertEqual("Value is signed, while the value type only allows unsigned values.", str(context.exception))

    def test_fail_native_type_is_valid_unsigned_16_overflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("unsigned_16", "65536")

        self.assertEqual("Value is too large for requested type.", str(context.exception))

    def test_native_type_is_valid_unsigned_32_lower(self):
        try:
            ensure_native_type_value_is_valid("unsigned_32", "0")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_native_type_is_valid_unsigned_32_upper(self):
        try:
            ensure_native_type_value_is_valid("unsigned_32", "4294967295")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_native_type_is_valid_unsigned_32_underflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("unsigned_32", "-1")

        self.assertEqual("Value is signed, while the value type only allows unsigned values.", str(context.exception))

    def test_fail_native_type_is_valid_unsigned_32_overflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("unsigned_32", "4294967296")

        self.assertEqual("Value is too large for requested type.", str(context.exception))

    def test_native_type_is_valid_unsigned_64_lower(self):
        try:
            ensure_native_type_value_is_valid("unsigned_64", "0")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_native_type_is_valid_unsigned_64_upper(self):
        try:
            ensure_native_type_value_is_valid("unsigned_64", "18446744073709551615")
        except Exception:
            self.fail("Call should not raise exception with input parameters.")

    def test_fail_native_type_is_valid_unsigned_64_underflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("unsigned_64", "-1")

        self.assertEqual("Value is signed, while the value type only allows unsigned values.", str(context.exception))

    def test_fail_native_type_is_valid_unsigned_64_overflow(self):
        with self.assertRaises(IDLParseError) as context:
            ensure_native_type_value_is_valid("unsigned_64", "18446744073709551616")

        self.assertEqual("Value is too large for requested type.", str(context.exception))

if __name__ == "__main__":
    unittest.main()