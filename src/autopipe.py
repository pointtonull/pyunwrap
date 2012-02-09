#!/usr/bin/env python
#-*- coding: UTF-8 -*-

import os
import sys

if os.name in ("nt", "posix"):
    import tkpipe
    pipe = tkpipe.Tkpipe()
    sys.stdout = pipe.default("green")
    sys.stderr = pipe.default("red")
