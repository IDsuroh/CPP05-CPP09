#ifndef BASE_HPP
#define BASE_HPP

class Base {
public:
    virtual ~Base();
};

class A : public Base
{};

class B : public Base
{};

class C : public Base
{};

Base* generate(void);

void identify(Base* p); // function overloading
void identify(Base& p); // function overloading

#endif

/*

===What is a Base Class?===
A base class (also called a parent class or superclass) is a class that serves as
a foundation for other classes to inherit from. It defines common properties and behaviors
that derived classes can use and extend.


===Base Classes vs Utility Classes===
Base Classes (Inheritance-based)
Base classes are designed for inheritance - they create a parent-child relationship:

Utility Classes (Composition-based)
Utility classes provide standalone functionality - they're used as tools:


===Base Class vs Full Polymorphic Class===
Base Class (Minimal Interface)
A base class can be very minimal - just providing the foundation for inheritance:
Full Polymorphic Class (Rich Interface)
A full polymorphic class defines a complete interface with meaningful behavior:

When to Use Each?
Base Class (Minimal):
- Type identification systems
- Plugin architectures where you just need to know "what type is this?"
- Simple polymorphic containers
Full Polymorphic Class:
- Complete object-oriented designs
- When derived classes share significant common behavior
- Complex systems with rich interfaces
- GUI frameworks, game engines, graphics systems


===Why We Made the Base Class?===

The Virtual Destructor is Key:
- Enables RTTI: Without a virtual function, dynamic_cast won't work
- Polymorphic Behavior: Makes the class "polymorphic" in C++ terms
- Proper Cleanup: Ensures derived class destructors are called
    when deleting through base pointer

Without Virtual Destructor:
class Base {};  // No virtual functions
// dynamic_cast<A*>(basePtr) would NOT work!
*/