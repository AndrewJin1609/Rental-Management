#include "app.h"

using namespace std;

/*
----------------------------------------------------------------------------
  This is where you start.
  However, make sure you do not write all your code in a single file!
----------------------------------------------------------------------------
*/

App::App() {
  garage_ = {};
  date_configured_ = false;
  current_date_ = Date();
}

void App::CreateCar(const string &registration_plate,
                    const string &make,
                    const string &daily_rental_fee) {
  string plate = Utils::GetUppercase(registration_plate);
  // Checking for plate duplicate
  for (auto &car : garage_) {
    if (plate == car->GetPlate()) {
      Message::CAR_ALREADY_EXISTS.PrintMessage({plate});
      return;
    }
  }

  // Creating
  Car *new_car = new Car(plate, make, daily_rental_fee);
  if (!new_car->IsValid()) {
    return;
  }
  garage_.push_back(new_car);
  Message::CAR_CREATED.PrintMessage({plate});
}

void App::DisplayCars() const {
  // No cars
  if (garage_.empty()) {
    Message::NO_CARS_AVAILABLE.PrintMessage();
    return;
  }

  // Formatting
  string plural_1 = (garage_.size() == 1) ? "is" : "are";
  string plural_2 = (garage_.size() == 1) ? "" : "s";
  Message::NUMBER_OF_CARS_AVAILABLE.PrintMessage({
    plural_1,
    to_string(garage_.size()),
    plural_2});

  // Listing
  for (auto &car : garage_) {
    car->PrintForApp(current_date_);
  }
}

void App::ConfigureDate(const std::string &date) {
  Date proposed_date = Date(date);

  // Checking validity
  if (proposed_date < current_date_) {
    Message::DATE_BEFORE_CURRENT.PrintMessage();
    return;
  }

  // Configuring
  current_date_ = proposed_date;
  Message::DATE_CONFIGURED.PrintMessage({current_date_.PrintDate()});
  date_configured_ = true;
}

void App::DisplayDate() const {
  if (!date_configured_) {
    Message::DATE_NOT_CONFIGURED.PrintMessage();
    return;
  }
  Message::DATE_CURRENTLY.PrintMessage({current_date_.PrintDate()});
}

Car *App::FindCar(const string &plate) const {
  // Looping through cars
  for (auto &car : garage_) {
    if (plate == car->GetPlate()) {
      return car;
    }
  }
  Message::NO_CAR_WITH_PLATE.PrintMessage({plate});
  return nullptr;
}

void App::CreateRental(const std::vector<std::string> options) {
  string plate = Utils::GetUppercase(options[0]);
  Date *start = new Date(options[1]);
  Date *end = new Date(options[2]);
  string id = Utils::GetLowercase(options[3]);

  // Checking dates
  if (!date_configured_) {
    Message::DATE_NOT_CONFIGURED.PrintMessage();
    return;
  }
  if (*start < current_date_) {
    Message::START_DATE_BEFORE_TODAY.PrintMessage({current_date_.PrintDate()});
    return;
  }
  if (*end < *start) {
    Message::END_DATE_BEFORE_START.PrintMessage({start->PrintDate()});
    return;
  }

  // Finding car
  Car *car = FindCar(plate);
  if (car == nullptr) {
    return;
  }

  // Creating
  car->InsertRental(*start, *end, id);
}

void App::DisplayRentals(const std::string &registration_plate) const {
  if (!date_configured_) {
    Message::DATE_NOT_CONFIGURED.PrintMessage();
    return;
  }

  // Finding car
  string plate = Utils::GetUppercase(registration_plate);
  Car *car = FindCar(plate);
  if (car == nullptr) {
    return;
  }

  // Displaying
  car->PrintRentals(current_date_);
}

Rental *App::FindRental(const string &ref) const {
  // Looping through rentals
  for (auto &car : garage_) {
    for (auto &booking : car->bookings_) {
      if (ref == booking->GetRef()) {
        return booking;
      }
    }
  }
  return nullptr;
}

void App::InitialiseAddOn(const string &reference, const string &add_on_type) {
  string ref = Utils::GetUppercase(reference);
  Rental *rental = FindRental(ref);

  // Checking rental validity
  if (rental == nullptr) {
    Message::CANNOT_ADD_ADDON_REFERENCE_NOT_FOUND.PrintMessage({
      ref,
      add_on_type});
    return;
  }
  if (rental->GetStart() < current_date_) {
    Message::CANNOT_ADD_ADDON_IN_PAST.PrintMessage({
      ref,
      add_on_type});
    return;
  }

  // Inserting
  rental->InsertAddOn(add_on_type);
}

void App::AddGPSUnit(const std::string &rental_reference) {
  InitialiseAddOn(rental_reference,
                  Message::ADDON_GPS_UNIT_NAME.GetMessage());
}

void App::AddChildSeat(const std::string &rental_reference) {
  InitialiseAddOn(rental_reference,
                  Message::ADDON_CHILD_SEAT_NAME.GetMessage());
}

void App::AddInsurance(const std::string &rental_reference) {
  InitialiseAddOn(rental_reference,
                  Message::ADDON_INSURANCE_NAME.GetMessage());
}

void App::DisplayReceipt(const std::string &rental_reference) const {
  // Finding
  string ref = Utils::GetUppercase(rental_reference);
  Rental *rental = FindRental(ref);
  if (rental == nullptr) {
    Message::REFERENCE_NOT_FOUND_NO_RECEIPT.PrintMessage({ref});
    return;
  }

  // Displaying
  rental->PrintReceipt();
}
