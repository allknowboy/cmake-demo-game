#include <rttr/type>
#include "fmt/format.h"

int main(int argc, char** argv)
{
    fmt::print("hello {} \n", "fmt");

    rttr::type t = rttr::type::get_by_name("Person");
    rttr::variant v = t.create();
    t.get_property("name").set_value(v, std::string("limo"));
    t.get_property("age").set_value(v, 10);
    t.get_method("show").invoke(v);
    t.get_method("growupTo").invoke(v, rttr::argument{11});
}