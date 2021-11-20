//
// Created by Kirill Danilchuk <kirill.danilchuk01@gmail.com> on 21/07/2021.
//

#include <pybind11/pybind11.h>
#include <vector>
#include <future>
#include <chrono>
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

namespace py = pybind11;

double SumTrigonometry(float angle, size_t count, std::function<double(double)> trigonometry) {
  double result{};
  for (size_t i = 0; i < count; ++i) {
    result += trigonometry(angle);
  }
  return result;
}

std::chrono::milliseconds Sequence(float angle, size_t count) {
  auto begin = std::chrono::steady_clock::now();
  SumTrigonometry(angle, count, [](double a) {return std::sin(a);});
  SumTrigonometry(angle, count, [](double a) {return std::cos(a);});
  SumTrigonometry(angle, count, [](double a) {return std::tan(a);});
  SumTrigonometry(angle, count, [](double a) {return 1 / std::tan(a);});
  auto end = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

std::chrono::milliseconds Parallel(float angle, size_t count) {
  auto begin = std::chrono::steady_clock::now();
  auto f1 = std::async(std::launch::async, SumTrigonometry, angle, count, [](double a) {return std::sin(a);});
  auto f2 = std::async(std::launch::async, SumTrigonometry, angle, count, [](double a) {return std::cos(a);});
  auto f3 = std::async(std::launch::async, SumTrigonometry, angle, count, [](double a) {return std::tan(a);});
  auto f4 = std::async(std::launch::async, SumTrigonometry, angle, count, [](double a) {return 1 / std::tan(a);});
  f1.wait();
  f2.wait();
  f3.wait();
  f4.wait();
  auto end = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
}

PYBIND11_MODULE(MODULE_NAME, module) {
  module.def("sequence", &Sequence);
  module.def("parallel", &Parallel);
}
