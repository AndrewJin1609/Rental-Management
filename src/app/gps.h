#ifndef TRONICRENTALS_SRC_APP_GPS_H_
#define TRONICRENTALS_SRC_APP_GPS_H_

#include "add_on.h"

class GPS : public AddOn {
 public:
  GPS(int n_days);
  string GetType() const override;
};

#endif  // TRONICRENTALS_SRC_APP_GPS_H_
