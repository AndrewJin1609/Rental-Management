#ifndef APP_H
#define APP_H

#include "car.h"

/*
----------------------------------------------------------------------------
  This is where you start.
  However, make sure you do not write all your code in a single file!
----------------------------------------------------------------------------
*/

class App {
 private:
  vector<Car *> garage_;
  bool date_configured_;
  Date current_date_;
 public:
  App();
  void CreateCar(const std::string &registration_plate, const std::string &make,
                 const std::string &daily_rental_fee);
  void DisplayCars() const;
  void ConfigureDate(const std::string &date);
  void DisplayDate() const;
  void CreateRental(const std::vector<std::string> options);
  void DisplayRentals(const std::string &registration_plate) const;
  void AddGPSUnit(const std::string &rental_reference);
  void AddChildSeat(const std::string &rental_reference);
  void AddInsurance(const std::string &rental_reference);
  void DisplayReceipt(const std::string &rental_reference) const;

  Car *FindCar(const string &plate) const;
  Rental *FindRental(const string &ref) const;
  void InitialiseAddOn(const string &reference, const string &add_on_type);
};

#endif  // APP_H
