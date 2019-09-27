#include "DirectoryPosix.h"

namespace maievertias{
    ///iterator

    Directory::iterator::iterator(DIR *dir,const Path &path)
        :m_dir(dir),
         m_dirinfo(nullptr),
         m_path(path){
        if(dir != nullptr){
            m_dirinfo = readdir(dir);
        }
    }

    Directory::iterator::~iterator() = default;

    Directory::iterator &Directory::iterator::operator++() noexcept{
        m_dirinfo = readdir(m_dir);
        return *this;
    }

    File Directory::iterator::operator*() const noexcept{
        return File(m_path/Path(m_dirinfo->d_name));
    }

    bool Directory::iterator::operator==(const Directory::iterator &rhs) const noexcept{
        return m_dirinfo == nullptr;
    }

    bool Directory::iterator::operator!=(const Directory::iterator &rhs) const noexcept{
        return m_dirinfo != nullptr;
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
        return iterator(nullptr,m_file.path());
    }

}
