#include <iostream>

 int main() {
     int x; // default-initialized: value is indeterminate
     std::cout << x << "\n";
     int y{};     // value-initialized: guaranteed to be 0
     std::cout << y << "\n"; // definitely 0

     // elements have indeterminate values
     int* data1 = new int[5];

     // elements are value-initialized to 0
     int* data2 = new int[5]{};
 }