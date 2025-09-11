#include "Phonebook.hpp"
#include <iomanip>
#include <iostream>

static std::string format_display_string(const std::string& str) {
  if (str.length() > 10) {
    return str.substr(0, 9) + ".";
  }
  return str;
}

PhoneBook::PhoneBook() : _num_of_contacts(0), _oldest_contact(0) {}

void PhoneBook::add_contact(std::string fname, std::string lname,
                            std::string nname, std::string phone,
                            std::string secret) {
  if (fname == "" || lname == "" || nname == "" || phone == "" ||
      secret == "") {
    std::cout << "One of the fields is empty, retry" << std::endl;
    return;
  }

  int index_to_add = _num_of_contacts;
  if (_num_of_contacts >= 8) {
    index_to_add = _oldest_contact;
    std::cout << "Phonebook is full. Overwriting oldest contact." << std::endl;
    _oldest_contact = (_oldest_contact + 1) % 8;
  } else {
    _num_of_contacts++;
  }

  _contacts[index_to_add].set_fname(fname);
  _contacts[index_to_add].set_lname(lname);
  _contacts[index_to_add].set_nname(nname);
  _contacts[index_to_add].set_phone_number(phone);
  _contacts[index_to_add].set_secret(secret);
}

void PhoneBook::display_contacts_list() {
  if (_num_of_contacts == 0) {
    std::cout << "PhoneBook is empty. No contacts to display." << std::endl;
    return;
  }

  std::cout << std::right << std::setw(10) << "Index"
            << "|" << std::right << std::setw(10) << "First Name"
            << "|" << std::right << std::setw(10) << "Last Name"
            << "|" << std::right << std::setw(10) << "Nickname" << std::endl;
  std::cout << "-------------------------------------------" << std::endl;

  for (int i = 0; i < _num_of_contacts; ++i) {
    std::cout << std::right << std::setw(10) << i << "|" << std::right
              << std::setw(10) << format_display_string(_contacts[i].get_fname())
              << "|" << std::right << std::setw(10)
              << format_display_string(_contacts[i].get_lname()) << "|"
              << std::right << std::setw(10)
              << format_display_string(_contacts[i].get_nname()) << std::endl;
  }
}

void PhoneBook::display_contact_details(int index) {
  if (index < 0 || index >= _num_of_contacts) {
    std::cout << "Invalid index. Please enter an index between 0 and "
              << _num_of_contacts - 1 << "." << std::endl;
    return;
  }

  std::cout << "\n--- Contact Details (Index: " << index << ") ---\n";
  std::cout << "First Name:     " << _contacts[index].get_fname() << std::endl;
  std::cout << "Last Name:      " << _contacts[index].get_lname() << std::endl;
  std::cout << "Nickname:       " << _contacts[index].get_nname() << std::endl;
  std::cout << "Phone Number:   " << _contacts[index].get_phone_number()
            << std::endl;
  std::cout << "Darkest Secret: " << _contacts[index].get_secret() << std::endl;
  std::cout << "--------------------------------------\n";
}

int PhoneBook::get_num_of_contacts() const {
  return _num_of_contacts;
}