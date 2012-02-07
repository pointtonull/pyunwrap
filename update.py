#!/usr/bin/env python
#-*- coding: UTF-8 -*-

"""
Este es un script que busca actualizar el repositorio en que se halla
aprovechando git. Debe funcionar en GNU/Linux y en Windows, especialmente en
este último donde es más probable que el entorno esté incompleto o
desactualizado.
"""

from subprocess import Popen, PIPE
from src import autopipe
from src.executables import get_paths

def main():
    "The main routine"
    git_path = get_paths("git")[0]
    print("Feching last version\n")
    commands = ([git_path, "fetch", "-v"],
        [git_path, "stash"],
        [git_path, "rebase", "-v"])
    for command in commands:
        proc = Popen(command, stdout=PIPE)
        for line in iter(proc.stdout.readline, ''):
            print("    " + line)


if __name__ == "__main__":
    exit(main())
