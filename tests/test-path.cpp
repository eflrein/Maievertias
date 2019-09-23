#include "Path.h"
#include "XTest/XTest.h"

using namespace std;
namespace fs = maievertias;

CASE_BEGIN(empty_path)
    fs::Path p("");
    ASSERT(p.empty(),"check p.empty()");
CASE_END

CASE_BEGIN(unix_root_and_iterator)
    fs::Path p1("/cnm/fuck/");
    ASSERT(p1.hasRoot(),"check p.hasRoot()");
    INFO("output p1 and check all components");
    INFO("p1:",p1);
    for(const auto &path:p1){
        cout << path << '\t';
    }
    cout << endl;
    INFO("Output Done");
CASE_END

//CASE_BEGIN(unix_root2_and_iterator)
//        fs::Path p1("/");
//        ASSERT(p1.hasRoot(),"check p.hasRoot()");
//        INFO("output p1 and check all components");
//        INFO("p1:",p1);
//        for(const auto &path:p1){
//            cout << path << '\t';
//        }
//        cout << endl;
//        INFO("Output Done");
//CASE_END

CASE_BEGIN(windows_root_and_iterator)
        fs::Path p1("C:\\");
        ASSERT(p1.hasRoot(),"check p.hasRoot()");
        INFO("output p1 and check all components");
        INFO("p1:",p1);
        for(const auto &path:p1){
            cout << path << '\t';
        }
        cout << endl;
        INFO("Output Done");
CASE_END

RUN(empty_path,
    unix_root_and_iterator,
    //unix_root2_and_iterator,
    windows_root_and_iterator)