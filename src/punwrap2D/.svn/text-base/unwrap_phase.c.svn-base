#include <stdio.h>

#include "Python.h"
#include "numpy/noprefix.h"
#include "Munther_2D_unwrap.h"

static char doc_Unwrap2D[] = "Performs 2D phase unwrapping on a ndarray object; accepts a binary mask";

PyObject *punwrap2D_Unwrap2D(PyObject *self, PyObject *args) {
  PyObject *op1, *op2;
  PyArrayObject *phsArray, *mskArray, *retArray;
  float *wr_phs, *uw_phs;
  BYTE *bmask;
  int typenum_phs, typenum_msk, ndim;
  npy_intp *dims;
  PyArray_Descr *dtype_phs;

  if(!PyArg_ParseTuple(args, "OO", &op1, &op2)) {
    PyErr_SetString(PyExc_Exception,"Unwrap2D: Couldn't parse the arguments");
    return NULL;
  }
  if(op1==NULL || op2==NULL) {
    PyErr_SetString(PyExc_Exception,"Unwrap2D: Arguments not read correctly");
    return NULL;
  }
  
  typenum_phs = PyArray_TYPE(op1);
  typenum_msk = PyArray_TYPE(op2);
  ndim = PyArray_NDIM(op1);
  dims = PyArray_DIMS(op2);
  /* This stuff is technically enforced in punwrap/__init__.py */
  if(typenum_phs != PyArray_FLOAT) {
    PyErr_SetString(PyExc_Exception, "Unwrap2D: I can only handle single-precision floating point numbers");
    return NULL;
  }
  if(typenum_msk != PyArray_UBYTE) {
    PyErr_SetString(PyExc_Exception, "Unwrap2D: The mask should be type uint8");
    return NULL;
  }
  if(ndim != 2) {
    PyErr_SetString(PyExc_Exception, "Unwrap2D: I can only unwrap 2D arrays");
    return NULL;
  }

  dtype_phs = PyArray_DescrFromType(typenum_phs);
  /* increasing references here */
  phsArray = (PyArrayObject *)PyArray_FROM_OTF(op1, typenum_phs, NPY_IN_ARRAY);
  mskArray = (PyArrayObject *)PyArray_FROM_OTF(op2, typenum_msk, NPY_IN_ARRAY);
  /* create a new, empty ndarray with floats */
  retArray = (PyArrayObject *)PyArray_SimpleNewFromDescr(ndim, dims, dtype_phs);
  wr_phs = (float *)PyArray_DATA(phsArray);
  uw_phs = (float *)PyArray_DATA(retArray);
  bmask = (BYTE *)PyArray_DATA(mskArray);

  phase_unwrap_2D(wr_phs, uw_phs, bmask, (int) dims[0], (int) dims[1]);

  Py_DECREF(phsArray);
  Py_DECREF(mskArray);
  return PyArray_Return(retArray);
    
}

static struct PyMethodDef punwrap2D_module_methods[] = {
  {"Unwrap2D",	(PyCFunction)punwrap2D_Unwrap2D, 1, doc_Unwrap2D},
  {NULL, NULL, 0}
};

DL_EXPORT(void) init_punwrap2D(void) {
  PyObject *m;
  m = Py_InitModule3("_punwrap2D", punwrap2D_module_methods, "c library for phase unwrapping in python");
  import_array();
}
