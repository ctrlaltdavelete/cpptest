#include "Organ.h"
#include "utils/NumberUtils.h"
#include <iostream>

namespace cpptest::human::organs {

float Organ::getHealth() { return health; }

bool Organ::isFailed() { return failed; }

bool Organ::heal(float amount) {
  if (cpptest::utils::isPositive(amount)) {
    health += amount;
    return true;
  } else {
    std::cout << "Non-positve number passed in. Ignoring" << std::endl;
  }
  return false;
}

} // namespace cpptest::human::organs