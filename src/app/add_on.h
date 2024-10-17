#ifndef TRONICRENTALS_SRC_APP_ADD_ON_H_
#define TRONICRENTALS_SRC_APP_ADD_ON_H_

#include <string>

#include "message.h"

using namespace std;

class AddOn {
 protected:
  int n_days_;
  int price_;
 public:
  AddOn(int n_days);
  void AdjustDays();
  int GetPrice() const;
  virtual string GetType() const = 0;
  void PrintForReceipt() const;
};

#endif  // TRONICRENTALS_SRC_APP_ADD_ON_H_
