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


def enqueue_output(out, queue):
    for line in iter(out.read, ''):
        queue.put(line)
    out.close()


def non_blocking_proc(command):
    sys.stderr.write("» Launch: %s\n" % (" ".join(command)).lower(), "blue")
    info = STARTUPINFO()
    info.dwFlags |= STARTF_USESHOWWINDOW
    info.wShowWindow = SW_HIDE

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
            sys.stdout.write("    " + line)

        try:
            line = stderr_queue.get_nowait()
        except Empty:
            pass
        else:
            sys.stderr.write("    " + line)

    return proc.returncode


def check_module(name, module):
    sys.stdout.write("    Cheking %s: " % name, "blue")
    try:
        module = __import__(module)
        print "pass"
        return module
    except ImportError:
        sys.stderr.write("fail\n")
        return False


def execute(path):
    sys.stderr.write("""***     Executing installer\n"""
        """***     execute & retry\n""")
    return non_blocking_proc([path])


def download(url):
    sys.stderr.write("""***     Fetching installer\n"""
        """***     execute & retry\n""")
    return webbrowser.open(url)


def easy_install(module):
    easy_install_paths = get_paths("easy_install")
    command = [easy_install_paths[0], module]
    non_blocking_proc(command)


def pip_install(module):
    pip_paths = get_paths(r"pip")
    command = [pip_paths[0], "install", module]
    non_blocking_proc(command)


def message(text, color="blue"):
    return sys.stderr.write(text, color)


def main():
    "The main routine"

    message("Verifing git: ")
    git_paths = get_paths(r"git\cmd\git")
    if git_paths:
        print("pass")
    else:
        message("fail\n", "red")
        download("http://msysgit.googlecode.com/files/"
            "Git-1.7.9-preview20120201.exe")
        return 1

    message("Verifing valid repository: ")
    if os.path.isdir(".git"):
        print("pass")
    else:
        message("fail\n", "red")
        message("Attempting to clone the repository at the current location\n"
            "blue")
        non_blocking_proc([git_paths[0], "clone",
            "git://github.com/pointtonull/pyunwrap.git"])
        message("""\n\nMust execute "update.pyw".""")
        return

    commands = (
        [git_paths[0], "stash"],
        [git_paths[0], "fetch", "-v"],
        [git_paths[0], "rebase", "-v"]
    )

    for command in commands:
        non_blocking_proc(command)

    methods = {
        "executable" : execute,
        "easy_install" : easy_install,
        "download" : download,
        "pip" : pip_install
    }

    sys.stderr.write("\nTesting dependencies:\n")
    lines = (line.strip().split(";") for line in open("dependencies.txt"))
    for name, module, method, argument in lines:
        if not check_module(name, module):
            methods[method](argument)


if __name__ == "__main__":
    exit(main())
