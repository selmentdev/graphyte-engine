import sys
import os
import json
from enum import Enum
from typing import List, Dict

_ANDROID_ABI_MAPPINGS = {
    'armv7': {
        'toolchain': 'arm',
        'platform': 'arm',
        'bitness': 32,
        'libdir': 'lib',
    },
    'armv8': {
        'toolchain': 'aarch64',
        'platform': 'arm64',
        'bitness': 64,
        'libdir': 'lib',
    },
    'x86': {
        'toolchain': 'i686',
        'platform': 'x86',
        'bitness': 32,
        'libdir': 'lib',
    },
    'x86_64': {
        'toolchain': 'x86_64',
        'platform': 'x86_64',
        'bitness': 64,
        'libdir': 'lib64',
    },
}

def abi_toolchain_prefix(abi : str) -> str:
    return _ANDROID_ABI_MAPPINGS.get(abi)['toolchain']

def abi_platform_prefix(abi : str) -> str:
    return _ANDROID_ABI_MAPPINGS.get(abi)['platform']

def abi_bitness(abi : str) -> int:
    return _ANDROID_ABI_MAPPINGS.get(abi)['bitness']

def abi_platform_libdir(abi : str) -> str:
    return _ANDROID_ABI_MAPPINGS.get(abi)['libdir']

ANDROID_SDK_PATH = os.getenv('ANDROID_SDK')
ANDROID_NDK_PATH = os.getenv('ANDROID_NDK')

"""
Returns min and max version of APIs
"""
def _find_ndk_platforms() -> (int, int):
    if ANDROID_NDK_PATH is not None:
        with open(os.path.join(ANDROID_NDK_PATH, 'meta', 'platforms.json'), 'r') as f:
            keys = json.loads(f.read())
            return (keys['min'], keys['max'])

    return (0, 0)

ANDROID_MIN_API_LEVEL, ANDROID_MAX_API_LEVEL = _find_ndk_platforms()

"""
Returns available NDK ABIs
"""
def _find_ndk_abis() -> List[str]:
    if ANDROID_NDK_PATH is not None:
        with open(os.path.join(ANDROID_NDK_PATH, 'meta', 'abis.json'), 'r') as f:
            abis = json.loads(f.read())

            return [x for x in abis.keys()]

    return None

ANDROID_NDK_ABIS : List[str] = _find_ndk_abis()

"""
Returns list of system libs matching specific API level
"""
def _find_system_libs() -> Dict[str, str]:
    if ANDROID_NDK_PATH is not None:
        with open(os.path.join(ANDROID_NDK_PATH, 'meta', 'system_libs.json'), 'r') as f:
            libs = json.loads(f.read())
            for key in libs:
                libs[key] = int(libs[key])
            return libs

    return None

ANDROID_NDK_LIBS = _find_system_libs()

def find_system_libs(api_level : int = None) -> List[str]:
    libs = ANDROID_NDK_LIBS

    if (api_level is not None):
        libs = { k:v for (k, v) in libs.items() if v <= api_level }

    return libs

def find_compiler_paths(api_level : int, abi : str) -> Dict[str, str]:
    if ANDROID_NDK_PATH is not None:
        path = os.path.join(ANDROID_NDK_PATH, 'toolchains', 'llvm', 'prebuilt', 'windows-x86_64')

        path_bin = os.path.join(path, 'bin')

        exec_compiler = os.path.join(path_bin, '{}-linux-android{}-clang++.cmd'.format(
            abi_toolchain_prefix(abi),
            api_level
        ))

        path_lib = os.path.join(
            ANDROID_NDK_PATH,
            'platforms',
            'android-{}'.format(api_level),
            'arch-{}'.format(abi_platform_prefix(abi)),
            'usr',
            abi_platform_libdir(abi)
        )


        return {
            'bin': path_bin,
            'cxx': exec_compiler,
            'cc': exec_compiler,
            'lib': path_lib,
            'link': exec_compiler,
        }
    return None

def is_supported(api_level : int) -> bool:
    return ANDROID_MIN_API_LEVEL <= api_level and api_level <= ANDROID_MAX_API_LEVEL

def is_vulkan_supported(api_level : int) -> bool:
    level = ANDROID_NDK_LIBS.get('libvulkan.so', None)

    if level is not None:
        return api_level >= level
    return False