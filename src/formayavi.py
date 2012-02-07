#!/usr/bin/env python
#-*- coding: UTF-8 -*-

import unwrap
from mayavi.mlab import surf as surf
import numpy

def image_surf(image, postblur=3, mirrored=True):
    return surf(unwrap.unwrap_image(image, postblur, mirrored))

def main():
    print("This is just a module")

if __name__ == "__main__":
    exit(main())

