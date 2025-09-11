#include "Contact.hpp"

void Contact::set_fname(std::string name) {
  _first_name = name;
}
void Contact::set_lname(std::string name) {
  _last_name = name;
}
void Contact::set_nname(std::string name) {
  _nickname = name;
}
void Contact::set_phone_number(std::string num) {
  _phone_number = num;
}
void Contact::set_secret(std::string secret) {
  _darkest_secret = secret;
}

std::string Contact::get_fname() {
  return (_first_name);
}
std::string Contact::get_lname() {
  return (_last_name);
}
std::string Contact::get_nname() {
  return (_nickname);
}
std::string Contact::get_phone_number() {
  return (_phone_number);
}
std::string Contact::get_secret() {
  return (_darkest_secret);
}