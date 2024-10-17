#ifndef TRONICRENTALS_SRC_APP_CHILD_SEAT_H_
#define TRONICRENTALS_SRC_APP_CHILD_SEAT_H_

#include "add_on.h"

class ChildSeat : public AddOn {
 public:
  ChildSeat(int n_days);
  string GetType() const override;
};

#endif  // TRONICRENTALS_SRC_APP_CHILD_SEAT_H_
