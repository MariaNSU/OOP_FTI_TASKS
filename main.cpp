#include <iostream>
#include <list>
#include "sharedPtr.h"

int main() {
    std::list<int> l = {7, 5, 16, 8};
    auto l_ptr = &l;
    SharedPTR < std::list<int>, std::default_delete<std::list<int> > > a(l_ptr);
    auto x = a.get();
    std::cout << x << std::endl;
    return 0;
}