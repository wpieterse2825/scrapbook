class IDLDriverTextOutput:
    output_name = None

    def __init__(self, output_name):
        self.output_name = output_name

    def save(self, item):
        with open(self.output_name, "w") as output_file:
            output_file.write(item)
