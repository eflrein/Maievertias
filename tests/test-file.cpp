#include "XTest/XTest.h"
#include "File.h"
#include "Directory.h"
#include <memory>

namespace fs = maievertias;

CASE_BEGIN(file_exist_test)
    fs::File file("../File.h");
    ASSERT(file.path().relative(),"check relative()");
    INFO("name:",file.path().name());
    ASSERT(file.exist(),"check exist()");
    ASSERT(!file.isDirectory(),"check isDirectory()");
    ASSERT(file.isRegularFile(),"check isRegularFile()");
    INFO("size:",file.size());
CASE_END

CASE_BEGIN(file_noexist_test)
    fs::File file("../fuck.h");
    ASSERT(!file.exist(),"check exist()");
//    file.isDirectory(); ///expetions here
CASE_END

CASE_BEGIN(directory_iterator)
    fs::File file("D:\\git\\Maievertias");
    for(const auto &subf : fs::Directory(file)){
        INFO(subf.path());
    }
CASE_END

CASE_BEGIN(move_test)
    fs::File f(R"(D:\git\Maievertias\cmake-build-debug\asd)");
    ASSERT(f.exist(),"File not exist");
    f.move(R"(D:\git\Maievertias\cmake-build-release\asd)");
    INFO("moved:",f.path());
    ASSERT(f.exist(),"File not exist");
CASE_END

CASE_BEGIN(rename_test)
    fs::File f(R"(D:\git\Maievertias\cmake-build-debug\asdasd.txt)");
    f.rename("asd.txt");
CASE_END

CASE_BEGIN(delete_test)
    fs::File f(R"(D:\git\Maievertias\cmake-build-debug\asdasd.txt)");
    ASSERT(f.exist(),"file not exist , cannot be deleted");
    ASSERT(!f.remove().exist(),"File exist , delete failed");
CASE_END

CASE_BEGIN(get_current_dir_test)
    auto d = fs::File::getCurrentDirectory();
    INFO(d.path());
CASE_END

RUN(file_exist_test,
    file_noexist_test,
    directory_iterator,
    //move_test //passed,
    //rename_test//passed
    //delete_test //passed
    get_current_dir_test
)