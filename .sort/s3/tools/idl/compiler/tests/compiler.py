import unittest

from tools.idl.compiler.compiler import IDLCompiler

class TestCompiler(unittest.TestCase):
    def test_assign_correct_values(self):
        compiler = IDLCompiler("output", "input")

        self.assertEqual("output", compiler.compiler_output)
        self.assertEqual("input", compiler.compiler_input)

if __name__ == "__main__":
    unittest.main()
