#pragma once

namespace cpptest::utils {

template <typename T> bool isZero(T number) { return (number == 0.0); }
template <typename T> bool isNegative(T number) { return (number < 0.0); }
template <typename T> bool isPositive(T number) { return (number > 0.0); }
} // namespace cpptest::utils