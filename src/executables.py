#!/usr/bin/env python
#-*- coding: UTF-8 -*-

import os
import sys

def get_paths(command):
    """
    return a list of the abspath to executables of <command> except this file
    """
    try:
        my_path = os.path.realpath(__file__)
    except NameError:
        my_path = None

    # because windows sucks  ╮（╯＿╰）╭
    dirs = os.environ["PATH"].split(os.pathsep)
    if os.name in ("posix",):
        exts = ["%s"]
    elif os.name == "nt":
        exts = ["%s" + ext for ext in os.environ["PATHEXT"].split(";")]
        python_scripts = (os.path.join(path, "Scripts") for path in sys.path)
        python_scripts = [path for path in python_scripts
            if os.path.isdir(path)]
        dirs += python_scripts
    else:
        raise NotImplementedError("Operative system not recognized.")
    
    posibles = [pos % command for ext in exts]

    paths = []
    for command in posibles:
        all_paths = (os.path.realpath(os.path.join(dirname, command))
            for dirname in dirs)
        paths += [path for path in all_paths if os.path.exists(path)]

    paths = [path for path in paths if path != my_path]
    return paths
