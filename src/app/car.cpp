#include <cctype>

#include "car.h"

using namespace std;

Car::Car(const string &registration_plate,
         const string &make,
         const string &daily_rental_fee) {
  registration_plate_ = Utils::GetUppercase(registration_plate);
  make_ = Utils::GetUppercase(make.substr(0, 1)) +
          Utils::GetLowercase(make.substr(1, string::npos));
  daily_rental_fee_ = daily_rental_fee;
}

string Car::GetPlate() const { return registration_plate_; }
string Car::GetMake() const { return make_; }
int Car::GetFee() const { return stoi(daily_rental_fee_); }

bool Car::IsValid() const {
  // Checking plate validity
  if (registration_plate_.length() != 6) {
    Message::INVALID_REGISTRATION_PLATE.PrintMessage({registration_plate_});
    return false;
  }

  string letters = registration_plate_.substr(0, 3);
  string numbers = registration_plate_.substr(3, 3);
  for (size_t i = 0; i < 3; i++) {
    if (!isalpha(letters[i]) || !isdigit(numbers[i])) {
      Message::INVALID_REGISTRATION_PLATE.PrintMessage({registration_plate_});
      return false;
    }
  }

  // Checking fee validity
  for (char i : daily_rental_fee_) {
    if (!isdigit(i) && i != '-') {
      Message::RENTAL_FEE_MUST_BE_NUMERIC.PrintMessage();
      return false;
    }
  }

  if (GetFee() <= 0) {
    Message::RENTAL_FEE_NOT_POSITIVE.PrintMessage();
    return false;
  }

  return true;
}

void Car::PrintForApp(const Date &current_date) const {
  // Determining availability
  string availability;
  for (auto &booking : bookings_) {
    if (!booking->IsAvail(current_date)) {
      availability = " not";
      break;
    }
  }

  // Displaying
  Message::LIST_CAR_ENTRY.PrintMessage({
    registration_plate_,
    make_,
    daily_rental_fee_,
    availability});
}

void Car::InsertRental(const Date &start,
                       const Date &end,
                       const string &id) {
  // Checking validity
  for (auto booking : bookings_) {
    if (!booking->IsValid(start, end)) {
      Message::CAR_ALREADY_RENTED.PrintMessage({
        registration_plate_,
        booking->GetRef()});
      return;
    }
  }

  // Creating
  auto *new_rental = new Rental(
      start,
      end,
      id,
      GetFee(),
      "RR-" + registration_plate_ + "-" + to_string(bookings_.size() + 1));

  // Inserting
  bookings_.push_back(new_rental);
  string plural = (new_rental->GetDays() == 1) ? "" : "s";
  Message::CAR_IS_NOW_RENTED.PrintMessage({
    registration_plate_,
    id,
    to_string(new_rental->GetDays()),
    plural,
    new_rental->GetRef()});
}

void Car::PrintRentals(const Date &current_date) const {
  // Finding relevant rentals
  int count = 0;
  for (auto booking : bookings_) {
    if (booking->IsCurrentOrUpcoming(current_date)) {
      // Displaying
      booking->PrintForApp();
      count++;
    }
  }
  if (count == 0) {
    Message::NO_UPCOMING_RENTALS.PrintMessage();
    return;
  }
}
