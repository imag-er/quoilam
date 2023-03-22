#include "Database.h"
#include <sstream>
#include <cstring>
namespace quoilam
{

    Database::Database(const std::string &path)
        : logger(new StdLogger("database"))
    {

        int res = sqlite3_open(path.c_str(), &pDB);
        if (res)
        {
            logger->log("read error");
            return;
        }

        logger->log("successfully opened database");
    }

    void Database::create_table(const std::string &name,
                                const StrList &cols)
    {
        char *errmsg;

        std::string cmd =
            "create table " +
            name +
            " (" +
            make_string_list(cols) +
            ");";

        int res = sqlite3_exec(pDB, cmd.c_str(), nullptr, nullptr, &errmsg);
        if (res != SQLITE_OK)
        {
            logger->log("cannot create table : \"", name, "\"\terr:", errmsg);
            return;
        }

        logger->log("successfully created table");
        switch_table(name);
    }

    void Database::switch_table(const std::string &table_name)
    {
        if (current_table == table_name)
            return;

        current_table = table_name;
        logger->log("switched into ", current_table);
    }
    void Database::insert_value(const StrList &value)
    {
        char *errmsg;
        std::string cmd =
            "INSERT INTO " +
            current_table +
            " VALUES (" +
            make_string_list(value) +
            ");";

        int res = sqlite3_exec(pDB, cmd.c_str(), 0, 0, &errmsg);
        if (res != SQLITE_OK)
        {
            logger->log("cannot insert. err:", errmsg);
            logger->log("err command: ", cmd);
            return;
        }
    }
    void Database::insert_values(const Table &values)
    {
        for (const StrList &line : values)
        {
            insert_value(line);
        }
    }

    Database::Query Database::select(const std::string &cmd)
    {
        char** presult;
        char* errmsg;
        int row,col;
        sqlite3_get_table(pDB,cmd.c_str(),&presult,&row,&col,&errmsg);
        return Query();
    }
    std::string Database::make_string_list(
        const StrList &cols)
    {
        std::stringstream ss;
        std::string str;
        for (auto col_name : cols)
            ss << col_name << ',';

        str = ss.str();
        return str.assign(str.begin(), str.end() - 1);
    }

    Database::~Database()
    {
        sqlite3_close(pDB);
    }

};