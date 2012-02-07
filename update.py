#!/usr/bin/env python
#-*- coding: UTF-8 -*-

"""
Este es un script que busca actualizar el repositorio en que se halla
aprovechando git. Debe funcionar en GNU/Linux y en Windows, especialmente en
este último donde es más probable que el entorno esté incompleto o
desactualizado.
"""

from subprocess import Popen, PIPE
import os
import sys
from Tkinter import Button, Frame, Label, Text

APP_NAME = "update"
if os.name in ("posix"):
    HAPP_NAME = "." + APP_NAME
else:
    HAPP_NAME = "" + APP_NAME

LOG_FILE = os.path.expanduser("~/%s.log" % (HAPP_NAME))
VERBOSE = 20


def get_paths(command):
    """
    return a list of the abspath to executables of <command> except this file
    """
    try:
        my_path = os.path.realpath(__file__)
    except:
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


def write(text, destination):
    """
    Shortcut to append text to destination and flush
    """
    DEBUG("""write::writing "%s" to %s""" % (text, destination))
    fileo = open(destination, "a")
    fileo.write("%s\n" % text.encode("UTF-8", "replace"))
    fileo.close()

LOG = lambda string: write(string, LOG_FILE)


class Interface(Frame):

    def __init__(self, title="Standard output", label="Propram progress"):
        Frame.__init__(self)
        self.master.title(title)
        self.grid(stick="nsew")
        self.createWidgets()
        self.label = label


    def createWidgets(self):
        top = self.winfo_toplevel()

        top.rowconfigure(0, weight=1, minsize=96)
        top.columnconfigure(0, weight=1)

        self.columnconfigure(0, weight=1)

        self.rowconfigure(0, minsize=24)
        self.lbl_pretext = Label(self, text="Update progress:")
        self.lbl_pretext.grid(row=0, sticky="nwsw")

        self.rowconfigure(1, minsize=48, weight=1)
        self.txt_messages = Text(self)
        self.txt_messages.grid(row=1, sticky="nsew")

        self.rowconfigure(2, minsize=24)
        self.btn_quit = Button(self, text="Quit", command=self.quit)
        self.btn_quit.grid(row=2, sticky="ew")

        self.update()


    def put_line(self, line):
        self.txt_messages.insert("end", line)
        self.txt_messages.see("end")
        self.txt_messages.update()




def main():
    "The main routine"
    git_path = get_paths("git")[0]
    gui = Interface()
    gui.put_line("Feching last version")
    commands = ("fetch", "stash", "rebase")
    for command in commands:
        proc = Popen([git_path, command], stdout=PIPE)
        for line in iter(proc.stdout.readline, ''):
               gui.put_line(line)
    gui.mainloop()



if __name__ == "__main__":
    exit(main())
