#pragma once
#include <string>
#include <rttr/type>

class Person {
public:
    Person();
    ~Person();
    void set_name(const std::string& name);
    const std::string& get_name() const;

    void set_age(int age);
    int get_age();

    virtual void show();
    void growupTo(int age = 20);
private:
    std::string m_name;
    int m_age;

    RTTR_ENABLE();
};