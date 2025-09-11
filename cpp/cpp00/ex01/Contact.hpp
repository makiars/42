#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
private:
  std::string _first_name;
  std::string _last_name;
  std::string _nickname;
  std::string _phone_number;
  std::string _darkest_secret;

public:
  void set_fname(std::string name);
  void set_lname(std::string name);
  void set_nname(std::string name);
  void set_phone_number(std::string num);
  void set_secret(std::string secret);

  std::string get_fname();
  std::string get_lname();
  std::string get_nname();
  std::string get_phone_number();
  std::string get_secret();
};

#endif