#pragma once

#include "Organ.h"

namespace cpptest::human::organs {

class Heart : private Organ {
public:
  void execute();

private:
};

} // namespace cpptest::human::organs
