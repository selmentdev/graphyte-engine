import os

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