#include <pybind11/pybind11.h>


namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

template <typename T>
struct MyClass {
    private:
        T a_val;
    public:
        MyClass() = default;

        MyClass(T val);

        template <typename V>
        void set(V val);

        T val();
};

template <typename T>
MyClass<T>::MyClass(T val) {
    a_val = val;
}

template <typename T>
template <typename V>
void MyClass<T>::set(V val) {
    a_val = static_cast<T>(val);
}

template <typename T>
T MyClass<T>::val() {
    return a_val;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function that adds two numbers");

    py::class_<MyClass<int>>(m, "MyClassT")
    .def(py::init<>())
    .def(py::init<int>())
    .def("set", &MyClass<int>::set<int>)
    .def("val", &MyClass<int>::val);
}