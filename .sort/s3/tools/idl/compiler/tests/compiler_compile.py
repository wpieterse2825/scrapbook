import unittest

from tools.idl.compiler.compiler import IDLCompiler

class TestCompilerCompile(unittest.TestCase):
    def test_compile_throws_exception(self):
        compiler = IDLCompiler("input", "output")

        self.assertRaises(NotImplementedError, compiler.compile)

if __name__ == "__main__":
    unittest.main()
