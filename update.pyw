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

assert 'posix' not in sys.builtin_module_names


def enqueue_output(out, queue):
    for line in iter(out.readline, ''):
        queue.put(line)
    out.close()


def main():
    "The main routine"
    git_path = get_paths("git")[0]
    commands = (
        [git_path, "stash"],
        [git_path, "fetch", "-v"],
        [git_path, "rebase", "-v"]
    )

    info = STARTUPINFO()
    info.dwFlags |= STARTF_USESHOWWINDOW
    info.wShowWindow = SW_HIDE

    for command in commands:
        proc = Popen(command, stdout=PIPE, stderr=PIPE, bufsize=1,
            close_fds=False)

        stdout_queue = Queue()
        stdout = Thread(target=enqueue_output, args=(proc.stdout, stdout_queue))
        stdout.daemon = True
        stdout.start()

        stderr_queue = Queue()
        stderr = Thread(target=enqueue_output, args=(proc.stderr, stderr_queue))
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
