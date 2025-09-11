#include "Phonebook.hpp"

std::string get_string_input(const std::string& prompt) {
  std::string input_value;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input_value);

    if (std::cin.eof()) {
      std::cout << "\nEnd of input detected. Exiting program." << std::endl;
      exit(0);
    }
    if (std::cin.fail()) {
      std::cout << "Input error. Please try again." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      return input_value;
    }
  }
}

int get_int_input(const std::string& prompt) {
  std::string input_str;
  int index;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input_str);

    if (std::cin.eof()) {
      std::cout << "\nEnd of input detected. Exiting program." << std::endl;
      exit(0);
    }

    std::stringstream ss(input_str);

    if ((ss >> index) && ss.eof()) {
      return index;
    }

    std::cout << "Invalid input. Please enter a valid integer." << std::endl;
  }
}

int main() {
  std::string input;
  PhoneBook my_phonebook;

  while (true) {
    std::cout << "\nADD, SEARCH or EXIT: ";
    std::cin >> input;

    if (std::cin.eof()) {
      std::cout << std::endl << "Exiting PhoneBook." << std::endl;
      break;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (input == "ADD") {
      std::string fname = get_string_input("First Name: ");
      std::string lname = get_string_input("Last Name: ");
      std::string nname = get_string_input("Nickname: ");
      std::string phone = get_string_input("Phone number: ");
      std::string secret = get_string_input("Darkest secret: ");
      my_phonebook.add_contact(fname, lname, nname, phone, secret);
    } else if (input == "SEARCH") {
      if (my_phonebook.get_num_of_contacts() == 0) {
        std::cout << "PhoneBook is empty. No contacts to search." << std::endl;
        continue;
      }
      my_phonebook.display_contacts_list();
      int index = get_int_input("Enter the index of the contact to display: ");
      my_phonebook.display_contact_details(index);
    } else if (input == "EXIT") {
      std::cout << "Exiting PhoneBook." << std::endl;
      break;
    } else {
      std::cout << "Invalid command. Please enter ADD, SEARCH, or EXIT."
                << std::endl;
    }
  }
  return 0;
}