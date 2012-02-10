#!/usr/bin/env python
#-*- coding: UTF-8 -*-

from distutils.core import setup
import py2exe
import sys

sys.path.append("")

setup(
    windows=['update.pyw'],
        options={
            "py2exe":{
                "unbuffered": True,
                "optimize": 2,
                "includes": ["src.autopipe", "src.tkpipe"]
            }
        }
)
