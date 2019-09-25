#include "XTest/XTest.h"
#include "File.h"
#include "Directory.h"

namespace fs = maievertias;

CASE_BEGIN(file_exist_test)
    fs::File file(fs::Path("../File.h"));
    ASSERT(file.path().relative(),"check relative()");
    INFO("name:",file.path().name());
    ASSERT(file.exist(),"check exist()");
    ASSERT(!file.isDirectory(),"check isDirectory()");
    ASSERT(file.isRegularFile(),"check isRegularFile()");
    INFO("size:",file.size());
CASE_END

CASE_BEGIN(file_noexist_test)
    fs::File file(fs::Path("../fuck.h"));
    ASSERT(!file.exist(),"check exist()");
//    file.isDirectory(); ///expetions here
CASE_END

CASE_BEGIN(directory_iterator)
    fs::File file(fs::Path("D:\\git\\Maievertias"));
    for(const auto &subf : fs::Directory(file)){
        INFO(subf.path());
    }
CASE_END

RUN(file_exist_test,
    file_noexist_test,
    directory_iterator)