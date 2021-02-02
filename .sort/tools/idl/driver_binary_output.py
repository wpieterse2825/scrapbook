class IDLDriverBinaryOutput:
    output_name = None

    def __init__(self, output_name):
        self.output_name = output_name

    def save(self, item):
        with open(self.output_name, "wb") as output_file:
            item_string = item.SerializeToString()
            output_file.write(item_string)
