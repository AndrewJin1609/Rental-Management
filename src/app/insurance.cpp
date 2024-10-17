#include "insurance.h"

Insurance::Insurance(int n_days, int rental_cost) : AddOn(n_days) {
  // Calculating price
  price_ = rental_cost * 0.05;
}
string Insurance::GetType() const {
  return Message::ADDON_INSURANCE_NAME.GetMessage();
}
