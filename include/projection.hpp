#pragma once
#include <cmath>
#include <numbers>

#include "ra.hpp"
#include "dec.hpp"
#include "point.hpp"
#include "flatpoint.hpp"


template <typename T, typename Point>
class Stereographic {
    public:
        Stereographic() = default;

        PolarPoint<T> project() const;
};

template <typename T, typename Point>
PolarPoint<T> Stereographic<T, Point>::project() const {
    Point & pt = static_cast<Point &>(*this);
    T theta = pt.RA();
    T dec_radians = pt.Dec()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T r = static_cast<T>(2.0)*std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> - static_cast<T>(0.5)*dec_radians);
    return PolarPoint(r, theta);
}

/*
template <typename T, T ra0 = static_cast<T>(0.0), T dec0 = static_cast<T>(50.0), T dec1 = static_cast<T>(30.0), T dec2 = static_cast<T>(70.0)>
class LambertConformal {
    private:
        T lambda0, phi0, phi1, phi2, n, F, rho0;
    public:
        LambertConformal();

        CartesianPoint<T> project(CelestialPoint<T, Projection> const pt);
};

template <typename T, T ra0, T dec0, T dec1, T dec2>
LambertConformal<T, ra0, dec0, dec1, dec2>::LambertConformal() {
    lambda0 = ra0*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    phi0 = dec0*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    phi1 = dec1*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    phi2 = dec2*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T n_numer = std::log(std::cos(phi1)/std::cos(phi2));
    T n_denom = std::log(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*phi2)/std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*phi1));
    n = n_numer/n_denom;
    F = (std::cos(phi1)*std::pow(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*phi1), n))/n;
    rho0 = F/std::pow(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*phi1), n);
}

template <typename T, T ra0, T dec0, T dec1, T dec2>
CartesianPoint<T> LambertConformal<T, ra0, dec0, dec1, dec2>::project(CelestialPoint<T, Projection> const pt) {
    T ra_radians = pt.RA()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T dec_radians = pt.Dec()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T rho = F/std::pow(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*dec_radians), n);
    T x = rho*std::sin(n*(ra_radians - lambda0));
    T y = rho0 - rho*(std::cos(n*(ra_radians - lambda0)));
    return CartesianPoint(x, y);
}

template <typename T, T ra0 = static_cast<T>(0.0)>
class Mercator {
    private:
        T lambda0;
    public:
        Mercator();

        CartesianPoint<T> project(CelestialPoint<T, Projection> const pt);
};

template <typename T, T ra0>
Mercator<T, ra0>::Mercator() {
    lambda0 = ra0*(std::numbers::pi_v<T>/static_cast<T>(180.0));    
}

template <typename T, T ra0>
CartesianPoint<T> Mercator<T, ra0>::project(CelestialPoint<T, Projection> const pt) {
    T ra_radians = pt.RA()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T dec_radians = pt.Dec()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T x = ra_radians - lambda0;
    T y = std::log(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*dec_radians));
    return CartesianPoint(x, y);
}
*/