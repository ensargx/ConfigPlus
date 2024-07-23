#pragma once

#include <string>
#include <vector>
#include <type_traits>

class IConfigClass
{
protected:
    std::vector<size_t> m_VariableOffsets;
};

// make sure a typename is derived from IConfigClass or
// can be converted to string
template <typename T>
using IsDerivedOrConvertibleToString = std::disjunction<std::is_base_of<IConfigClass, T>, std::is_convertible<T, std::string>>;

// check template type inherits from IConfigClass or 
// is a type which can be converted to string (like
// int, float, double, etc.) also make sure the Variable
// is in a class that inherits from IConfigClass
template <typename T, typename = std::enable_if<std::is_convertible<T, std::string>::value>>
struct ConfigVariable
{
    std::string name;
    T value;
    ConfigVariable(std::string name, T value = T{}) : name(name), value(value) {}

    operator T() const { return value; }
    const T& operator=(const T& rhs) { return value = rhs; }
};

class TheOtherClass : public IConfigClass
{
public:
    ConfigVariable<int> myInt{ "TheInt2" };
    ConfigVariable<float> myFloat{ "TheFloat2" };
};

// Example usage
class Config : public IConfigClass
{
public:
    ConfigVariable<int> myInt{ "TheInt" };
    ConfigVariable<float> myFloat{ "TheFloat" };

    ConfigVariable<TheOtherClass> otherClass{ "TheOtherClass" };
};

