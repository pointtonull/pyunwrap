#!/usr/bin/env python
#-*- coding: UTF-8 -*-

"""
Este es un script que busca actualizar el repositorio en que se halla
aprovechando git. Debe funcionar en GNU/Linux y en Windows, especialmente en
este último donde es más probable que el entorno esté incompleto o
desactualizado.
"""

from Queue import Queue, Empty
from src import autopipe
from src.executables import get_paths
from subprocess import Popen, PIPE, STARTUPINFO, SW_HIDE, STARTF_USESHOWWINDOW
from threading  import Thread
import sys
import webbrowser

assert 'posix' not in sys.builtin_module_names


def enqueue_output(out, queue):
    for line in iter(out.readline, ''):
        queue.put(line)
    out.close()


def main():
    "The main routine"
    git_paths = get_paths("git")
    easy_install_paths = get_paths("easy_install")

    error_message = """
----
ERROR: couldt find a valid %s installation

"""

    if not git_paths:
        sys.stderr.write(error_message % "GIT")
        sys.stderr.write("Redirecting to the download webpage.")
        sys.stderr.write("Download, install and retry please.")
        webbrowser.open("https://code.google.com/p/msysgit/downloads/detail?"
            "name=Git-1.7.9-preview20120201.exe")
        return 1

    elif not easy_install_paths:
        sys.stderr.write(error_message % "EASY_INSTALL")
        sys.stderr.write("Starting installer.")
        webbrowser.open("")
        commands = (["src\\setuptools.exe"])

    else:

        commands = (
            [git_paths, "stash"],
            [git_paths, "fetch", "-v"],
            [git_paths, "rebase", "-v"]
        )


    info = STARTUPINFO()
    info.dwFlags |= STARTF_USESHOWWINDOW
    info.wShowWindow = SW_HIDE

    for command in commands:
        print(" ".join(command))
        proc = Popen(command, stdout=PIPE, stderr=PIPE, bufsize=1,
            close_fds=False, startupinfo=info)

        stdout_queue = Queue()
        stdout = Thread(target=enqueue_output, args=(proc.stdout,
            stdout_queue))
        stdout.daemon = True
        stdout.start()

        stderr_queue = Queue()
        stderr = Thread(target=enqueue_output, args=(proc.stderr,
            stderr_queue))
        stderr.daemon = True
        stderr.start()

        while proc.poll() is None:

            try:
                line = stdout_queue.get_nowait()
            except Empty:
                pass
            else:
                sys.stdout.write(line)

            try:
                line = stderr_queue.get_nowait()
            except Empty:
                pass
            else:
                sys.stderr.write(line)


if __name__ == "__main__":
    exit(main())
