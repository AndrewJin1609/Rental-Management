#ifndef TRONICRENTALS_SRC_APP_RENTAL_H_
#define TRONICRENTALS_SRC_APP_RENTAL_H_

#include <vector>

#include "date.h"
#include "gps.h"
#include "child_seat.h"
#include "insurance.h"

class Rental {
 private:
  Date start_;
  Date end_;
  int n_days_;
  string id_;
  int daily_fee_;
  string ref_;
  int rental_cost_;

 public:
  Rental(const Date &start,
         const Date &end,
         const string &id,
         const int &daily_fee,
         const string &ref);
  vector<AddOn *> extras_;
  Date GetStart() const;
  Date GetEnd() const;
  int GetDays() const;
  string GetId() const;
  int GetDailyFee() const;
  string GetRef() const;
  bool IsAvail(const Date &current_date);
  bool IsValid(const Date &proposed_start, const Date &proposed_end) const;
  bool IsCurrentOrUpcoming(const Date &current_date) const;
  void PrintForApp() const;
  void InsertAddOn(const string &add_on_type);
  void PrintReceipt() const;
};

#endif  // TRONICRENTALS_SRC_APP_RENTAL_H_
