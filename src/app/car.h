#ifndef TRONICRENTALS_SRC_APP_CAR_H_
#define TRONICRENTALS_SRC_APP_CAR_H_

#include "utils.h"
#include "rental.h"

class Car {
 private:
  string registration_plate_;
  string make_;
  string daily_rental_fee_;

 public:
  Car(const string &registration_plate,
      const string &make,
      const string &daily_rental_fee);
  vector<Rental *> bookings_;
  string GetPlate() const;
  string GetMake() const;
  int GetFee() const;
  bool IsValid() const;
  void PrintForApp(const Date &current_date) const;
  void InsertRental(const Date &start, const Date &end, const string &id);
  void PrintRentals(const Date &current_date) const;
};

#endif  // TRONICRENTALS_SRC_APP_CAR_H_
