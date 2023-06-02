#pragma once
#include <cmath>
#include <numbers>

#include "ra.hpp"
#include "dec.hpp"
#include "point.hpp"


template <typename T>
class Stereographic {
    public:
        Stereographic() = default;

        PolarPoint<T> project(CelestialPoint<T> const pt) const;
};

template <typename T>
PolarPoint<T> Stereographic<T>::project(CelestialPoint<T> const pt) const {
    T theta = pt.RA();
    T dec_radians = pt.Dec()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T r = static_cast<T>(2.0)*std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> - static_cast<T>(0.5)*dec_radians);
    return PolarPoint(r, theta);
}

template <typename T, T fakor>
class LambertConformal {
    private:
        T Fakor;
        T lambda0, phi0, phi1, phi2, n, F, rho0;
    public:
        LambertConformal(T ra0, T dec0, T dec1, T dec2);

        LambertConformal() : LambertConformal(static_cast<T>(0.0), static_cast<T>(50.0), static_cast<T>(30.0), static_cast<T>(70.0)) {};

        LambertConformal(T ra0, T dec0) : LambertConformal(ra0, dec0, static_cast<T>(30.0), static_cast<T>(50)) {};

        CartesianPoint<T> project(CelestialPoint<T> const pt);
};

template <typename T, T fakor>
LambertConformal<T, fakor>::LambertConformal(T ra0, T dec0, T dec1, T dec2) {
    Fakor = fakor;
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

template <typename T, T fakor>
CartesianPoint<T> LambertConformal<T, fakor>::project(CelestialPoint<T> const pt) {
    T ra_radians = pt.RA()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T dec_radians = pt.Dec()*(std::numbers::pi_v<T>/static_cast<T>(180.0));
    T rho = F/std::pow(std::tan(static_cast<T>(0.25)*std::numbers::pi_v<T> + static_cast<T>(0.5)*dec_radians), n);
    T x = rho*std::sin(n*(ra_radians - lambda0));
    T y = rho0 - rho*(std::cos(n*(ra_radians - lambda0)));
    return CartesianPoint(x, y);
}

// template <typename T>
// class Mercator {
// };

template <typename T, typename P>
class Projector : public P {
    private:
        int x;
};