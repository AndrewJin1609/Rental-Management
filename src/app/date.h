#ifndef TRONICRENTALS_SRC_APP_DATE_H_
#define TRONICRENTALS_SRC_APP_DATE_H_

#include <string>
using namespace std;

class Date {
 private:
  string day_;
  string month_;
  string year_;
 public:
  Date();
  Date(const string &date_string);
  int GetDay() const;
  int GetMonth() const;
  int GetYear() const;
  string PrintDate() const;
  int Raw() const;
  bool operator<(const Date &other) const;
  bool operator>(const Date &other) const;
  bool operator>=(const Date &other) const;
  bool operator<=(const Date &other) const;
  Date &operator=(const Date &other);
};

#endif  // TRONICRENTALS_SRC_APP_DATE_H_
