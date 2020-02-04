import os.path
import subprocess
import json

#---------------------------------------------------------------------------------------------------

if 'ProgramFiles(x86)' in os.environ:
    MSVC_DEFAULT_PATH = os.path.join(os.environ['ProgramFiles(x86)'], 'Microsoft Visual Studio', 'Installer', 'vswhere.exe')
else:
    MSVC_DEFAULT_PATH = None

# Version to toolkit mapping
_VS_AVAILABLE_TOOLKITS = {
    '2017': 'v141',
    '2019': 'v142',
}


"""
Finds location of vswhere.exe
"""
def _find_vswhere() -> str:
    if MSVC_DEFAULT_PATH and os.path.exists(MSVC_DEFAULT_PATH):
        return MSVC_DEFAULT_PATH
    return None

"""
Finds msvc installation info from vswhere
"""
def _find_msvc_installation(vswhere : str):
    args : list[str] = [
        vswhere,
        '-utf8',
        '-latest',
        '-products', '*',
        '-format', 'json'
    ]

    result = subprocess.check_output(args).decode('-utf8')
    return json.loads(result)


def get_msvc_compiler_info():
    vswhere = _find_vswhere()

    if (vswhere is not None):
        # Get first available installation for given params
        instance = _find_msvc_installation(vswhere)[0]

        name : str = instance['displayName']
        path : str = instance['installationPath']
        version : str = instance['catalog']['productLineVersion']
        toolkit : str = _VS_AVAILABLE_TOOLKITS[version]
        # check if Microsoft.VCRedistVersion.default.txt exists; else as is

        default_tools : str = os.path.join(path, 'VC', 'Auxiliary', 'Build', f'Microsoft.VCToolsVersion.{toolkit}.default.txt')
        with open(default_tools, 'r') as file:
            tools = file.read().splitlines()[0]

        return {
            'name': name,
            'path': path,
            'version': version,
            'toolkit': toolkit,
            'toolset': tools,
        }
    else:
        return None