#pragma once
#include <cmath>
#include <numbers>


template <typename T>
class PolarPoint {
    private:
        T R, Theta;
    public:
        PolarPoint();

        PolarPoint(T r, T theta);
        
        T const r() {return R;};
        
        T const theta() {return Theta;};
};

template <typename T>
PolarPoint<T>::PolarPoint() {
    R = static_cast<T>(0.0);
    Theta = static_cast<T>(0.0);
}

template <typename T>
PolarPoint<T>::PolarPoint(T r, T theta) {
    R = r;
    Theta = theta;
}

template <typename T>
class CartesianPoint {
    private:
        T X, Y;
    public:
        CartesianPoint();

        CartesianPoint(T x, T y);
        
        T const x() {return X;};
        
        T const y() {return Y;};
};

template <typename T>
CartesianPoint<T>::CartesianPoint() {
    X = static_cast<T>(0.0);
    Y = static_cast<T>(0.0);
}

template <typename T>
CartesianPoint<T>::CartesianPoint(T x, T y) {
    X = x;
    Y = y;
}
