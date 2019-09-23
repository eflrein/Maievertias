#include "Path.h"

#include <utility>

#include "XTest/Info.h"
#include "XTest/Assert.h"

namespace maievertias{
    ///iterator
    Path::iterator::iterator(Path::iterator::itr_t itr)
        :m_itr(itr){}

    Path::iterator::~iterator() = default;

    Path::iterator &Path::iterator::operator++() noexcept{
        ++m_itr;
        return *this;
    }

    const Path::iterator Path::iterator::operator++(int) noexcept{
        auto backup = *this;
        ++m_itr;
        return backup;
    }

    bool Path::iterator::operator==(const Path::iterator &rhs) const noexcept{
        return m_itr == rhs.m_itr;
    }

    bool Path::iterator::operator!=(const Path::iterator &rhs) const noexcept{
        return m_itr != rhs.m_itr;
    }

    Path Path::iterator::operator*() const noexcept{
        return Path(std::string(m_itr->first,m_itr->second));
    }

    ///Path
    Path::Path(std::string str,char separator)
        :m_separator(separator),
         m_has_root(false),
         m_raw_path(std::move(str)),
         m_components(){
        //empty
        if(m_raw_path.empty())return;
        //cache some var
        auto beg = m_raw_path.begin();
        auto end = m_raw_path.end();
        //place all separator
        for(char &itr : m_raw_path){
            if(itr == '/' || itr == '\\'){
                itr = separator;
            }
        }
        //detect root
        auto itr = beg;
        if(*itr == separator){
            //separator is the 1st character
            //root directory
            m_has_root = true;
            ++itr;
            m_components.emplace_back(beg,itr);
        }else{
            for(;itr != end && *itr != separator;++itr);
            --itr;
            if(*itr == ':'){
                //windows derive symbol
                m_has_root = true;
                ++itr;
                m_components.emplace_back(beg,itr);
                ++itr; //skip the separator
            }else{
                itr = beg;
            }
        }
        //split component
        for(auto itrl = itr;itrl != end;){
            auto itrr = std::next(itrl);
            for(;itrr != end && *itrr != separator;++itrr);
            if(itrr == end){
                m_components.emplace_back(itrl,end);
                break;
            }else{
                m_components.emplace_back(itrl,itrr);
                itrl = std::next(itrr);
            }
        }
        INFO("HERE");
    }

    Path::Path(const Path &) = default;

    Path::Path(Path &&)noexcept = default;

    Path::~Path() = default;

    Path &Path::operator=(const Path &) = default;

    Path &Path::operator=(Path &&) noexcept = default;

//    Path Path::name() const noexcept{
//        return Path(__cxx11::basic_string());
//    }
//
//    Path Path::extension() const noexcept{
//        return Path(__cxx11::basic_string());
//    }
//
//    Path Path::parent() const noexcept{
//        return Path(__cxx11::basic_string());
//    }
//
//    Path Path::path() const noexcept{
//        return Path(__cxx11::basic_string());
//    }
//
//    Path Path::stem() const noexcept{
//        return Path(__cxx11::basic_string());
//    }
//
//    Path Path::root() const noexcept{
//        return Path(__cxx11::basic_string());
//    }

    bool Path::empty() const noexcept{
        return m_raw_path.empty();
    }

    Path::iterator Path::begin(){
        return iterator(m_components.begin());
    }

    Path::iterator Path::end(){
        return iterator(m_components.end());
    }

    bool Path::hasRoot() const noexcept{
        return m_has_root;
    }


}