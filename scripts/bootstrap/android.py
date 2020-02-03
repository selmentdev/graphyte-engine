import sys
import os
import json
from typing import List, Dict

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

    return (None, None)

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
