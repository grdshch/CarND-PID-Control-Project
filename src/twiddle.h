#ifndef PID_TWIDDLE_H
#define PID_TWIDDLE_H

#include "PID.h"
#include <vector>

class Twiddle {
public:
  Twiddle(PID& pid) : pid_(pid), first_run_(true), best_cte_(4), dp_({0.2, 0.2, 0.2}){}
  ~Twiddle() {}
  void Update(double cte);
  double BestError() { return best_cte_;}

private:
  void UpdateParameter();

  PID& pid_;  // reference to PID to update parameters
  bool increase_;  // previous parameter change was increasing
  int parameter_;  // which parameter was changed last time
  std::vector<double> dp_;  // updates of each parameter
  double best_cte_;
  bool first_run_;
};

#endif //PID_TWIDDLE_H
