#!/usr/bin/env python
#-*- coding: UTF-8 -*-

"""
This is a simple implementation of the Fourier-Mellin Trasform
image = [m, n]
ft_magnitude = |fft(image)|
lp_ft_magnitude = logpolar(ft_magnitude)
fmt = fft(lp_ft_magnitude)
"""

from numpy import pi, arctan2, sqrt, sin, tan, tan, log, log10, cos, exp, zeros, floor
from scipy.ndimage import geometric_transform
import Image
import numpy
import scipy
import sys

tau = 2 * pi

def logpolar(array, scale=1):
    rows, cols = array.shape
    out_rows = rows * scale
    out_cols = cols * scale
    row0 = rows / 2.
    col0 = cols / 2.
    rho_scalar = 2 * exp(1) / out_rows
    theta_scalar = tau / out_cols

    def out2in(dst_coords):
        rho, theta = dst_coords
        rho = rho * rho_scalar
        theta *= theta_scalar
        row_from = exp(rho) * cos(theta) + row0
        col_from = exp(rho) * sin(theta) + col0
        return row_from, col_from

    return geometric_transform(array, out2in, (out_rows, out_cols), order=3)


def main():
    import autopipe
    filename = sys.argv[1]
    print("Openning image file: %s" % filename)
    image = Image.open(filename)
    image = image.convert("L")
    print("Transforming to log polar")
    array = numpy.array(image)
    array = logpolar(array, 4)
    print("Displaying")
    Image.fromarray(array).show(sys.argv[1])

if __name__ == "__main__":
    exit(main())
