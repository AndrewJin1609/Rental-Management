#include "rental.h"

Rental::Rental(const Date &start,
               const Date &end,
               const string &id,
               const int &daily_fee,
               const string &ref) {
  start_ = start;
  end_ = end;
  n_days_ = end.GetDay() - start.GetDay() + 1;
  id_ = id;
  daily_fee_ = daily_fee;
  ref_ = ref;

  if (n_days_ <= 4) {
    rental_cost_ = n_days_ * daily_fee_;
  } else {
    rental_cost_ = 4 * daily_fee_ + (n_days_ - 4) * daily_fee_ * 0.5;
  }
}

Date Rental::GetStart() const { return start_; }
Date Rental::GetEnd() const { return end_; }
int Rental::GetDays() const { return n_days_; }
string Rental::GetId() const { return id_; }
int Rental::GetDailyFee() const { return daily_fee_; }
string Rental::GetRef() const { return ref_; }

bool Rental::IsAvail(const Date &current_date) {
  // Current date is in rental date range
  if (start_ <= current_date && end_ >= current_date) {
    return false;
  }
  return true;
}

bool Rental::IsValid(const Date &proposed_start,
                      const Date &proposed_end) const {
      // Start date overlaps
  if ((proposed_start >= start_ && proposed_start <= end_) ||
      // End date overlaps
      (proposed_end >= start_ && proposed_end <= end_) ||
      // Existing rental completely overlaps
      (proposed_start <= start_ && proposed_end >= end_)) {
    return false;
  }
  return true;
}

bool Rental::IsCurrentOrUpcoming(const Date &current_date) const {
      // Current
  if ((start_ <= current_date && end_ >= current_date) ||
      // Upcoming
      (start_ > current_date)) {
    return true;
  }
  return false;
}

void Rental::PrintForApp() const {
  // Determining format
  string plural = (n_days_ == 1) ? "" : "s";

  // Displaying
  Message::LIST_RENTAL_ENTRY.PrintMessage({
    start_.PrintDate(),
    end_.PrintDate(),
    to_string(n_days_),
    plural,
    ref_});
}

void Rental::InsertAddOn(const string &add_on_type) {
  // Determining add-on type
  AddOn *new_add_on;
  if (add_on_type == Message::ADDON_GPS_UNIT_NAME.GetMessage()) {
    new_add_on = new GPS(n_days_);
  } else if (add_on_type == Message::ADDON_CHILD_SEAT_NAME.GetMessage()) {
    new_add_on = new ChildSeat(n_days_);
  } else if (add_on_type == Message::ADDON_INSURANCE_NAME.GetMessage()) {
    new_add_on = new Insurance(n_days_, rental_cost_);
  }

  // Inserting
  extras_.push_back(new_add_on);
  Message::ADDON_ADDED.PrintMessage({add_on_type});
}

void Rental::PrintReceipt() const {
  int grand_total = 0;

  // Top
  Message::RECEIPT_TOP_PART.PrintMessage({
    ref_,
    id_,
    start_.PrintDate(),
    end_.PrintDate(),
    to_string(n_days_)});

  // Car cost
  Message::RECEIPT_COST_BREAKDOWN_CAR_RENTAL.PrintMessage({
    to_string(rental_cost_)});
  grand_total += rental_cost_;

  // Add-ons
  for (auto &add_on : extras_) {
    add_on->PrintForReceipt();
    grand_total += add_on->GetPrice();
  }

  // Bottom
  Message::RECEIPT_BOTTOM_PART.PrintMessage({to_string(grand_total)});
}
