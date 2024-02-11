#pragma once
#include "hnswlib.h"
#include <functional>
#include <iostream>
#include <pybind11/pybind11.h>


namespace hnswlib {

class PySpace : public SpaceInterface<float> {
    DISTFUNC<float> fstdistfunc_;
    std::function<float(const void *, const void *, const void *)> func_;
    size_t data_size_;
    size_t dim_;

 public:
    PySpace(const std::function<float(const void *, const void *, const void *)> &py_dist_func, size_t dim) {
        if (py_dist_func) {
            const void* a = reinterpret_cast<const void *>(1);
            const void* b = reinterpret_cast<const void *>(2);
            const void* c = reinterpret_cast<const void *>(3);
            float res = py_dist_func(a, b, c);
            printf("res: %.6f\n", res);
        }
        func_ = py_dist_func;
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
