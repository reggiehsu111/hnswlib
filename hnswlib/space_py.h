#pragma once
#include "hnswlib.h"
#include <functional>
#include <iostream>
#include <pybind11/pybind11.h>
#include <vector>


namespace py = pybind11;
namespace hnswlib {
static py::function g_py_dist_func;

static float
call_py_func(const void *pVect1v, const void *pVect2v, const void *qty_ptr) {
    float *pVect1 = (float *) pVect1v;
    float *pVect2 = (float *) pVect2v;
    int qty = *((int *) qty_ptr);
    std::vector<float> v1;
    std::vector<float> v2;
    printf("qty: %d\n", qty);

    float res = 0;
    for (int i = 0; i < qty; i++) {
        v1.push_back(*pVect1);
        v2.push_back(*pVect2);
        // printf("%d: %.6f, %.6f\n", i, *pVect1, *pVect2);
        pVect1++;
        pVect2++;
    }
    printf("Here\n");
    if (g_py_dist_func) {
      printf("Has py function\n");
    }
    float ret = g_py_dist_func(v1, v2).cast<float>();
    printf("res: %.6f\n", res);
    return ret;
}

class PySpace : public SpaceInterface<float> {
    DISTFUNC<float> fstdistfunc_;
    std::function<float(const void *, const void *, const void *)> func_;
    size_t data_size_;
    size_t dim_;

 public:
    PySpace(const py::function &py_dist_func, size_t dim) {
        if (py_dist_func) {
            float a=1, b=2;
            int c=1;
            g_py_dist_func = py_dist_func;
            fstdistfunc_ = call_py_func;
            float res = fstdistfunc_(reinterpret_cast<const void *>(&a), reinterpret_cast<const void *>(&b), reinterpret_cast<const void *>(&c));
        }
        // func_ = py_dist_func;
        printf("Here\n");
        dim_ = dim;
        data_size_ = dim * sizeof(float);
    }

    size_t get_data_size() {
        return data_size_;
    }

    DISTFUNC<float> get_dist_func() {
        return fstdistfunc_;
    }

    void *get_dist_func_param() {
        return &dim_;
    }

    ~PySpace() {}
};
}
