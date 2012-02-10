#!/usr/bin/env python
#-*- coding: UTF-8 -*-

from distutils.core import setup
import py2exe

setup(
    windows=['../../update.pyw']
    console=['../../src/autopipe.py'],
)
