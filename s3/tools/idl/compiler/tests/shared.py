import yaml

from tools.idl.driver_multiple_documents_error import IDLDriverTextInputMultipleDocumentsError

class TestCompilerTextInput:
    def __init__(self, content):
        self.content = content

    def load(self):
        return self.content

class TestCompilerBinaryOutput:
    def __init__(self, default_item):
        self.content = default_item

    def save(self, item):
        self.content = item
