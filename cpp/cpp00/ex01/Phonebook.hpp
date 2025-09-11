#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
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

class PhoneBook {
public:
  PhoneBook();
  void add_contact(std::string fname, std::string lname,
                   std::string nname, std::string phone,
                   std::string secret);
  void display_contacts_list();
  void display_contact_details(int index);
  int get_num_of_contacts() const;

private:
  Contact _contacts[8];
  int _num_of_contacts;
  int _oldest_contact;
};

#endif