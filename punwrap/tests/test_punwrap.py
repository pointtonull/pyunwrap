from numpy.testing import *
from recon.punwrap import unwrap2D, unwrap3D
from recon.util import normalize_angle
from numpy import outer, arange, ones, abs, empty, power, indices

class test_unwrap(TestCase):
    def test_simple2d(self, level=1):
        grid = outer(ones(64), arange(-32,32)) + \
               1.j * outer(arange(-32,32), ones(64))
        pgrid = abs(grid)
        wr_grid = normalize_angle(pgrid)
        uw_grid = unwrap2D(wr_grid)
        uw_grid += (pgrid[32,32] - uw_grid[32,32])
        
        assert_array_almost_equal(pgrid, uw_grid, decimal=5)
    
    def test_simple3d(self):
        grid = indices((64,64,64))
        grid[0] -= 32
        grid[1] -= 32
        grid[2] -= 32
        # get distance of each point in the grid from 0
        grid = power(power(grid, 2.0).sum(axis=0), 0.5)
        wr_grid = normalize_angle(grid)
        uw_grid = unwrap3D(wr_grid)
        uw_grid += (grid[32,32,32] - uw_grid[32,32,32])
        assert_array_almost_equal(grid, uw_grid, decimal=5)

if __name__=="__main__":
    NumpyTest().run()
