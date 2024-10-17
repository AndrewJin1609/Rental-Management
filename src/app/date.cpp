#include "date.h"

#include <string>
using namespace std;

Date::Date() {
  day_ = "00";
  month_ = "00";
  year_ = "0000";
}

Date::Date(const string &date_string) {
  day_ = date_string.substr(0, 2);
  month_ = date_string.substr(3, 2);
  year_ = date_string.substr(6, 4);
}

int Date::GetDay() const { return stoi(day_); }
int Date::GetMonth() const { return stoi(month_); }
int Date::GetYear() const { return stoi(year_); }

string Date::PrintDate() const { return day_ + "/" + month_ + "/" + year_; }

int Date::Raw() const { return stoi(year_ + month_ + day_); }

bool Date::operator<(const Date &other) const {
  return (Raw() < other.Raw());
}

bool Date::operator>(const Date &other) const {
  return (Raw() > other.Raw());
}
bool Date::operator>=(const Date &other) const {
  return (Raw() >= other.Raw());
}

bool Date::operator<=(const Date &other) const {
  return (Raw() <= other.Raw());
}

Date &Date::operator=(const Date &other) = default;
