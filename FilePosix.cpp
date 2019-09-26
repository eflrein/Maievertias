#include "FilePosix.h"

#include <utility>

namespace maievertias{

    ///FileError
    File::FileError::FileError(int err)
        :m_err(err){}

    File::FileError::~FileError() = default;

    const char *File::FileError::what() const noexcept{
        switch(m_err){
            case ENOENT:
                return "No such file or directory";
            case EIO:
                return "I/O error";
            case ENXIO:
                return "No such device or address";
            case EAGAIN:
                return "Try again";
            case ENOMEM:
                return "Out of memory";
            case EACCES:
                return "Permission denied";
            case EFAULT:
                return "Bad address";
            case EEXIST:
                return "File exists";
            case ENODEV:
                return "No such device";
            case ENOTDIR:
                return "Not a directory";
            case EISDIR:
                return "Is a directory";
            case EINVAL:
                return "Invalid argument";
            case ENFILE:
                return "File table overflow ";
            case EMFILE:
                return "Too many open files";
            case EFBIG:
                return "File too large";
            case EROFS:
                return "Read-only file system";
            case EMLINK:
                return "Too many links";
            case ENOTEMPTY:
                return "Directory not empty";
            case ELOOP:
                return "Too many symbolic links encountered";
            default:
                return "unknown error";

        }
    }

    ///File
    File::File(Path path)
        :m_stated(false),
         m_stat{},
         m_path(std::move(path)){}

    File::~File() = default;

    const Path &File::path() const noexcept{
        return m_path;
    }

    bool File::isRegularFile()const{
        if(!m_stated){
            if(stat(m_path.c_str(),&m_stat)!=0){
                throw FileError(errno);
            }
            m_stated = true;
        }
        return S_ISREG(m_stat.st_mode);
    }

    bool File::isDirectory()const{
        if(!m_stated){
            if(stat(m_path.c_str(),&m_stat)!=0){
                throw FileError(errno);
            }
            m_stated = true;
        }
        return S_ISDIR(m_stat.st_mode);
    }

    bool File::isFIFO()const{
        if(!m_stated){
            if(stat(m_path.c_str(),&m_stat)!=0){
                throw FileError(errno);
            }
            m_stated = true;
        }
        return S_ISFIFO(m_stat.st_mode);
    }

    bool File::isBlockFile()const{
        if(!m_stated){
            if(stat(m_path.c_str(),&m_stat)!=0){
                throw FileError(errno);
            }
            m_stated = true;
        }
        return S_ISBLK(m_stat.st_mode);
    }

    bool File::isCharacterFile()const{
        if(!m_stated){
            if(stat(m_path.c_str(),&m_stat)!=0){
                throw FileError(errno);
            }
            m_stated = true;
        }
        return S_ISCHR(m_stat.st_mode);
    }



    bool File::exist() const noexcept{
        return access(m_path.c_str(),F_OK) == 0;
    }

    File::operator bool() const noexcept{
        return exist();
    }

    std::uint32_t File::size()const{
        if(!m_stated){
            if(stat(m_path.c_str(),&m_stat)!=0){
                throw FileError(errno);
            }
            m_stated = true;
        }
        return m_stat.st_size;
    }

}
