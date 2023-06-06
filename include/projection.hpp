#pragma once
#include <cmath>
#include <numbers>

#include "ra.hpp"
#include "dec.hpp"
#include "point.hpp"


template <typename T, T scale>
class Stereographic {
    private:
        T Scale;
    public:
        Stereographic();

        PolarPoint<T> project(CelestialPoint<T> const pt) const;
};

template <typename T, T scale>
Stereographic<T, scale>::Stereographic() {
    Scale = scale;
}

template <typename T, T scale>
PolarPoint<T> Stereographic<T, scale>::project(CelestialPoint<T> const pt) const {
    T theta = pt.RA();
    T dec_radians = pt.Dec()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T r = static_cast<T>(2.0)*Scale*std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> - static_cast<T>(0.5)*dec_radians);
    return PolarPoint(r, theta);
}

template <typename T, T scale, T ra0 = static_cast<T>(0.0), T dec0 = static_cast<T>(50.0), T dec1 = static_cast<T>(30.0), T dec2 = static_cast<T>(70.0)>
class LambertConformal {
    private:
        T Scale, lambda0, phi0, phi1, phi2, n, F, rho0;
    public:
        LambertConformal();

        CartesianPoint<T> project(CelestialPoint<T> const pt);
};

template <typename T, T scale, T ra0, T dec0, T dec1, T dec2>
LambertConformal<T, scale, ra0, dec0, dec1, dec2>::LambertConformal() {
    Scale = scale;
    lambda0 = ra0*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    phi0 = dec0*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    phi1 = dec1*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    phi2 = dec2*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T n_numer = std::log(std::cos(phi1)/std::cos(phi2));
    T n_denom = std::log(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*phi2)/std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*phi1));
    n = n_numer/n_denom;
    F = (std::cos(phi1)*std::pow(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*phi1), n))/n;
    rho0 = Scale*F/std::pow(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*phi1), n);
}

template <typename T, T scale, T ra0, T dec0, T dec1, T dec2>
CartesianPoint<T> LambertConformal<T, scale, ra0, dec0, dec1, dec2>::project(CelestialPoint<T> const pt) {
    T ra_radians = pt.RA()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T dec_radians = pt.Dec()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T rho = Scale*F/std::pow(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*dec_radians), n);
    T x = rho*std::sin(n*(ra_radians - lambda0));
    T y = rho0 - rho*(std::cos(n*(ra_radians - lambda0)));
    return CartesianPoint(x, y);
}

template <typename T, T scale, T ra0 = static_cast<T>(0.0)>
class Mercator {
    private:
        T Scale, lambda0;
    public:
        Mercator();

        CartesianPoint<T> project(CelestialPoint<T> const pt);
};

template <typename T, T scale, T ra0>
Mercator<T, scale, ra0>::Mercator() {
    Scale = scale;
    lambda0 = ra0*(std::numbers::pi_v<T>/static_cast<T>(180.0));    
}

template <typename T, T scale, T ra0>
CartesianPoint<T> Mercator<T, scale, ra0>::project(CelestialPoint<T> const pt) {
    T ra_radians = pt.RA()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T dec_radians = pt.Dec()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T x = Scale*(ra_radians - lambda0);
    T y = Scale*std::log(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*dec_radians));
    return CartesianPoint(x, y);
}

template <typename T, typename P>
class Projector : public P {
    private:
        int x;
};