
import os
import ycm_core

# You can customize this list with your compiler flags
flags = [
  '-Wall',
  '-Wextra',
  '-std=c99',
  '-x', 'c',
  '-I', 'include',  # <-- Important: tells YCM where your headers are
]

# This function is called by YCM
def FlagsForFile(filename, **kwargs):
    return {
        'flags': flags,
        'do_cache': True
    }
