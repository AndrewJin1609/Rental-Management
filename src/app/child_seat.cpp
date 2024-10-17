#include "child_seat.h"

ChildSeat::ChildSeat(int n_days) : AddOn(n_days) {
  // Calculating price
  AddOn::AdjustDays();
  price_ = n_days_ * 2;
}
string ChildSeat::GetType() const {
  return Message::ADDON_CHILD_SEAT_NAME.GetMessage();
}
