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
from math import atan
from scipy import ndimage
import Image
import numpy
import scipy
import sys

tau = 2 * pi # For god sake


def coord_logpol2car(coords, shape, origin):
    x, y = coords
    x0, y0 = origin
    xdiff = x - x0
    ydiff = y - y0
    rho = log(sqrt(xdiff ** 2 + ydiff ** 2))
    theta = arctan2(ydiff, xdiff)
    theta_index = round((theta + pi) * shape[1] / tau)
    return (rho, theta_index)


def array_logpol2car(array, order=3):
    shape = array.shape
    out_shape = shape[0] * 2, shape[1] * 2
    origin = shape[0], shape[0]

    return ndimage.geometric_transform(array, coord_logpol2car, out_shape,
        order=order, extra_keywords={'shape': shape, 'origin': origin})



def logpolar(input):
    output = numpy.zeros_like(input)
    rows, cols = input.shape
    print(input.shape)
    dTheta = 2 * pi / cols
    base = 10 ** (log10(rows) / rows);
    for x in range(cols):
        for y in range(rows):
            radius = base ** x
            theta = y * dTheta
            xx = round(radius * cos(theta) + cols / 2)
            yy = round(radius * sin(theta) + rows / 2)
            if xx > 0 and  yy > 0 and xx < rows and yy < cols:
                output[x, y] = input[xx, yy]
    return output



def arctan(x, y):
    r'''
    Returns the arc tangent at the point (x, y), in radians.

    This functuion defines the arc tangent as the angle between the line
    segment [(0,0), (x, y)] and the x-axis, always measured in the
    counter-clockwise direction. This is different from Python's math.atan()
    function, which works in the range [-0.5*pi, 0.5*pi].

    Because the tangent function is undefined for points over the y-axis,
    and always zero por points over the x-axis, the following conventions
    have been established for those cases:

    * Points over the x-axis have an arc tangent value of zero for all
      non-negative values of x, and value pi for all negative values;

    * Points over the y-axis have an arc tangent value of 0.5*pi for all
      non-negative values of y, and 1.5*pi for all negative values.

    Also, it should be noted that it is not possible to obtain an arc
    tangent of value 2*pi, since it would mean a full circle back into the
    positive x-axis - and the zero value has already been conventioned for
    that region.
    '''

    if y == 0:
        return 0 if x >= 0 else pi
    elif x == 0:
        return 0.5 * pi if y >= 0 else 1.5 * pi

    r = atan(abs(y / x))

    if x > 0 and y > 0:
        return r
    elif x < 0 and y > 0:
        return pi - r
    elif x < 0 and y < 0:
        return pi + r
    else:
        return 2 * pi - r


def max_rho(array, x0=None, y0=None):
    x0 = x0 or array.shape[1] / 2
    y0 = y0 or array.shape[0] / 2
    
    (rows, cols) = array.shape
    xmax = float(max(x0, cols - x0))
    ymax = float(max(y0, rows - y0))
    return (xmax ** 2.0 + ymax ** 2.0) ** .5


def lptshape(array, a, b, M):
    rhomax = 1 + int(floor(M * log(max_rho(array) + a) - b))
    phimax = array.shape[1]

    return rhomax, phimax


def fovea(array, t):
    m, n = array.shape
    for rho in range(0, m):
        pixels = [array[rho, phi] for phi in range(0, n) if t[rho, phi] > 0.0]
        w = len(pixels)
        if w >= n:
            break
        ratio = int((w << 16) / n)
        for phi in range(0, n):
            k = (phi * ratio) >> 16
            array[rho, phi] = pixels[k]
    return array


def transform(array, origin=None, a=None, b=None, M=None):
    '''
    a  - The radial distance offset. If ommited, a sensible guess
         is calculated.
    b  - Optional. The rho translation. If ommited, a sensible guess is
         calculated.
    M  - Optional. The rho scaling relative to the maximum radial distance.
         If ommited, a sensible guess is calculated.
    '''
    
    origin = origin or array.shape[0] / 2, array.shape[1] / 2
    x0 = origin[1]
    y0 = origin[0]
    a = a or (max_rho(array) - 3.0) * .5
    b = b or (1 + a) * log(1 + a) - 1.5
    M = M or 1 + a

    polar = zeros(lptshape(array, a, b, M))

    rnor = max_rho(array) / max_rho(array, x0, y0)
    t = zeros(polar.shape, float)
    (rows, cols) = array.shape
    (m, n) = polar.shape

    # Maps the pixels from the cartesian space into the log-polar space.
    polar[0, 0] = array[y0, x0]
    for y in range(0, rows):
        for x in range(0, cols):
            xt = float(x - x0)
            yt = float(y - y0)
            r = rnor * (xt ** 2.0 + yt ** 2.0) ** .5
            rho = int(floor(M * log(r + a) - b))
            phi = int(floor(n * arctan(xt, yt) / (2 * pi)))
            t[rho, phi] += 1.0
            polar[rho, phi] += int((array[y, x] - polar[rho, phi]) / t[rho,
                phi])

    # Recalculates the fovea region.
    polar = fovea(polar, t)

    return polar


def coord_car2logpol(coords, shape, origin, rows, cols, base):
    row, col = coords
    row0, col0 = origin
    theta = col * tau / cols
    rho = base ** row
    row = row0 + rho * cos(theta)
    col = col0 + rho * sin(theta)
    return row, col


def array_car2logpol(array, order=3):
    shape = array.shape
    rows, cols = shape
    out_shape = rows * 2, cols * 2
    extra_data = {
        'shape': shape,
        'origin': shape,
        "base": exp(log(rows) / rows),
        "rows": rows,
        "cols": cols,
    }

    return ndimage.geometric_transform(array, coord_car2logpol, out_shape,
        order=order, extra_keywords=extra_data)




def main():

    image = Image.open(sys.argv[1])
    image = image.convert("L")
    image.show()
    array = numpy.array(image)

    polar1 = transform(array)
    Image.fromarray(polar1).show()

    polar2 = array_car2logpol(array)
    Image.fromarray(polar2).show()

if __name__ == "__main__":
    exit(main())
