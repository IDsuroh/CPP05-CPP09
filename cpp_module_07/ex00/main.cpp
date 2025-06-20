#include <iostream>
#include <string>
#include "whatever.hpp"

int main(void) {
    int a = 2;
    int b = 3;
    
    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
    std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
    
    std::string c = "chaine1";
    std::string d = "chaine2";
    
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
    std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
    
    return 0;
}

/*

:: = Global scope

🌍 GLOBAL SCOPE (entire program)
├── globalVariable
├── globalFunction()  
├── swap<T>()         ← the template functions live here!
├── min<T>()
├── max<T>()
│
├── 📦 MyNamespace
│   ├── namespaceVariable
│   └── namespaceFunction()
│
├── 🏠 MyClass
│   ├── memberVariable
│   └── memberFunction()
│       └── 🚪 Local scope inside memberFunction
│           └── localVariable
│
└── 🏠 main()
    └── 🚪 Local scope inside main
        └── localVariable

Why the Templates Are in Global Scope?
// whatever.hpp
template <typename T>
void swap(T& a, T& b) {    // ← This is in GLOBAL SCOPE
    // Not inside any namespace, class, or function
}

This means:

✅ Can be called from anywhere in the program
✅ Available to any file that includes whatever.hpp
✅ Accessible from main(), other functions, classes, etc.


Scope Resolution Examples
int value = 100;        // Global scope

namespace Test {
    int value = 200;    // Namespace scope
}

class Example {
public:
    static int value;   // Class scope
};
int Example::value = 300;

int main() {
    int value = 400;    // Local scope
    
    // How to access each one:
    std::cout << value;         // 400 (local scope - closest)
    std::cout << ::value;       // 100 (global scope) ← This is what :: does!
    std::cout << Test::value;   // 200 (namespace scope)
    std::cout << Example::value;// 300 (class scope)
}

Templates are called anywhere such as in a namespace or in a class
or locally.

*/