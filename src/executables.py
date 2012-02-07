#!/usr/bin/env python
#-*- coding: UTF-8 -*-

import os

def get_paths(command):
    """
    return a list of the abspath to executables of <command> except this file
    """
    try:
        my_path = os.path.realpath(__file__)
    except NameError:
        my_path = None

    posibles = {
        "posix" : ["%s"],
        "nt" : ["%s.exe", "%s.cmd", "%s.com", "%s.bat"]
        }[os.name]
    posibles = [pos % command for pos in posibles]

    paths = []
    for command in posibles:
        paths += [os.path.realpath(os.path.join(path, command))
            for path in os.environ["PATH"].split(os.pathsep)
                if os.path.exists(os.path.join(path, command))]
    paths = [path for path in paths if path != my_path]
    return paths
