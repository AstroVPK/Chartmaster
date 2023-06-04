#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "ra.hpp"
#include "dec.hpp"


namespace py = pybind11;

/* Close, but does not work!! */

// template <typename T, typename I>
// void declare_RA(py::module &m, std::string &typestr) {
// 	using Class = coordinates::RA<T>;
// 	std::string pyclass_name = typestr + std::string("RA");
// 	py::class_<Class>(m, pyclass_name.c_str())
// 	.def(py::init<>())
// 	.def(py::init<I, I, T>())
// 	.def(py::init<I, T>())
// 	.def(py::init<T>())
// 	.def("value", &Class::value)
// 	.def("hour", &Class::hour<I>) 
/* Error! src/ra.cpp:19:36: error: expected primary-expression before ‘>’ token
   19 |         .def("hour", &Class::hour<I>)
      |                                    ^
src/ra.cpp:19:37: error: expected primary-expression before ‘)’ token
   19 |         .def("hour", &Class::hour<I>)
      |                                     ^
scons: *** [lib/ra.cpython-38-x86_64-linux-gnu.so] Error 1
*/
// 	.def("min", &Class::min<I>)
// 	.def("sec", &Class::sec)
// 	.def("deg", &Class::deg<I>)
// 	.def("arcmin", &Class::arcmin<I>)
// 	.def("arcsec", &Class::arcsec)
// 	.def("hour_min_sec", &Class::hour_min_sec<I>)
// 	// .def("deg_arcmin_arcsec", &Class::deg_arcmin_arcsec<I>)
// 	.def(py::self += py::self)
// 	.def(py::self -= py::self);
// }

// std::string floatstr{"f"}, doublestr{""}, longdoublestr{"ld"};

// PYBIND11_MODULE(ra, m) {
// declare_RA<float, int>(m, floatstr);
// declare_RA<double, int>(m, doublestr);
// declare_RA<long double, int>(m, longdoublestr);
// }


#define DEFINE_RADEC(T, I, S) \
	py::class_<coordinates::RA<T>>(m, #S "RA") \
	.def(py::init<>()) \
	.def(py::init<I, I, T>()) \
	.def(py::init<I, T>()) \
	.def(py::init<T>()) \
	.def("value", &coordinates::RA<T>::value) \
	.def("hour", &coordinates::RA<T>::hour<I>) \
	.def("min", &coordinates::RA<T>::min<I>) \
	.def("sec", &coordinates::RA<T>::sec) \
	.def("deg", &coordinates::RA<T>::deg<I>) \
	.def("arcmin", &coordinates::RA<T>::arcmin<I>) \
	.def("arcsec", &coordinates::RA<T>::arcsec) \
	.def("hour_min_sec", &coordinates::RA<T>::hour_min_sec<I>) \
	.def(py::self += py::self) \
	.def(py::self -= py::self) \
	.def("__add__", [](const coordinates::RA<T> &ra2, const coordinates::RA<T> &ra1) {return ra2 + ra1;}) \
	.def("__radd__", [](const coordinates::RA<T> &ra2, const coordinates::RA<T> &ra1) {return ra1 + ra2;}) \
	.def("__sub__", [](const coordinates::RA<T> &ra2, const coordinates::RA<T> &ra1) {return ra2 - ra1;}) \
	.def("__rsub__", [](const coordinates::RA<T> &ra2, const coordinates::RA<T> &ra1) {return ra1 - ra2;}); \
	py::class_<coordinates::Dec<T>>(m, #S "Dec") \
	.def(py::init<>()) \
	.def(py::init<I, I, T>()) \
	.def(py::init<I, T>()) \
	.def(py::init<T>()) \
	.def("value", &coordinates::Dec<T>::value) \
	.def("deg", &coordinates::Dec<T>::deg<I>) \
	.def("arcmin", &coordinates::Dec<T>::arcmin<I>) \
	.def("arcsec", &coordinates::Dec<T>::arcsec) \
	.def("deg_arcmin_arcsec", &coordinates::Dec<T>::deg_arcmin_arcsec<I>) \
	.def(py::self += py::self) \
	.def(py::self -= py::self) \
	.def("__add__", [](const coordinates::Dec<T> &dec2, const coordinates::Dec<T> &dec1) {return dec2 + dec1;}) \
	.def("__radd__", [](const coordinates::Dec<T> &dec2, const coordinates::Dec<T> &dec1) {return dec1 + dec2;}) \
	.def("__sub__", [](const coordinates::Dec<T> &dec2, const coordinates::Dec<T> &dec1) {return dec2 - dec1;}) \
	.def("__rsub__", [](const coordinates::Dec<T> &dec2, const coordinates::Dec<T> &dec1) {return dec1 - dec2;});


PYBIND11_MODULE(point, m) {
	DEFINE_RADEC(float, int, f)
	DEFINE_RADEC(double, int, d)
	DEFINE_RADEC(long double, int, )
}