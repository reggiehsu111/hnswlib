#pragma once
#include "hnswlib.h"
#include <functional>
#include <iostream>
#include <pybind11/pybind11.h>


namespace py = pybind11;
namespace hnswlib {
py::function g_py_dist_func;

static float
call_py_func(const void *a, const void *b, const void *c) {
  return g_py_dist_func(a, b, c).cast<float>();
}

class PySpace : public SpaceInterface<float> {
    DISTFUNC<float> fstdistfunc_;
    std::function<float(const void *, const void *, const void *)> func_;
    size_t data_size_;
    size_t dim_;

 public:
    PySpace(const py::function &py_dist_func, size_t dim) {
        if (py_dist_func) {
            int a=1, b=2, c=3;
            g_py_dist_func = py_dist_func;
            fstdistfunc_ = call_py_func;
            float res = fstdistfunc_(reinterpret_cast<const void *>(&a), reinterpret_cast<const void *>(&b), reinterpret_cast<const void *>(&c));
            printf("%p, %p, %p\n", &a, &b, &c);
            printf("res: %.6f\n", res);
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
