#ifndef TRONICRENTALS_SRC_APP_INSURANCE_H_
#define TRONICRENTALS_SRC_APP_INSURANCE_H_

#include "add_on.h"

class Insurance : public AddOn {
 public:
  Insurance(int n_days, int rental_cost);
  string GetType() const override;
};

#endif  // TRONICRENTALS_SRC_APP_INSURANCE_H_
