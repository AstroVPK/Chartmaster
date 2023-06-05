#pragma once
#include <cmath>

#include "ra.hpp"
#include "dec.hpp"
#include "flatpoint.hpp"
#include "projection.hpp"


template <typename T, typename Projection>
class CelestialPoint : Projection {
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

template <typename T, typename Projection>
CelestialPoint<T, Projection>::CelestialPoint() {
    ra_val = coordinates::RA<T>{static_cast<T>(0.0)};
    dec_val = coordinates::Dec<T>{static_cast<T>(0.0)};
}

template <typename T, typename Projection>
template <typename I> 
CelestialPoint<T, Projection>::CelestialPoint(I hour, I min, T sec, I deg, I arcmin, T arcsec) {
    ra_val = coordinates::RA<T>{hour, min, sec};
    dec_val = coordinates::Dec<T>{deg, arcmin, arcsec};
}