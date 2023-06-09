#ifndef _WIN32
#include <sqlite3.h>
#endif
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include "StdLogger.h"
#include "Typedef.h"
namespace quoilam::util
{

    using StrList = std::vector<std::string>;
    using StrTable = std::vector<StrList>;
#ifndef _WIN32

    class Database
    {
    public:
      

        Database(const std::string &path,io::iomode io_flags = io::iomode::read);
        ~Database();

        void create_table(const std::string &table_name,
                          const StrList &cols);

        void switch_table(const std::string &table_name);

        void insert_value(const StrList& value);
        void insert_values(const StrTable &values);

        const std::tuple<StrList,StrTable> select(const std::string &cmd) const;

    protected:
        std::string dbpath;
        std::shared_ptr<io::StdLogger> logger;

        sqlite3 *pDB = nullptr;
    private:
        std::string current_table;
        std::string make_string_list(const StrList &cols);
    };


#endif

}