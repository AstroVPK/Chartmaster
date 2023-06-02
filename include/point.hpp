#pragma once
#include <cmath>
#include <numbers>

#include "ra.hpp"
#include "dec.hpp"


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
    theta = static_cast<T>(0.0);
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


template <typename T>
class CelestialPoint {
    private:
        coordinates::RA<T> ra;
        coordinates::Dec<T> dec;
    public:
        CelestialPoint();

        CelestialPoint(T hour, T deg);

        //CelestialPoint(RA<T> ra, Dec<T> dec);

        T const RA() const {return ra.value();};

        T const Dec() const {return dec.value();};
};

template <typename T>
CelestialPoint<T>::CelestialPoint() {
    ra = coordinates::RA<T>{static_cast<T>(0.0)};
    dec = coordinates::Dec<T>{static_cast<T>(0.0)};
}

template <typename T>
CelestialPoint<T>::CelestialPoint(T hour, T deg) {
    ra = coordinates::RA<T>{hour};
    dec = coordinates::Dec<T>{deg};
}