#include <iostream>

int main() {
  int integer1, integer2, integer3;

  std::cout << "Enter integer #1: ";
  std::cin >> integer1;

  std::cout << "Enter integer #2: ";
  std::cin >> integer2;

  std::cout << "Enter integer #3: ";
  std::cin >> integer3;

  int *ptr1 = new int;
  int *ptr2 = new int;
  int *ptr3 = new int;

  *ptr1 = integer1;
  *ptr2 = integer2;
  *ptr3 = integer3;

  std::cout << "\nValues of the variables:" << std::endl;
  std::cout << "integer #1: " << integer1 << std::endl;
  std::cout << "integer #2: " << integer2 << std::endl;
  std::cout << "integer #3: " << integer3 << std::endl;

  std::cout << "\nContents of the pointers:" << std::endl;
  std::cout << "pointer #1: " << ptr1 << ", value: " << *ptr1 << std::endl;
  std::cout << "pointer #2: " << ptr2 << ", value: " << *ptr2 << std::endl;
  std::cout << "pointer #3: " << ptr3 << ", value: " << *ptr3 << std::endl;

  delete ptr1;
  delete ptr2;
  delete ptr3;

  return 0;
}
