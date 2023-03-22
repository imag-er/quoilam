#include <sqlite3.h>
#include <string>
#include <initializer_list>
#include <memory>
#include "StdLogger.h"
namespace quoilam
{
    using StrList = std::initializer_list<std::string>;
    using Table = std::initializer_list<StrList>;
    
    class Database
    {
    public:
        class Query;

        Database(const std::string &path);
        ~Database();

        void create_table(const std::string &table_name,
                          const StrList &cols);

        void switch_table(const std::string &table_name);

        void insert_value(const StrList& value);
        void insert_values(const Table &values);

        Query select(const std::string &cmd);

    protected:
        std::string dbpath;
        std::shared_ptr<StdLogger> logger;

        sqlite3 *pDB = nullptr;
    private:
        std::string current_table;
        std::string make_string_list(const StrList &cols);
    };

    class Database::Query
    {
    public:
        void *placeholder;
    };


}