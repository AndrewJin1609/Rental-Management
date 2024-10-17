#include "add_on.h"

AddOn::AddOn(int n_days) {
  n_days_ = n_days;
  price_ = 0.0;
}

int AddOn::GetPrice() const { return price_; }

void AddOn::AdjustDays() {
  if (n_days_ > 5) {
    n_days_ = 5;
  }
}

void AddOn::PrintForReceipt() const {
  Message::RECEIPT_COST_BREAKDOWN_ADDON_ITEM.PrintMessage({
    GetType(),
    to_string(price_)});
}
