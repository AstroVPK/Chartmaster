#pragma once
#include <cmath>
#include <tuple>
#include <type_traits>
#include <iostream>

#include "utils.hpp"


namespace coordinates {

    template <typename T>
    class RA {
        private:
            T val; /* Value in decimal degrees */
        public:
            using value_type = T;

            RA() {val = static_cast<T>(0.0);};

            template <typename I>
            RA(I hour, I min, T sec);

            template <typename I>
            RA(I hour, T min) : RA(hour, 0, static_cast<T>(60.0)*min) {};

            RA(T hour) : RA(0, 0, static_cast<T>(3600.0)*hour) {};

            T value() const {return val;};

            template <typename I>
            I hour();

            template <typename I>
            I min();

            T sec();

            template <typename I>
            I deg();

            template <typename I>
            I arcmin();

            T arcsec();

            template <typename I>
            std::tuple<I, I, T> hour_min_sec() const;

            template <typename I>
            std::tuple<I, I, T> deg_arcmin_arcsec() const;

            RA<T> & operator+=(RA<T> const & ra);

            RA<T> & operator-=(RA<T> const & ra);

    };

    template <typename T>
    template <typename I>
    RA<T>::RA(I hour, I min, T sec) {
        static_assert(std::is_integral<I>::value, "Integral type required!");
        static_assert(std::is_floating_point<T>::value, "Floating point type required!");
        val = std::fmod(static_cast<T>(15.0)*std::copysign(std::fabs(hour) + static_cast<T>(min)/static_cast<T>(60.0) + sec/static_cast<T>(3600.0), hour), static_cast<T>(360.0));
        if (val < static_cast<T>(0.0)) {
            val += static_cast<T>(360.0);
        }
    }

    template <typename T>
    template <typename I>
    std::tuple<I, I, T> RA<T>::hour_min_sec() const {
        static_assert(std::is_integral<I>::value, "Integral type required!");
        static_assert(std::is_floating_point<T>::value, "Floating point type required!");
        T decimal_hour = val/static_cast<T>(15.0);
        T hour = std::floor(decimal_hour);
        T min = std::floor(static_cast<T>(60.0)*(decimal_hour - hour));
        T sec = static_cast<T>(3600.0)*(decimal_hour - hour - (min/static_cast<T>(60.0)));
        return {static_cast<I>(hour), static_cast<I>(min), sec};
    }

    template <typename T>
    template <typename I>
    I RA<T>::hour() {
        static_assert(std::is_integral<I>::value, "Integral type required!");
        static_assert(std::is_floating_point<T>::value, "Floating point type required!");
        T decimal_hour = val/static_cast<T>(15.0);
        T hour = std::floor(decimal_hour);
        return static_cast<I>(hour);
    }

    template <typename T>
    template <typename I>
    I RA<T>::min() {
        static_assert(std::is_integral<I>::value, "Integral type required!");
        static_assert(std::is_floating_point<T>::value, "Floating point type required!");
        T decimal_hour = val/static_cast<T>(15.0);
        T hour = std::floor(decimal_hour);
        T min = std::floor(static_cast<T>(60.0)*(decimal_hour - hour));
        return static_cast<I>(min);
    }

    template <typename T>
    T RA<T>::sec() {
        static_assert(std::is_floating_point<T>::value, "Floating point type required!");
        T decimal_hour = val/static_cast<T>(15.0);
        T hour = std::floor(decimal_hour);
        T min = std::floor(static_cast<T>(60.0)*(decimal_hour - hour));
        T sec = static_cast<T>(3600.0)*(decimal_hour - hour - (min/static_cast<T>(60.0)));
        return sec;
    }

    template <typename T>
    template <typename I>
    I RA<T>::deg() {
        T deg = std::floor(val);
        return static_cast<I>(deg);
    }

    template <typename T>
    template <typename I>
    I RA<T>::arcmin() {
        T deg = std::floor(val);
        T arcmin = std::floor(static_cast<T>(60.0)*(val - deg));
        return static_cast<I>(arcmin);
    }

    template <typename T>
    T RA<T>::arcsec() {
        T deg = std::floor(val);
        T arcmin = std::floor(static_cast<T>(60.0)*(val - deg));
        T arcsec = static_cast<T>(3600.0)*(val - deg - (arcmin/static_cast<T>(60.0)));
        return arcsec;
    }

    template <typename T>
    RA<T> & coordinates::RA<T>::operator+=(RA<T> const & ra) {
        this->val = std::fmod((this->val + ra.value()), static_cast<T>(360.0));
        return *this;
    }

    template <typename T>
    RA<T> & coordinates::RA<T>::operator-=(RA<T> const & ra) {
        this->val = mod((this->val - ra.value()), static_cast<T>(360.0));
        return *this;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const RA<T>& ra) {
        std::tuple<int, int, T> repr = ra.hour_min_sec();
        os << std::get<0>(repr) << "h" << std::get<1>(repr) << "m" << std::get<2>(repr) << "s";
        return os;
    }

    template <typename T1, typename T2>
    const RA<typename std::common_type<T1, T2>::type> operator+(const RA<T1>& ra1, const RA<T2>& ra2) {
        typename std::common_type<T1, T2>::type res_degree = static_cast<typename std::common_type<T1, T2>::type>(ra1.value()) + static_cast<typename std::common_type<T1, T2>::type>(ra2.value());
        typename std::common_type<T1, T2>::type res_hour = res_degree/static_cast<typename std::common_type<T1, T2>::type>(15.0);
        RA<typename std::common_type<T1, T2>::type> res{res_hour};
        return res;
    }

    template <typename T1, typename T2>
    const RA<typename std::common_type<T1, T2>::type> operator-(const RA<T1>& ra1, const RA<T2>& ra2) {
        typename std::common_type<T1, T2>::type res_degree = static_cast<typename std::common_type<T1, T2>::type>(ra1.value()) - static_cast<typename std::common_type<T1, T2>::type>(ra2.value());
        typename std::common_type<T1, T2>::type res_hour = res_degree/static_cast<typename std::common_type<T1, T2>::type>(15.0);
        RA<typename std::common_type<T1, T2>::type> res{res_hour};
        return res;
    }

}