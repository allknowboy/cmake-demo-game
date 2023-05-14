#include "person.h"
#include "fmt/format.h"
#include <rttr/registration>

RTTR_REGISTRATION
{
    rttr::registration::class_<Person>("Person")
        .constructor<>()
        (
            rttr::policy::ctor::as_std_shared_ptr
        )
        .property("name", &Person::get_name, &Person::set_name)
        .property("age", &Person::get_age, &Person::set_age)
        .method("show", &Person::show)
        .method("growupTo", &Person::growupTo)
        (
            rttr::default_arguments(20),
            rttr::parameter_names("age")
        );

}

Person::Person()
    :m_age(0)
{

}

Person::~Person()
{

}

void Person::set_name(const std::string& name)
{
    m_name = name;
}

const std::string& Person::get_name() const
{
    return m_name;
}

void Person::set_age(int age)
{
    m_age = age;
}

int Person::get_age()
{
    return m_age;
}

void Person::show()
{
    fmt::print("My name is {}, i'm {} years old. \n", m_name.c_str(), m_age);
}

void Person::growupTo(int age)
{
    m_age = age;
    fmt::print("{} growup to {} years old. \n", m_name.c_str(), m_age);
}