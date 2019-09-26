#include "Path.h"

#include <utility>

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
    Path::Path(std::string str)
        :m_separator('/'),
         m_has_root(false),
         m_raw_path(std::move(str)),
         m_components(){
        //empty
        if(m_raw_path.empty())return;
        //cache some var
        auto beg = m_raw_path.begin();
        auto end = m_raw_path.end();
        //detect separator
        for(auto &c:m_raw_path){
            if(c == '\\'){
                m_separator = '\\';
                break;
            }else if(c == '/'){
                m_separator = '/';
                break;
            }
        }
        //replace all separator
        for(auto &c:m_raw_path){
            if(c == '/' || c == '\\'){
                c = m_separator;
            }
        }
        //detect root
        auto itr = beg;
        if(*itr == m_separator){
            //separator is the 1st character
            //root directory
            m_has_root = true;
            ++itr;
            m_components.emplace_back(beg,itr);
        }else{
            for(;itr != end && *itr != m_separator;++itr);
            --itr;
            if(*itr == ':'){
                //windows derive symbol
                m_has_root = true;
            }
            itr = beg;
        }
        //split component
        for(auto itrl = itr;itrl != end;){
            auto itrr = std::next(itrl);
            for(;itrr != end && *itrr != m_separator;++itrr);
            if(itrr == end){
                m_components.emplace_back(itrl,end);
                break;
            }else{
                m_components.emplace_back(itrl,itrr);
                itrl = std::next(itrr);
            }
        }
    }

    Path::Path(const Path &) = default;

    Path::Path(Path &&)noexcept = default;

    Path::~Path() = default;

    Path &Path::operator=(const Path &) = default;

    Path &Path::operator=(Path &&) noexcept = default;

    const char *Path::c_str() const noexcept{
        return m_raw_path.c_str();
    }

    Path Path::name() const{
        auto &p = m_components.back();
        return Path(std::string(p.first,p.second));
    }

    Path Path::extension() const{
        auto &p = m_components.back();
        auto point_itr = p.first;
        for(auto itr = p.first; itr != p.second;++itr){
            if(*itr == '.'){
                point_itr = itr;
            }
        }
        if(point_itr == p.first){
            return Path(std::string(p.second,p.second));
        }else{
            return Path(std::string(std::next(point_itr),p.second));
        }
    }

    Path Path::parent() const{
        if(m_components.size() < 2){
            return Path("");
        }else{
            auto itr = m_components.end();
            itr = std::prev(itr);
            itr = std::prev(itr);
            return Path(std::string(m_raw_path.cbegin(),itr->second));
        }
    }

    Path Path::path() const{
        return Path(*this);
    }

    Path Path::root() const {
        if(hasRoot()){
            auto &p = m_components.front();
            return Path(std::string(p.first,p.second));
        }
        return Path("");
    }

    bool Path::empty() const noexcept{
        return m_raw_path.empty();
    }

    bool Path::absolute() const noexcept{
        return hasRoot();
    }

    bool Path::relative() const noexcept{
        return !hasRoot();
    }

    Path &Path::changeSeparator(char seperator) noexcept{
        m_separator = seperator;
        for(auto &c:m_raw_path){
            if(c == '/' || c == '\\'){
                c = m_separator;
            }
        }
        return *this;
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

    bool Path::operator==(const Path &rhs) const noexcept{
        return m_raw_path == rhs.m_raw_path;
    }

    bool Path::operator!=(const Path &rhs) const noexcept{
        return m_raw_path != rhs.m_raw_path;;
    }

    bool Path::operator<=(const Path &rhs) const noexcept{
        return m_raw_path <= rhs.m_raw_path;;
    }

    bool Path::operator>=(const Path &rhs) const noexcept{
        return m_raw_path >= rhs.m_raw_path;;
    }

    bool Path::operator<(const Path &rhs) const noexcept{
        return m_raw_path < rhs.m_raw_path;;
    }

    bool Path::operator>(const Path &rhs) const noexcept{
        return m_raw_path > rhs.m_raw_path;;
    }

    bool Path::isSelf() const noexcept{
        return name() == Path(".");
    }

    bool Path::isParent() const noexcept{
        return name() == Path("..");
    }

    bool Path::isHome() const noexcept{
        return name() == Path("~");
    }

    Path Path::operator/(const Path &rhs) const noexcept{
        if(m_raw_path.back() == m_separator){
            ///auto reconstruct m_compoent
            return Path(m_raw_path+rhs.m_raw_path);
        }else{
            return Path(m_raw_path+std::string(1,m_separator)+rhs.m_raw_path);
        }
    }

    Path &Path::operator/=(const Path &rhs) noexcept{
        return (*this = *this / rhs);
    }


}
