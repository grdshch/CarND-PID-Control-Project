#include "PID.h"

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  Kp_ = Kp;
  Ki_ = Ki;
  Kd_ = Kd;
  prev_cte_ = 0;
  i_error_ = 0;
  timestamp_ = std::chrono::steady_clock::now();
}

void PID::UpdateError(double cte) {
  p_error_ = cte;
  i_error_ += cte;
  auto now = std::chrono::steady_clock::now();
  long dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - timestamp_).count();
  timestamp_ = now;
  d_error_ = (cte - prev_cte_) / dt * 100;
  prev_cte_ = cte;
}

double PID::TotalError() {
  return p_error_ + i_error_ + d_error_;
}

double PID::GetValue() {
  return -Kp_ * p_error_ - Ki_ * i_error_ - Kd_ * d_error_;
}

