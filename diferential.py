#!/usr/bin/env python
#-*- coding: UTF-8 -*-

def FCT(array):
    o_xlen, o_ylen = array.shape
    ct_array = numpy.zeros(shape=(o_xlen * 2, o_ylen * 2))
    for x in xrange(o_xlen):
        for y in xrange(o_xlen):
            ct_array[o_xlen - 1 + x - y, x + y] += array(x, y)
            ct_array[o_xlen + x - y, x + y] += array(x, y)
            ct_array[o_xlen - 1 + x - y, x + y] -= array(x, y)
            ct_array[o_xlen + x - y, x + y] -= array(x, y)

def main():
    pass

if __name__ == "__main__":
    exit(main())
