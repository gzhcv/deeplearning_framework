from __future__ import absolute_import

import os
import ctypes


def _load_lib():
    cur_path = os.path.abspath(__file__)
    lib_path = os.path.join(cur_path, "../../build/lib/")
    lib_so_path = os.path.join(lib_path, "libc_runtime_api.so")
    lib = ctypes.CDLL(lib_so_path, ctypes.RTLD_GLOBAL)
    return lib


_LIB = _load_lib()


def check_call(ret):
    assert(ret == 0)


def c_array(ctype, values):
    return (ctype * len(values))(*values)