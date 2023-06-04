#pragma once
#include <cmath>
#include <tuple>
#include <type_traits>
#include <iostream>

#include "utils.hpp"


namespace coordinates {

    template <typename T>
    class Dec {
        private:
            T val; /* Value in decimal degrees */
        public:
            using value_type = T;

            Dec() {val = static_cast<T>(0.0);};

            template <typename I>
            Dec(I deg, I arcmin, T arcsec);

            template <typename I>
            Dec(I deg, T arcmin) : Dec(deg, 0, static_cast<T>(60.0)*arcmin) {};

            Dec(T deg) : Dec(0, 0, static_cast<T>(3600.0)*deg) {};

            T value() const {return val;};

            template <typename I>
            I deg();

            template <typename I>
            I arcmin();

            T arcsec();

            template <typename I>
            std::tuple<I, I, T> deg_arcmin_arcsec() const;

            Dec<T> & operator+=(Dec<T> const & dec);

            Dec<T> & operator-=(Dec<T> const & dec);

    };

    template <typename T>
    template <typename I>
    Dec<T>::Dec(I deg, I arcmin, T arcsec) {
        static_assert(std::is_integral<I>::value, "Integral type required!");
        static_assert(std::is_floating_point<T>::value, "Floating point type required!");
        T value = std::copysign(static_cast<T>(std::fabs(deg) + arcmin/static_cast<T>(60.0)) + arcsec/static_cast<T>(3600.0), deg);
        if (value < static_cast<T>(-90.0) || value > static_cast<T>(90.0)) {
            throw std::out_of_range("Declination value out-of-bounds");
        }
        val = value;
    }

    template <typename T>
    template <typename I>
    std::tuple<I, I, T> Dec<T>::deg_arcmin_arcsec() const {
        static_assert(std::is_integral<I>::value, "Integral type required!");
        T deg = std::floor(val);
        T arcmin = std::floor(static_cast<T>(60.0)*(val - deg));
        T arcsec = static_cast<T>(3600.0)*(val - deg - (arcmin/static_cast<T>(60.0)));
        return {static_cast<I>(deg), static_cast<I>(arcmin), arcsec};
    }

    template <typename T>
    template <typename I>
    I coordinates::Dec<T>::deg() {
        T deg = std::floor(val);
        return static_cast<I>(deg);
    }

    template <typename T>
    template <typename I>
    I coordinates::Dec<T>::arcmin() {
        T deg = std::floor(val);
        T arcmin = std::floor(static_cast<T>(60.0)*(val - deg));
        return static_cast<I>(arcmin);
    }

    template <typename T>
    T coordinates::Dec<T>::arcsec() {
        T deg = std::floor(val);
        T arcmin = std::floor(static_cast<T>(60.0)*(val - deg));
        T arcsec = static_cast<T>(3600.0)*(val - deg - (arcmin/static_cast<T>(60.0)));
        return arcsec;
    }

    template <typename T>
    Dec<T> & coordinates::Dec<T>::operator+=(Dec<T> const & dec) {
        T value = this->val + dec.value();
        if (value < static_cast<T>(-90.0) || value > static_cast<T>(90.0)) {
            throw std::out_of_range("Declination value out-of-bounds");
        }
        this->val = value;
        return *this;
    }

    template <typename T>
    Dec<T> & coordinates::Dec<T>::operator-=(Dec<T> const & dec) {
        T value = this->val - dec.value();
        if (value < static_cast<T>(-90.0) || value > static_cast<T>(90.0)) {
            throw std::out_of_range("Declination value out-of-bounds");
        }
        this->val = value;
        return *this;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Dec<T>& dec) {
        std::tuple<int, int, T> repr = dec.deg_arcmin_arcsec();
        os << std::get<0>(repr) << "d" << std::get<1>(repr) << "arcmin" << std::get<2>(repr) << "arcsec";
        return os;
    }

    template <typename T1, typename T2>
    const Dec<typename std::common_type<T1, T2>::type> operator+(const Dec<T1>& dec1, const Dec<T2>& dec2) {
        typename std::common_type<T1, T2>::type res_degree = static_cast<typename std::common_type<T1, T2>::type>(dec1.value()) + static_cast<typename std::common_type<T1, T2>::type>(dec2.value());
        Dec<typename std::common_type<T1, T2>::type> res{res_degree};
        return res;
    }

    template <typename T1, typename T2>
    const Dec<typename std::common_type<T1, T2>::type> operator-(const Dec<T1>& dec1, const Dec<T2>& dec2) {
        typename std::common_type<T1, T2>::type res_degree = static_cast<typename std::common_type<T1, T2>::type>(dec1.value()) - static_cast<typename std::common_type<T1, T2>::type>(dec2.value());
        Dec<typename std::common_type<T1, T2>::type> res{res_degree};
        return res;
    }

}