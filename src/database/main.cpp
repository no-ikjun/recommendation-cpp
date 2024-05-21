#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Contact {
  std::string name;
  std::string phone_number;

  // 직렬화 함수
  void serialize(std::ostream& os) const {
    std::size_t name_len = name.length();
    std::size_t phone_len = phone_number.length();

    os.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
    os.write(name.c_str(), name_len);
    os.write(reinterpret_cast<const char*>(&phone_len), sizeof(phone_len));
    os.write(phone_number.c_str(), phone_len);
  }

  // 역직렬화 함수
  void deserialize(std::istream& is) {
    std::size_t name_len, phone_len;
    is.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
    name.resize(name_len);
    is.read(&name[0], name_len);

    is.read(reinterpret_cast<char*>(&phone_len), sizeof(phone_len));
    phone_number.resize(phone_len);
    is.read(&phone_number[0], phone_len);
  }
};


class ContactDatabase {
private:
  std::vector<Contact> contacts;

public:
  void addContact(const Contact& contact) {
    contacts.push_back(contact);
  }

  void listContacts() const {
    for (const auto& contact : contacts) {
      std::cout << "Name: " << contact.name << ", Phone: " << contact.phone_number << std::endl;
    }
  }

  void saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    for (const auto& contact : contacts) {
      contact.serialize(file);
    }
  }

  void loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    while (!file.eof()) {
      Contact contact;
      contact.deserialize(file);
      if (file) contacts.push_back(contact); // Check for valid deserialization
    }
  }
};


int main() {
  ContactDatabase db;
  db.loadFromFile("contacts.bin"); // 파일로부터 불러오기

  bool done = false;
  while (!done) {
    std::cout << "1. Add contact\n2. List contacts\n3. Save and exit\nChoose an option: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
      Contact contact;
      std::cout << "Enter name: ";
      std::cin >> contact.name;
      std::cout << "Enter phone number: ";
      std::cin >> contact.phone_number;
      db.addContact(contact);
    } else if (choice == 2) {
      db.listContacts();
    } else if (choice == 3) {
      db.saveToFile("contacts.bin"); // 파일로 저장하기
      done = true;
    } else {
      std::cout << "Invalid option." << std::endl;
    }
  }

  return 0;
}
