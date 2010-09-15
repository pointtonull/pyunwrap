#!/usr/bin/env python
#-*- coding: UTF-8 -*-

"""
Unwrap phase images
"""

from scipy import signal
import Image
import numpy
from punwrap import unwrap2D as unwrap
from math import pi, exp
import sys
from debug import debug


def gauss_kern(size, sizey=None):
    """ Returns a normalized 2D gauss kernel array for convolutions """
    size = int(size)
    if not sizey:
        sizey = size
    else:
        sizey = int(sizey)
    x, y = numpy.mgrid[-size:size + 1, -sizey:sizey + 1]
    g = numpy.exp(-(x ** 2 / float(size) + y ** 2 / float(sizey)))
    return g / g.sum()


def blur_image(im, n, ny=None) :
    """ blurs the image by convolving with a gaussian kernel of typical
        size n. The optional keyword argument ny allows for a different
        size in the y direction.
    """
    g = gauss_kern(n, sizey=ny)
    improc = signal.convolve(im, g, mode='valid')
    return improc


def unwrap_image(image, postblur=0, mirrored=True):
    if issubclass(type(image), basestring):
        image = Image.open(image)


    image = image.convert("L")

    array = numpy.array(image, float)

    width, height = array.shape

    if mirrored:
        array = numpy.append(array[::-1], numpy.append(array[1:-1],
            array[::-1], 0), 0)
        array = numpy.append(array[:,::-1], numpy.append(array[:, 1:-1],
            array[:, ::-1], 1), 1)

    array = (array * 2 * pi / 256) - pi

    array = unwrap(array)

    array -= array.min()
    array /= array.max() / 255

    if postblur:
        array = blur_image(array, postblur)

    if mirrored:

        tiles = [array[
            i * (width - 1) : (i + 1) * width - i,
            j * (height - 1) : (j + 1) * height - j]
            for i in range(3)
                for j in range(3)]

        minstd = None
        for tile in tiles:
            currentstd = numpy.std(tile)
            debug(currentstd)
            if (-currentstd) > minstd:
                minstd = -currentstd
                array = tile

        debug(minstd)


    image = Image.fromarray(array)

    return image


def main():
    if len(sys.argv) == 1:
        print("Se debe especificar al menos un fichero de entrada.")
    else:
        image = Image.open(sys.argv[1])
        uw_image = unwrap_image(image)

        if len(sys.argv) == 2:
            image.show()
            uw_image.show()
            return True
        elif len(sys.argv) == 3:
            uw_image.convert("RGB").save(sys.argv[2])
            print("Imagen guardada con exito.")
            return True
        else:
            print("Cantidad de parametros erronea.")

    return None

if __name__=='__main__':
    exit(main())

