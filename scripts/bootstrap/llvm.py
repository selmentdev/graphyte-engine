import sys
import os

def find_llvm_windows() -> str:
    path = os.getenv('LLVM_PATH')

    if path is not None:
        return path
    return ''
