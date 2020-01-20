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

is_win : bool = sys.platform == "win32"

assert(sys.version_info[0] == 3)
if is_win:
    import winreg


#---------------------------------------------------------------------------------------------------
# Version class util
class Version:
    component_re = re.compile(r'(\d+ | \.)', re.VERBOSE)

    def __init__(self, s : str = None):
        if s:
            self.parse(s)

    def parse(self, s : str):
        parts : List[str] = [x for x in filter(lambda x: x and x != '.', self.component_re.split(s))]

        self.components : List[int] = []

        for i in range(len(parts)):
            self.components.append(int(parts[i]))

    def __str__(self):
        return '.'.join([str(x) for x in self.components])

    def __eq__(self, other):
        return Version.__cmp(self, other) == 0

    def __lt__(self, other):
        return Version.__cmp(self, other) < 0

    def __gt__(self, other):
        return Version.__cmp(self, other) > 0

    def __le__(self, other):
        return Version.__cmp(self, other) <= 0

    def __ge__(self, other):
        return Version.__cmp(self, other) >= 0

    @staticmethod
    def __cmp(lhs, rhs):
        i = 0
        while True:
            if i == len(lhs.components):
                if i == len(rhs.components):
                    return 0
                else:
                    return -1
            else:
                if i == len(rhs.components):
                    return 1
                elif lhs.components[i] != rhs.components[i]:
                    return lhs.components[i] - rhs.components[i]
            i = i + 1

#---------------------------------------------------------------------------------------------------
# Internal commands

def _bootstrap_execute_command(args):
    try:
        return subprocess.check_output(args).decode('utf-8').splitlines()
    except:
        return None

def _bootstrap_emit_header(file):
    file.write('//--------------------------------------------------------------------------------------------------\n')
    file.write("// This file was generated by 'bootstrap.py'\n\n")


#---------------------------------------------------------------------------------------------------
# MSVS Locator service

if 'ProgramFiles(x86)' in os.environ:
    MSVC_DEFAULT_PATH = os.path.join(os.environ['ProgramFiles(x86)'], 'Microsoft Visual Studio', 'Installer', 'vswhere.exe')
else:
    MSVC_DEFAULT_PATH = None

def _msvc_find_vswhere():
    if MSVC_DEFAULT_PATH and os.path.exists(MSVC_DEFAULT_PATH):
        return MSVC_DEFAULT_PATH

    return None

def _msvc_get_installation(vswhere):
    args : List[str] = [
        vswhere,
        '-utf8',
        '-latest',
        '-products', '*',
        '-format', 'json'
    ]

    result = subprocess.check_output(args).decode('utf-8')
    return json.loads(result)

def _locate_windows10_sdk_kits():
    roots_key : str = r"SOFTWARE\Microsoft\Windows Kits\Installed Roots"
    roots = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, roots_key, 0, winreg.KEY_READ)

    for i in range(0, winreg.QueryInfoKey(roots)[1]):
        (name, value, kind) = winreg.EnumValue(roots, i)

        if (name.startswith('KitsRoot10') and kind == winreg.REG_SZ):
            windows_sdk_location = value

    windows_sdk_kits : List[Version] = []

    for i in range(0, winreg.QueryInfoKey(roots)[0]):
        version : str = winreg.EnumKey(roots, i)

        if version.startswith("10."):
            windows_sdk_kits.append(Version(version))

    return (windows_sdk_location, windows_sdk_kits)

def _find_highest_version(versions):
    return max(versions)

#---------------------------------------------------------------------------------------------------
# Generate BFF file with MSVC compiler

def generate_msvc_compiler_info():
    if is_win:
        vswhere : str = _msvc_find_vswhere()
        vsinstance : str = _msvc_get_installation(vswhere)[0]
        vsname : str = vsinstance['displayName']
        vspath : str = vsinstance['installationPath']

        msvs_tools_version_location : str = os.path.join(vspath, 'VC', 'Auxiliary', 'Build', 'Microsoft.VCToolsVersion.default.txt')
        with open(msvs_tools_version_location, 'r') as file:
            vstools = file.read().splitlines()[0]

        #
        # Get Windows Kits locations
        #

        windows_sdk_version : int = 10
        (windows_sdk_location, windows_sdk_kits) = _locate_windows10_sdk_kits()
    else:
        windows_sdk_version : int = -1
        windows_sdk_location = '/dev/null'
        windows_sdk_kits : List[Version] = [Version('0.0.0.0')]
        vspath : str = '/dev/null'
        vsname : str = '/dev/null'
        vstools : str = '/dev/null'

    # Generate header
    with open('scripts/compiler.msvs.bff', 'w') as f:
        _bootstrap_emit_header(f)

        f.write(".VsToolsLocation = '{}'\n".format(vspath))
        f.write(".VsToolsName = '{}'\n".format(vsname))
        f.write(".VsToolsVersion = '{}'\n".format(vstools))
        f.write(".WindowsSdkLocation = '{}'\n".format(os.path.normpath(windows_sdk_location)))
        f.write(".WindowsKitVersion = '{}'\n".format(windows_sdk_version))
        f.write(".WindowsSdkVersion = '{}'\n".format(max(windows_sdk_kits)))

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
        build_commit : str = _bootstrap_execute_command(['git', 'log', '-1', '--format=%H'])
        build_commit_short : str = _bootstrap_execute_command(['git', 'log', '-1', '--format=%h'])
        build_branch : str = _bootstrap_execute_command(['git', 'rev-parse', '--abbrev-ref', 'HEAD'])

        date : datetime = datetime.datetime.now()

        build_version_major : int = date.year - 2000
        build_version_minor : int = date.month
        build_version_release : int = date.timetuple().tm_yday
        build_version_build : int = math.floor((date - datetime.datetime(year = 2000, day = 1, month = 1)).total_seconds() / (60 * 15))
        build_timestamp : str = date.strftime("%Y-%m-%dT%H:%M:%SZ")
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

if __name__ == "__main__":
    generate_version_file()
    generate_msvc_compiler_info()
