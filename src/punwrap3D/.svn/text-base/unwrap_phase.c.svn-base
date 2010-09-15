#include <stdio.h>

#include "Python.h"
#include "numpy/noprefix.h"
#include "UnwrapMain.h"

static char doc_Unwrap3D[] = "Performs 3D phase unwrapping on an ndarray";

PyObject *punwrap3D_Unwrap3D(PyObject *self, PyObject *args) {
  PyObject *op;
  PyArrayObject *phsArray, *retArray;
  float *wr_phs, *uw_phs;
  npy_intp *dims;
  int typenum_phs, ndim;
  PyArray_Descr *dtype_phs;
    
  if(!PyArg_ParseTuple(args, "O", &op)) {
    PyErr_SetString(PyExc_Exception, "Unwrap3D: Couldn't parse any args");
    return NULL;
  }
  if(op==NULL) {
    PyErr_SetString(PyExc_Exception, "Unwrap3D: Arguments not read correctly");
    return NULL;
  }

  typenum_phs = PyArray_TYPE(op);
  ndim = PyArray_NDIM(op);
  dims = PyArray_DIMS(op);
  if(typenum_phs != PyArray_FLOAT) {
    PyErr_SetString(PyExc_Exception, "Unwrap3D: I can only handle single-precision floating point numbers");
    return NULL;
  }
  if(ndim < 3) {
    PyErr_SetString(PyExc_Exception, "Unwrap3D: I can only unwrap 3D arrays");
    return NULL;
  }

  dtype_phs = PyArray_DescrFromType(typenum_phs);
  /* increasing reference here */
  phsArray = (PyArrayObject *)PyArray_FROM_OTF(op, typenum_phs, NPY_IN_ARRAY);
  /* create a new, empty ndarray with floats */
  retArray = (PyArrayObject *)PyArray_SimpleNewFromDescr(ndim, dims, dtype_phs);
  
  wr_phs = (float *)PyArray_DATA(phsArray);
  uw_phs = (float *)PyArray_DATA(retArray);

  unwrap_phs(wr_phs, uw_phs, (int) dims[0], (int) dims[1], (int) dims[2]);
  
  Py_DECREF(phsArray);
  return PyArray_Return(retArray);
    
}

static struct PyMethodDef punwrap3D_module_methods[] = {
  {"Unwrap3D",	(PyCFunction)punwrap3D_Unwrap3D, 1, doc_Unwrap3D},
  {NULL, NULL, 0}
};

DL_EXPORT(void) init_punwrap3D(void) {
  PyObject *m;
  m = Py_InitModule3("_punwrap3D", punwrap3D_module_methods, "c library for phase unwrapping in python");
  import_array();
}
