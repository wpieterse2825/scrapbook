import yaml

from tools.idl.shared import *

from tools.idl.driver_multiple_documents_error import IDLDriverTextInputMultipleDocumentsError

class IDLDriverTextInput:
    input_name = None

    def __init__(self, input_name):
        self.input_name = input_name

    def load(self):
        ensure_file(self.input_name, "Could not open input file %s." % self.input_name)

        with open(self.input_name) as input_file:
            yaml_content = ""

            try:
                yaml_content = yaml.load(input_file)
            except yaml.composer.ComposerError:
                raise IDLDriverTextInputMultipleDocumentsError

            return yaml_content
