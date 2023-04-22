#include "Database.h"

#include <sstream>
#include <cstring>
namespace quoilam::util
{
    Database::Database(const std::string &path, io::iomode open_flags)
        : logger(new io::StdLogger("database"))
    {
        int flags = 0;
        switch (open_flags)
        {
        case io::iomode::read:
            flags |= SQLITE_OPEN_READONLY;
            break;
        case io::iomode::readwrite:
            flags |= SQLITE_OPEN_READWRITE;
            break;
        case io::iomode::app:
            flags |= SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
            break;
        case io::iomode::ate:
            // TODO: wait for filesystem succeed
            break;
        default:
            break;
        }
        logger->log(flags);

        int res = sqlite3_open_v2(path.c_str(), &pDB, flags, nullptr);
        if (res != SQLITE_OK)
        {
            logger->log("read table failed. err:", res);
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
    void Database::insert_values(const StrTable &values)
    {
        for (const StrList &line : values)
            insert_value(line);
    }

    const std::tuple<StrList, StrTable> Database::select(const std::string &cmd) const
    {
        char **presult;
        char *errmsg;
        int row, col;

        int res = sqlite3_get_table(pDB, cmd.c_str(), &presult, &row, &col, &errmsg);
        if (res != SQLITE_OK)
        {
            logger->log("cannot read table");
            return {};
        }
        logger->log(row, 'x', col);

        StrList colname;

        StrTable rettable(row + 1);

        for (int i = 0; i <= col - 1; ++i)
            colname.push_back(presult[i]);

        for (int i = col; i < col * row + col; ++i)
            rettable[i / col].push_back(presult[i]);

        sqlite3_free_table(presult);
        return std::make_tuple(colname, rettable);
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