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
    fs::Path p1("C:\\Windows\\fuck.txt");
    ASSERT(p1.hasRoot(),"check p.hasRoot()");
    INFO("output p1 and check all components");
    INFO("p1:",p1);
    for(const auto &path:p1){
        cout << path << '\t';
    }
    cout << endl;
    INFO("Output Done");
CASE_END

CASE_BEGIN(change_separator)
    fs::Path p1("C:\\Windows\\fuck.txt");
    INFO("p1         ",p1);
    p1.changeSeparator('/');
    INFO("p1 changed ",p1);

    fs::Path p2("/usr/fuck.txt");
    INFO("p2         ",p2);
    p2.changeSeparator('\\');
    INFO("p2 changed ",p2);
CASE_END

CASE_BEGIN(path_component_test_1)
    fs::Path p1("/usr/asad.txt/");
    INFO("p1:",p1);
    INFO("name:",p1.name());
    INFO("extension:",p1.extension());
    INFO("parent:",p1.parent());
    INFO("root:",p1.root());
CASE_END

CASE_BEGIN(absulote_test)
    ASSERT(fs::Path("/aasdasd/").absolute(),"check absolute");
    ASSERT(fs::Path("C:\\Windows\\fuck.txt").absolute(),"check absolute");
    ASSERT(fs::Path("aasdasd/asdasd").relative(),"check relative");
    ASSERT(fs::Path(".\\aasdasd\\asdasd").relative(),"check relative");
CASE_END

CASE_BEGIN(cstr_test)
    INFO("c_str:",fs::Path("C:\\Windows\\fuck.inf").c_str());
CASE_END

RUN(empty_path,
    unix_root_and_iterator,
    //unix_root2_and_iterator,
    windows_root_and_iterator,
    change_separator,
    path_component_test_1,
    absulote_test,
    cstr_test)