#include "gps.h"

GPS::GPS(int n_days) : AddOn(n_days) {
  // Calculating price
  AddOn::AdjustDays();
  price_ = n_days_ * 5;
}

string GPS::GetType() const {
  return Message::ADDON_GPS_UNIT_NAME.GetMessage();
}
