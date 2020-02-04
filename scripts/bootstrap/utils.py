import platform
import sys

# --------------------------------------------------------------------------------------------------
# CPU architecture support

CPU_ARCHITECTURE_X64    = 'x64'
CPU_ARCHITECTURE_X86    = 'x86'
CPU_ARCHITECTURE_ARMV7  = 'ARMv7'
CPU_ARCHITECTURE_ARMV8  = 'ARMv8'

def _init_cpu_architecture():
    """
    Gets reliable CPU architecture for current system
    """

    machine = platform.machine()

    if machine == 'AMD64' or machine == 'x86_64':
        return CPU_ARCHITECTURE_X64
    raise NotImplementedError("unknown architecture: {}".format(machine))


CPU_ARCHITECTURE = _init_cpu_architecture()


# --------------------------------------------------------------------------------------------------
# System Type

SYSTEM_WINDOWS = 'Windows'
SYSTEM_LINUX   = 'Linux'

def _init_system_type():
    """
    Initializes system type
    """

    if sys.platform.startswith("win32"):
        return SYSTEM_WINDOWS
    if sys.platform.startswith("linux"):
        return SYSTEM_LINUX
    raise NotImplementedError("OS not supported: {}".format(sys.platform))

SYSTEM = _init_system_type()