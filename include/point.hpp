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


template <typename T>
class CelestialPoint {
    private:
        coordinates::RA<T> ra_val;
        coordinates::Dec<T> dec_val;
    public:
        CelestialPoint();

        template <typename I>
        CelestialPoint(I hour, I min, T sec, I deg, I arcmin, T arcsec);

        template <typename I>
        CelestialPoint(I hour, T min, I deg, T arcmin) : CelestialPoint(hour, 0, static_cast<T>(60.0)*min, deg, 0, static_cast<T>(60.0)*arcmin) {};

        template <typename I>
        CelestialPoint(T hour, I deg, T arcmin) : CelestialPoint(0, 0, static_cast<T>(3600.0)*hour, deg, 0, static_cast<T>(60.0)*arcmin) {};

        template <typename I>
        CelestialPoint(I hour, T min, T deg) : CelestialPoint(hour, 0, static_cast<T>(60.0)*min, 0, 0, static_cast<T>(3600.0)*deg) {};

        CelestialPoint(coordinates::RA<T> ra, coordinates::Dec<T> dec) {ra_val = ra; dec_val = dec;};

        T const RA() const {return ra_val.value();};

        T const Dec() const {return dec_val.value();};
};

template <typename T>
CelestialPoint<T>::CelestialPoint() {
    ra_val = coordinates::RA<T>{static_cast<T>(0.0)};
    dec_val = coordinates::Dec<T>{static_cast<T>(0.0)};
}

template <typename T>
template <typename I> 
CelestialPoint<T>::CelestialPoint(I hour, I min, T sec, I deg, I arcmin, T arcsec) {
    ra_val = coordinates::RA<T>{hour, min, sec};
    dec_val = coordinates::Dec<T>{deg, arcmin, arcsec};
}