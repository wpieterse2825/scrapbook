load(
    "//idl_compiler:build_private.bzl",
    _IDLArchiveInfo = "IDLArchiveInfo",
    _IDLEnumerationInfo = "IDLEnumerationInfo",
    _IDLFunctionInfo = "IDLFunctionInfo",
    _IDLGeneratorInfo = "IDLGeneratorInfo",
    _IDLHandleInfo = "IDLHandleInfo",
    _IDLStructureInfo = "IDLStructureInfo",
)
load("//idl_compiler/compiler:build.bzl", _idl_compiler_toolchain = "idl_compiler_toolchain")
load("//idl_compiler/compiler/handle:build.bzl", _idl_handle = "idl_handle")
load("//idl_compiler/compiler/enumeration:build.bzl", _idl_enumeration = "idl_enumeration")
load("//idl_compiler/compiler/structure:build.bzl", _idl_structure = "idl_structure")
load("//idl_compiler/compiler/function:build.bzl", _idl_function = "idl_function")
load("//idl_compiler/linker:build.bzl", _idl_linker_toolchain = "idl_linker_toolchain")
load("//idl_compiler/linker/archive:build.bzl", _idl_archive = "idl_archive")
load("//idl_compiler/generator:build.bzl", _idl_generator_toolchain = "idl_generator_toolchain")
load("//idl_compiler/generator/generator_props:build.bzl", _idl_generator_props = "idl_generator_props")
load("//idl_compiler/generator/c:build.bzl", _idl_generator_c = "idl_generator_c")
load("//idl_compiler/generator/cpp:build.bzl", _idl_generator_cpp = "idl_generator_cpp")

IDLHandleInfo = _IDLHandleInfo
IDLEnumerationInfo = _IDLEnumerationInfo
IDLStructureInfo = _IDLStructureInfo
IDLFunctionInfo = _IDLFunctionInfo
IDLArchiveInfo = _IDLArchiveInfo
IDLGeneratorInfo = _IDLGeneratorInfo

idl_generator_props = _idl_generator_props

idl_compiler_toolchain = _idl_compiler_toolchain
idl_linker_toolchain = _idl_linker_toolchain
idl_generator_toolchain = _idl_generator_toolchain

idl_handle = _idl_handle
idl_enumeration = _idl_enumeration
idl_structure = _idl_structure
idl_function = _idl_function
idl_archive = _idl_archive

idl_generator_c = _idl_generator_c
idl_generator_cpp = _idl_generator_cpp