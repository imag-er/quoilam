#include "../include/Database.h"

int main()
{
    using namespace quoilam;

    Database q("resource.db",io::app);

    q.create_table("newtable", {"col1 INT", "col2 INT", "col3 INT"});
    q.switch_table("newtable");

    q.insert_value({"1", "2", "3"});

    glog.log("value inserted");
    StrTable t({{"1", "2", "3"},
                {"1", "3", "2"},
                {"2", "1", "3"},
                {"2", "3", "1"},
                {"3", "2", "1"},
                {"3", "1", "2"}});
    q.insert_values(t);
    glog.log("values inserted");

    auto [col, content] = q.select("SELECT * FROM newtable");
    for (auto name : col)
        std::cout << name << ' ';

    for (auto vline : content)
    {
        for (auto ve : vline)
            std::cout << ve << ' ';

        std::cout << std::endl;
    }
    return 0;
}
