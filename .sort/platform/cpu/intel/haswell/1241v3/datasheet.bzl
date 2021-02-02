_THREAD_FEATURES_X86_64 = [
    "avx_1",
    "avx_2",
]

_THREAD_OPERATING_MODES = {
    "x86_64": _THREAD_FEATURES_X86_64,
}

_CACHE_THREAD_INSTRUCTION = {
    "supported": True,
    "size": 32 * 1024,
    "associativity": 8,
    "line_size": 64,
}

_CACHE_THREAD_DATA = {
    "supported": True,
    "size": 32 * 1024,
    "associativity": 8,
    "line_size": 64,
}

_LAYOUT_CORE_1_THREAD_1 = {
    "cache_instruction": _CACHE_THREAD_INSTRUCTION,
    "cache_data": _CACHE_THREAD_DATA,
    "operating_modes": _THREAD_OPERATING_MODES,
}

_LAYOUT_CORE_1_THREAD_2 = {
    "cache_instruction": _CACHE_THREAD_INSTRUCTION,
    "cache_data": _CACHE_THREAD_DATA,
    "operating_modes": _THREAD_OPERATING_MODES,
}

_LAYOUT_CORE_2_THREAD_1 = {
    "cache_instruction": _CACHE_THREAD_INSTRUCTION,
    "cache_data": _CACHE_THREAD_DATA,
    "operating_modes": _THREAD_OPERATING_MODES,
}

_LAYOUT_CORE_2_THREAD_2 = {
    "cache_instruction": _CACHE_THREAD_INSTRUCTION,
    "cache_data": _CACHE_THREAD_DATA,
    "operating_modes": _THREAD_OPERATING_MODES,
}

_LAYOUT_CORE_3_THREAD_1 = {
    "cache_instruction": _CACHE_THREAD_INSTRUCTION,
    "cache_data": _CACHE_THREAD_DATA,
    "operating_modes": _THREAD_OPERATING_MODES,
}

_LAYOUT_CORE_3_THREAD_2 = {
    "cache_instruction": _CACHE_THREAD_INSTRUCTION,
    "cache_data": _CACHE_THREAD_DATA,
    "operating_modes": _THREAD_OPERATING_MODES,
}

_LAYOUT_CORE_4_THREAD_1 = {
    "cache_instruction": _CACHE_THREAD_INSTRUCTION,
    "cache_data": _CACHE_THREAD_DATA,
    "operating_modes": _THREAD_OPERATING_MODES,
}

_LAYOUT_CORE_4_THREAD_2 = {
    "cache_instruction": _CACHE_THREAD_INSTRUCTION,
    "cache_data": _CACHE_THREAD_DATA,
    "operating_modes": _THREAD_OPERATING_MODES,
}

_CACHE_CORE = {
    "supported": True,
    "size": 256 * 1024,
    "associativity": 8,
    "line_size": 64,
}

_LAYOUT_CORE_1 = {
    "cache": _CACHE_CORE,
    "threads": 2,
    "thread_1": _LAYOUT_CORE_1_THREAD_1,
    "thread_2": _LAYOUT_CORE_1_THREAD_2,
}

_LAYOUT_CORE_2 = {
    "cache": _CACHE_CORE,
    "threads": 2,
    "thread_1": _LAYOUT_CORE_2_THREAD_1,
    "thread_2": _LAYOUT_CORE_2_THREAD_2,
}

_LAYOUT_CORE_3 = {
    "cache": _CACHE_CORE,
    "threads": 2,
    "thread_1": _LAYOUT_CORE_3_THREAD_1,
    "thread_2": _LAYOUT_CORE_3_THREAD_2,
}

_LAYOUT_CORE_4 = {
    "cache": _CACHE_CORE,
    "threads": 2,
    "thread_1": _LAYOUT_CORE_4_THREAD_1,
    "thread_2": _LAYOUT_CORE_4_THREAD_2,
}

_CACHE_SOCKET = {
    "supported": True,
    "size": 8 * 1024 * 1024,
    "associativity": 16,
    "line_size": 64,
}

_LAYOUT_SOCKET = {
    "cache": _CACHE_SOCKET,
    "cores": 4,
    "core_1": _LAYOUT_CORE_1,
    "core_2": _LAYOUT_CORE_2,
    "core_3": _LAYOUT_CORE_3,
    "core_4": _LAYOUT_CORE_4,
}

MODEL = {
    "model": "1241v3",
    "socket_layout": _LAYOUT_SOCKET,
    "branding": "xeon_e3_v3",
}
