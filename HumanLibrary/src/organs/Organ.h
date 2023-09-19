#pragma once

#include <string>

namespace cpptest::human::organs {

class Organ {
public:
  Organ() = default;
  ;
  virtual ~Organ() = default;
  ;

  virtual void execute() = 0;
  /**
   * Returns amount of health as float
   */

  float getHealth();
  /**
   * Returns whether organ has failed (bool failed)
   */
  bool isFailed();

protected:
  /**
   * Adds x amount to health. Must be positive. Returns true if heal was
   * successful.
   * @param[in] amount The amount of health to heal organ by
   */
  bool heal(float amount);

  /**
   * Removes x amount to health.
   * @param[in] amount The amount of health to damage organ by
   */
  bool damage(float amount);

private:
  float health = 100.0;
  // Organs fail at 0 health.
  bool failed = false;
};

} // namespace cpptest::human::organs
