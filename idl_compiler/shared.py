import sys
import os.path
import collections

from functools import reduce as _reduce

from idl_compiler.parse_error import IDLParseError

def fail_with_message(message):
    print("ERROR: %s" % message)
    sys.exit(1)

def ensure_file(file_name, message):
    if not os.path.isfile(file_name):
        fail_with_message(message)

def ensure_correct_type(input_value, input_type, fail_message):
    if not isinstance(input_value, input_type):
        raise IDLParseError(fail_message)

def ensure_is_list(input_value, fail_message):
    ensure_correct_type(input_value, list, fail_message)

def ensure_is_dictionary(input_value, fail_message):
    ensure_correct_type(input_value, collections.Mapping, fail_message)

def ensure_collection_is_not_empty(input_value, fail_message):
    if isinstance(input_value, collections.Mapping):
        if len(input_value.items()) == 0:
            raise IDLParseError(fail_message)
    else:
        if len(input_value) == 0:
            raise IDLParseError(fail_message)

def ensure_dictionary_key_is_string(input_key, fail_message):
    if not isinstance(input_key, str):
        raise IDLParseError(fail_message)

    if len(input_key) == 0:
        raise IDLParseError(fail_message)

def ensure_dictionary_value_is_string(input_value, fail_message):
    if not isinstance(input_value, str):
        raise IDLParseError(fail_message)

    if len(input_value) == 0:
        raise IDLParseError(fail_message)

def ensure_key_was_processed(processed_keys, key_name, fail_message):
    if key_name not in processed_keys:
        raise IDLParseError(fail_message)

def convert_string_to_integer(value):
    try:
        return int(value)
    except ValueError:
        raise IDLParseError("Value is not an integer.")

def ensure_native_type_value_is_valid(native_type_name, value):
    converted_value = convert_string_to_integer(value)

    if native_type_name.startswith("unsigned"):
        if converted_value < 0:
            raise IDLParseError("Value is signed, while the value type only allows unsigned values.")

    if native_type_name == "unsigned_8":
        if converted_value > 255:
            raise IDLParseError("Value is too large for requested type.")
    elif native_type_name == "unsigned_16":
        if converted_value > 65535:
            raise IDLParseError("Value is too large for requested type.")
    elif native_type_name == "unsigned_32":
        if converted_value > 4294967295:
            raise IDLParseError("Value is too large for requested type.")
    elif native_type_name == "unsigned_64":
        if converted_value > 18446744073709551615:
            raise IDLParseError("Value is too large for requested type.")
    elif native_type_name == "signed_8":
        if converted_value < -127:
            raise IDLParseError("Value is too little for requested type.")
        elif converted_value > 128:
            raise IDLParseError("Value is too large for requested type.")
    elif native_type_name == "signed_16":
        if converted_value < -32767:
            raise IDLParseError("Value is too little for requested type.")
        elif converted_value > 32767:
            raise IDLParseError("Value is too large for requested type.")
    elif native_type_name == "signed_32":
        if converted_value < -2147483647:
            raise IDLParseError("Value is too little for requested type.")
        elif converted_value > 2147483647:
            raise IDLParseError("Value is too large for requested type.")
    elif native_type_name == "signed_64":
        if converted_value < -9223372036854775807:
            raise IDLParseError("Value is too little for requested type.")
        elif converted_value > 9223372036854775807:
            raise IDLParseError("Value is too large for requested type.")
    else:
        raise IDLParseError("Value type references unknown native type '%s'." % native_type_name)

class CircularDependencyError(ValueError):
    def __init__(self, data):
        s = 'Circular dependencies exist among these items: {{{}}}'.format(', '.join('{!r}:{!r}'.format(key, value) for key, value in sorted(data.items())))
        super(CircularDependencyError, self).__init__(s)
        self.data = data

def toposort(data):
    if len(data) == 0:
        return

    data = data.copy()
    for k, v in data.items():
        v.discard(k)

    extra_items_in_deps = _reduce(set.union, data.values()) - set(data.keys())
    data.update({item:set() for item in extra_items_in_deps})
    while True:
        ordered = set(item for item, dep in data.items() if len(dep) == 0)
        if not ordered:
            break

        yield ordered
        data = {item: (dep - ordered)
                for item, dep in data.items()
                    if item not in ordered}

    if len(data) != 0:
        raise CircularDependencyError(data)


def toposort_flatten(data, sort=True):
    result = []
    for d in toposort(data):
        result.extend((sorted if sort else list)(d))

    return result
