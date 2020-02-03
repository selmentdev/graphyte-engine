# Check where Windows SDK is installed
import sys
import os
from scripts.bootstrap.version import Version

is_windows : bool = sys.platform.startswith("win32")

if is_windows:
    import winreg

"""
Enumerates all available Windows SDKs found in registry
"""
def _enumerate_all_windows_10_sdk_kits():
    # Open root key
    root_path : str = r"SOFTWARE\WOW6432Node\Microsoft\Windows Kits\Installed Roots"
    root_key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, root_path, 0, winreg.KEY_READ)

    # Try to find Windows 10 location
    for i in range(0, winreg.QueryInfoKey(root_key)[1]):
        (name, value, kind) = winreg.EnumValue(root_key, i)

        if (name.startswith('KitsRoot10') and kind == winreg.REG_SZ):
            windows_sdk_location = value
            break

    # Options required by engine in order to build
    required_options : set[str] = {
        'OptionId.DesktopCPPx64',
        'OptionId.DesktopCPParm64',
        'OptionId.SigningTools'
    }


    windows_sdk_kits : List[Version] = []

    # Enumerate all versions of Windows SDK
    for i in range(0, winreg.QueryInfoKey(root_key)[0]):
        version : str = winreg.EnumKey(root_key, i)

        if version.startswith("10."):
            try:
                kit = winreg.OpenKey(root_key, version, 0, winreg.KEY_READ)
                options = winreg.OpenKey(kit, 'Installed Options', 0, winreg.KEY_READ)

                options_found : List[str] = []

                for k in range(0, winreg.QueryInfoKey(options)[1]):
                    (name, value, kind) = winreg.EnumValue(options, k)

                    if name.startswith('OptionId'):
                        options_found.append(name)

                if required_options.issubset(options_found):
                    windows_sdk_kits.append(Version(version))
            except FileNotFoundError as e:
                pass

    return (windows_sdk_location, windows_sdk_kits)


"""
Finds location of specific Windows SDK.

If version is none, it tries to find latest one instead
"""
def find_windows_sdk(version : str = None) -> (str, str):
    if is_windows:
        (location, kits) = _enumerate_all_windows_10_sdk_kits()

        if (version is None):
            selected = max(kits)
        else:
            selected = next((x for x in kits if x == version), None)

        return (location, selected)
    else:
        return (None, None)


"""
Finds Vulkan SDK
"""
def find_vulkan_sdk() -> str:
    sdk = os.getenv('VULKAN_SDK')

    if (sdk is not None):
        # SDK subdirectories to check
        dir_include = os.path.join(sdk, 'Include')
        dir_lib = os.path.join(sdk, 'Lib')
        dir_bin = os.path.join(sdk, 'Bin')

        if not os.path.exists(os.path.join(dir_include, 'vulkan/vulkan.h')):
            # Header file is required
            return None

        # We are good :)
        return sdk
    else:
        # :(
        return None