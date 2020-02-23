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
import scripts.bootstrap.utils as utils
import scripts.bootstrap.llvm as llvm
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

    llvm_path = llvm.find_llvm_windows()

    # Generate header
    with open('scripts/compiler.msvs.bff', 'w') as f:
        _bootstrap_emit_header(f)

        f.write(f".VsToolsLocation = '{vspath}'\n")
        f.write(f".VsToolsName = '{vsname}'\n")
        f.write(f".VsToolsVersion = '{vstoolset}'\n")
        f.write(f".VsVersion = '{vsversion}'\n")
        f.write(f".VsPlatformToolset = '{vstoolkit}'\n")
        f.write(f".WindowsSdkLocation = '{os.path.normpath(windows_sdk_location)}'\n")
        f.write(f".WindowsKitVersion = '{windows_sdk_version}'\n")
        f.write(f".WindowsSdkVersion = '{windows_sdk_kit}'\n")
        f.write(f".WindowsLlvmPath = '{llvm_path}'\n")

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

def _emit_toolchain_triplet(f, platform, architecture, compiler, msbuild_platform):
    varname = '.TripletDef_{}_{}_{}'.format(platform, architecture, compiler)
    _emit_separator(f)
    f.write(f'// Triplet definition {platform}-{architecture}-{compiler}\n')
    f.write(f'{varname} = [\n')
    f.write(f'    .Triplet_Platform = "{platform}"\n')
    f.write(f'    .Triplet_Architecture = "{architecture}"\n')
    f.write(f'    .Triplet_Compiler = "{compiler}"\n')
    f.write(f'    .MsBuildPlatform = "{msbuild_platform}"\n')
    f.write(']\n')
    f.write(f'.Global_Triplets + {varname}\n\n')

def _emit_host_information(f):
    _emit_separator(f)
    f.write('// Host information\n')
    f.write('.HostPlatform = [\n')
    f.write('    .Architecture = "{}"\n'.format(utils.CPU_ARCHITECTURE))
    f.write('    .System = "{}"\n'.format(utils.SYSTEM))
    f.write(']\n')


def generate_compilers_gen_bff():
    with open('scripts/compilers.gen.bff', 'w') as f:
        _emit_separator(f)
        f.write('// Generated by bootstrap.py\n\n')
        _emit_host_information(f)
        _emit_toolchain_triplet(f, 'Windows', 'ARMv8', 'MSVC', 'ARM64')
        _emit_toolchain_triplet(f, 'Windows', 'x64', 'MSVC', 'x64')

        if linux.is_linux:
            _emit_toolchain_triplet(f, 'Linux', 'x64', 'GCC', 'Linux')

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument('--ndk', help='specifies Android API level', default=24, type=int)
    parser.add_argument('--verbose', action='store_true')
    args = parser.parse_args()

    generate_version_file()
    generate_msvc_compiler_info()
    generate_compilers_gen_bff()

    #print(dcvs.get_branch_name())
    #print(dcvs.get_commit_id())
    #print(dcvs.get_commit_id_short())
    #print(vulkan.find_vulkan_sdk())
    #print(windows.find_windows_sdk())
    #print(android.ANDROID_MIN_API_LEVEL)
    #print(android.ANDROID_MAX_API_LEVEL)
    #print(android.ANDROID_NDK_ABIS)
    #print(android.ANDROID_NDK_LIBS)
    #print(android.find_system_libs(24))
    #print(android.find_compiler_paths(24, 'armv8'))
    #print(android.is_vulkan_supported(16))
    #print(android.is_vulkan_supported(24))
    #print(android.is_vulkan_supported(26))
    #print(utils.CPU_ARCHITECTURE)
