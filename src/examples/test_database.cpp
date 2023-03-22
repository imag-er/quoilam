#include "../include/Database.h"

int main()
{
    using namespace std;
    using namespace quoilam;

    Database q("resource.db");

    q.create_table("newtable",{"col1 INT","col2 INT","col3 INT"});
    q.switch_table("newtable");

    q.insert_value({"1","2","3"});

    Table t({
        {"1","2","3"},
        {"1","3","2"},
        {"2","1","3"},
        {"2","3","1"},
        {"3","2","1"},
        {"3","1","2"}
    });
    q.insert_values(t);

    q.select("SELECT * FROM newtable");



    return 0;
}

