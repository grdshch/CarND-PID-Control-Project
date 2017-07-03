#include "twiddle.h"

void Twiddle::Update(double cte) {
  if (first_run_) {
    first_run_ = false;
    best_cte_ = cte;

    parameter_ = 0;
    increase_ = true;
    UpdateParameter();
    return;
  }

  if (cte < best_cte_) {
    dp_[parameter_] *= 1.1;
    best_cte_ = cte;
    ++parameter_ %= 3;
  }
  else if (increase_) {
    increase_ = false;
    UpdateParameter();
  }
  else {
    increase_ = true;
    UpdateParameter();
    dp_[parameter_] *= 0.9;
    ++parameter_ %= 3;
    UpdateParameter();
  }
}

void Twiddle::UpdateParameter() {
  int c = increase_ ? 1: -2;
  if (parameter_ == 0) pid_.Kp_ += dp_[0] * c;
  else if (parameter_ == 1) pid_.Ki_ += dp_[1] * c;
  else if (parameter_ == 2) pid_.Kd_ += dp_[2] * c;
}