#pragma once

#include <vector>
#include <type_traits>
#include <cstddef>
#include <iostream>

class IConfigClass
{
protected:
    std::vector<size_t> m_VariableOffsets;
};

// there are 3 options that T can be
//   1 - a simple type (int, float, double, etc) 
//   2 - a class that inherits from IConfigClass (another config class)
//   3 - a vector which can be nested as many times as needed which 
//         will eventually end up being one of the above 2 options

template <typename T>
using is_simple_type = std::disjunction<std::is_arithmetic<T>, std::is_enum<T>>;

template <typename T>   
using is_config_class = std::is_base_of<IConfigClass, T>;

template <typename T>
struct is_vector : std::false_type {};

// Helper to get the class type from a member pointer
template <typename T>
struct get_member_class;

// Specialization for member pointer types
template <typename ClassType, typename MemberType>
struct get_member_class<MemberType ClassType::*> {
    using type = ClassType;
};

template <typename T>
struct get_class_from_member;

template <typename ClassT, typename MemberT>
struct get_class_from_member<MemberT ClassT::*>
{
    /* class Test1
     * {
     *    int a;
     *    float b;
    */
    // we have the a or b members, 
    // we must return the class type Test1 
    
    using type = ClassT;
};

template <typename T>
struct VariableType 
{
    // static_assert(is_class_inherits_from_IConfigClass_v<T>, "Invalid type");
    // static_assert(is_simple_type<T>::value || is_config_class<T>::value || is_vector<T>::value, "Invalid type");
};

template <typename T>
struct Variable : public VariableType<T>
{

    using ClassType = typename get_class_from_member<T>::type;

    T value;
    operator T() const { return value; }
    Variable& operator=(const T& v) { value = v; return *this; }
};


struct Config1 : public IConfigClass
{
    Variable<int> var1;
    Variable<float> var2;
};

struct Config : public IConfigClass
{
    Variable<int> var1;
    Variable<float> var2;
    Variable<Config1> var3;
};
