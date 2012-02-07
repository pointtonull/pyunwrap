#!/usr/bin/env python
#-*- coding: UTF-8 -*-

from Tkinter import Button, Frame, Label, Text

class Tkpipe(Frame):

    def __init__(self, title="Standard output", label="Propram progress"):
        Frame.__init__(self)
        self.master.title(title)
        self.grid(stick="nsew")
        self.createWidgets()
        self.label = label
        self.closed = False


    def createWidgets(self):
        top = self.winfo_toplevel()

        top.rowconfigure(0, weight=1, minsize=96)
        top.columnconfigure(0, weight=1)

        self.columnconfigure(0, weight=1)

        self.rowconfigure(0, minsize=24)
        self.lbl_pretext = Label(self, text="Update progress:")
        self.lbl_pretext.grid(row=0, sticky="ew")

        self.rowconfigure(1, minsize=48, weight=1)
        self.txt_messages = Text(self)
        self.txt_messages.grid(row=1, sticky="nsew")
        self.txt_messages.tag_config("green", foreground="darkgreen")
        self.txt_messages.tag_config("blue", foreground="darkblue")
        self.txt_messages.tag_config("red", foreground="darkred")

        self.rowconfigure(2, minsize=24)
        self.btn_quit = Button(self, text="Quit", command=self.quit)
        self.btn_quit.grid(row=2, sticky="ew")

        self.update()


    def write(self, line, tag=None):
        self.txt_messages.insert("end", line, tag)
        self.txt_messages.see("end")
        self.txt_messages.update()


    def writelines(self, iterable, tag=None):
        for line in iterable:
            self.write(line, tag)


    def flush(self):
        self.update()


    def close(self):
        if not self.closed:
            self.write("\n-----\nProcess ended\n", "blue")
            self.closed = True
            self.mainloop()


    def default(self, tagname):
        return ColoredPipe(self, tagname)


    def __del__(self, *args):
        self.close()


class ColoredPipe:

    def __init__(self, pipe, tag):
        self.pipe = pipe
        self.default_tag = tag


    def default(self, tagname):
        return ColoredPipe(self.pipe, tagname)


    def write(self, string, tag=None):
        self.pipe.write(string, tag or self.default_tag)


    def writelines(self, iterable, tag=None):
        for line in iterable:
            self.write(line, tag or self.default_tag)

    def flush(self):
        self.pipe.flush()

    def close(self):
        self.pipe.close()

    def __del__(self, *args):
        self.pipe.__del__(*args)
