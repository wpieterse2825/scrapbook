load(
    "//tools/idl:build_private.bzl",
    _IDLArchiveInfo = "IDLArchiveInfo",
    _IDLEnumerationInfo = "IDLEnumerationInfo",
    _IDLFunctionInfo = "IDLFunctionInfo",
    _IDLGeneratorInfo = "IDLGeneratorInfo",
    _IDLHandleInfo = "IDLHandleInfo",
    _IDLStructureInfo = "IDLStructureInfo",
)
load("//tools/idl/compiler:build.bzl", _idl_compiler_toolchain = "idl_compiler_toolchain")
load("//tools/idl/compiler/handle:build.bzl", _idl_handle = "idl_handle")
load("//tools/idl/compiler/enumeration:build.bzl", _idl_enumeration = "idl_enumeration")
load("//tools/idl/compiler/structure:build.bzl", _idl_structure = "idl_structure")
load("//tools/idl/compiler/function:build.bzl", _idl_function = "idl_function")
load("//tools/idl/linker:build.bzl", _idl_linker_toolchain = "idl_linker_toolchain")
load("//tools/idl/linker/archive:build.bzl", _idl_archive = "idl_archive")
load("//tools/idl/generator:build.bzl", _idl_generator_toolchain = "idl_generator_toolchain")
load("//tools/idl/generator/generator_props:build.bzl", _idl_generator_props = "idl_generator_props")
load("//tools/idl/generator/c:build.bzl", _idl_generator_c = "idl_generator_c")
load("//tools/idl/generator/cpp:build.bzl", _idl_generator_cpp = "idl_generator_cpp")

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
