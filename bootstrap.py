#!/usr/bin/python
import subprocess
import os
import platform
import datetime
import math
import uuid
import hashlib
import sys
import logging
import re
import json
import functools
import argparse

import scripts.bootstrap.windows as windows
import scripts.bootstrap.android as android
import scripts.bootstrap.linux as linux
import scripts.bootstrap.vulkan as vulkan
import scripts.bootstrap.msvc as msvc
import scripts.bootstrap.dcvs as dcvs
from scripts.bootstrap.version import Version

assert(sys.version_info[0] == 3)

#---------------------------------------------------------------------------------------------------
# Internal commands

def _bootstrap_emit_header(file):
    file.write('// -------------------------------------------------------------------------------------------------\n')
    file.write("// This file was generated by 'bootstrap.py'\n\n")


#---------------------------------------------------------------------------------------------------
# Generate BFF file with MSVC compiler

def generate_msvc_compiler_info():
    compiler = msvc.get_msvc_compiler_info()

    if compiler is not None:
        vsname = compiler['name']
        vspath = compiler['path']
        vsversion = compiler['version']
        vstoolkit = compiler['toolkit']
        vstoolset = compiler['toolset']

        #
        # Get Windows Kits locations
        #

        windows_sdk_version : int = 10
        (windows_sdk_location, windows_sdk_kit) = windows.find_windows_sdk()
        print('Using Windows SDK "{}"'.format(windows_sdk_kit))
    else:
        windows_sdk_version : int = -1
        windows_sdk_location = '/dev/null'
        windows_sdk_kit : str = 'unknown'
        vspath : str = '/dev/null'
        vsname : str = '/dev/null'
        vstoolset : str = '/dev/null'
        vsversion : str = ''
        vstoolkit : str = ''

    # Generate header
    with open('scripts/compiler.msvs.bff', 'w') as f:
        _bootstrap_emit_header(f)

        f.write(".VsToolsLocation = '{}'\n".format(vspath))
        f.write(".VsToolsName = '{}'\n".format(vsname))
        f.write(".VsToolsVersion = '{}'\n".format(vstoolset))
        f.write(".VsVersion = '{}'\n".format(vsversion))
        f.write(".VsPlatformToolset = '{}'\n".format(vstoolkit))
        f.write(".WindowsSdkLocation = '{}'\n".format(os.path.normpath(windows_sdk_location)))
        f.write(".WindowsKitVersion = '{}'\n".format(windows_sdk_version))
        f.write(".WindowsSdkVersion = '{}'\n".format(windows_sdk_kit))

def generate_version_file():
    os.makedirs('./engine/include/Graphyte', exist_ok=True)

    with open('engine/include/Graphyte/Build.Version.hxx', 'w+') as file:
        # Gather system and platform version for builder machine
        os_version : str = platform.version()
        os_release : str = platform.release()
        os_system : str = platform.system()
        os_platform : str = platform.platform()
        os_node : str = platform.node()

        # Gather source control info
        build_commit : str = dcvs.get_commit_id()
        build_commit_short : str = dcvs.get_commit_id_short()
        build_branch : str = dcvs.get_branch_name()

        date : datetime = datetime.datetime.now()

        build_version_major : int = date.year - 2000
        build_version_minor : int = date.month
        build_version_release : int = date.timetuple().tm_yday
        build_version_build : int = math.floor((date - datetime.datetime(year = 2000, day = 1, month = 1)).total_seconds() / (60 * 15))
        build_timestamp : str = date.strftime("%Y-%m-%dT%H:%M:%S")
        build_uuid : str = hashlib.sha256(b'graphyte').hexdigest()[0:32]

        file.write('#define GRAPHYTE_BUILD_OS_VERSION        "{}"\n'.format(os_version))
        file.write('#define GRAPHYTE_BUILD_OS_RELEASE        "{}"\n'.format(os_release))
        file.write('#define GRAPHYTE_BUILD_OS_SYSTEM         "{}"\n'.format(os_system))
        file.write('#define GRAPHYTE_BUILD_OS_PLATFORM       "{}"\n'.format(os_platform))
        file.write('#define GRAPHYTE_BUILD_OS_NODE           "{}"\n'.format(os_node))

        file.write('#define GRAPHYTE_BUILD_COMMIT            "{}"\n'.format(build_commit[0] or "<unknown>"))
        file.write('#define GRAPHYTE_BUILD_COMMIT_SHORT      "{}"\n'.format(build_commit_short[0] or "<unknown>"))
        file.write('#define GRAPHYTE_BUILD_BRANCH            "{}"\n'.format(build_branch[0] or "<unknown>"))
        file.write('#define GRAPHYTE_BUILD_UUID              "{}"\n'.format(build_uuid))
        file.write('#define GRAPHYTE_BUILD_VERSION           "{}.{}.{}.{}"\n'.format(
            build_version_major,
            build_version_minor,
            build_version_release,
            build_version_build
        ))

        file.write('#define GRAPHYTE_BUILD_VERSION_MAJOR     {}\n'.format(build_version_major))
        file.write('#define GRAPHYTE_BUILD_VERSION_MINOR     {}\n'.format(build_version_minor))
        file.write('#define GRAPHYTE_BUILD_VERSION_RELEASE   {}\n'.format(build_version_release))
        file.write('#define GRAPHYTE_BUILD_VERSION_BUILD     {}\n'.format(build_version_build))
        file.write('#define GRAPHYTE_BUILD_TIMESTAMP         "{}"\n'.format(build_timestamp))

def _emit_separator(f):
    f.write('// -------------------------------------------------------------------------------------------------\n')

def _emit_toolchain_triplet(f, platform, architecture, compiler):
    varname = '.TripletDef_{}_{}_{}'.format(platform, architecture, compiler)
    _emit_separator(f)
    f.write('// Triplet definition {}-{}-{}\n'.format(platform, architecture, compiler))
    f.write('{} = [\n'.format(varname))
    f.write('    .Triplet_Platform = \"{}\"\n'.format(platform))
    f.write('    .Triplet_Architecture = \"{}\"\n'.format(architecture))
    f.write('    .Triplet_Compiler = \"{}\"\n'.format(compiler))
    f.write(']\n')
    f.write('.Global_Triplets + {}\n\n'.format(varname))


def generate_compilers_gen_bff():
    with open('scripts/compilers.gen.bff', 'w') as f:
        _emit_separator(f)
        f.write('// Generated by bootstrap.py\n\n')
        _emit_toolchain_triplet(f, 'Windows', 'ARMv8', 'MSVC')
        _emit_toolchain_triplet(f, 'Windows', 'x64', 'MSVC')
        _emit_toolchain_triplet(f, 'Linux', 'x64', 'GCC')




if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument('--ndk', help='specifies Android API level', default=24, type=int)
    parser.add_argument('--verbose', action='store_true')
    args = parser.parse_args()

    generate_version_file()
    generate_msvc_compiler_info()
    generate_compilers_gen_bff()

    print(dcvs.get_branch_name())
    print(dcvs.get_commit_id())
    print(dcvs.get_commit_id_short())
    print(vulkan.find_vulkan_sdk())
    print(windows.find_windows_sdk())
    print(android.ANDROID_MIN_API_LEVEL)
    print(android.ANDROID_MAX_API_LEVEL)
    print(android.ANDROID_NDK_ABIS)
    print(android.ANDROID_NDK_LIBS)
    print(android.find_system_libs(24))
    print(android.find_compiler_paths(24, 'armv8'))
    print(android.is_vulkan_supported(16))
    print(android.is_vulkan_supported(24))
    print(android.is_vulkan_supported(26))