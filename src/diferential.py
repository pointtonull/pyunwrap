#!/usr/bin/env python
#-*- coding: UTF-8 -*-

from math import sqrt
import Image
import numpy
import sys

def ribonize(left, right=None):
    if right is None:
        right = left
    else:
        assert left.shape == right.shape
    xlen, ylen = left.shape
    assert xlen == ylen #must be?

    ribon = numpy.zeros(shape=(xlen * 2, ylen * 2))
    for x in xrange(xlen):
        for y in xrange(ylen):
            ribon[x + y + 1, xlen - 1 + x - y] = left[x, y]
            ribon[x + y + 1, xlen     + x - y] = right[x, y]
    return ribon


def derive(array, eps=(1, 0), order=1):
    meps = sqrt(eps[0] ** 2 + eps[1] ** 2)
    xlen, ylen = array.shape

    for time in xrange(order):
        displaced = numpy.zeros_like(array)
        displaced[:xlen - eps[0], :ylen - eps[1]] = array[eps[0]:, eps[1]:]
        array = array - displaced

    return array


def main():
    if len(sys.argv) > 1:
        image = Image.open(sys.argv[1])
        left = numpy.array(image, float)
        right = left
    else:
        left = numpy.ones(shape=(5, 5))
        right = left.copy()
        right.fill(2)
    right = derive(right, (1, 0), 2)
    left = derive(left, (0, 1), 2)
    print left
    print right
    ribon = ribonize(left, right)
    print ribon
    image = Image.fromarray(ribon)
    image.show()

if __name__ == "__main__":
    exit(main())
