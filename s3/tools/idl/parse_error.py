class IDLParseError(Exception):
    def __init__(self, message):
        super().__init__(message)
