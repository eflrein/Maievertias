#include "DirectoryPosix.h"

namespace maievertias{


    ///iterator

    Directory::iterator::iterator(DIR *dir,const Path &path)
        :m_dir(dir),
         m_path(path),
         m_name(""){
        if(dir == nullptr){
            m_name = Path("");
        }else{
            dirent *p = readdir(dir);
            m_name = Path(p == nullptr ? "" : p->d_name);
        }
    }

    Directory::iterator::~iterator() = default;

    Directory::iterator &Directory::iterator::operator++() noexcept{
        dirent *p = readdir(m_dir);
        m_name = Path(p == nullptr ? "" : p->d_name);
        return *this;
    }

    File Directory::iterator::operator*() const noexcept{
        return File(m_path/m_name);
    }

    bool Directory::iterator::operator==(const Directory::iterator &rhs) const noexcept{
        return m_name == rhs.m_name;
    }

    bool Directory::iterator::operator!=(const Directory::iterator &rhs) const noexcept{
        return m_name != rhs.m_name;
    }

    ///directory
    Directory::Directory(const File &file)
        :m_file(file),
         m_dir(nullptr){
        m_dir = opendir(m_file.path().c_str());
        if(m_dir == nullptr)
            throw File::FileError(errno);
    }

    Directory::~Directory(){
        closedir(m_dir);
    }

    Directory::iterator Directory::begin()const{
        return iterator(m_dir,m_file.path());
    }

    Directory::iterator Directory::end()const{
        return iterator(nullptr,m_file.path());///construct a "" path
    }

}
