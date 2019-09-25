#include "FilePosix.h"

#include <utility>

namespace maievertias{

    File::GetInfoError::GetInfoError(int err)
        :m_err(err){}

    File::GetInfoError::~GetInfoError() = default;

    const char *File::GetInfoError::what() const noexcept{
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

    File::File(Path path)
        :m_stated(false),
         m_stat{},
         m_path(std::move(path)){}

    File::~File() = default;

    const Path &File::path() const noexcept{
        return m_path;
    }

    bool File::isRegularFile(){
        if(!m_stated){
            //ensure the file exist outside
            if(stat(m_path.c_str(),&m_stat)!=0){
                throw GetInfoError(errno);
            }
            m_stated = true;
        }
        return S_ISREG(m_stat.st_mode);
    }

    bool File::isDirectory(){
        return false;
    }

    bool File::isFIFO(){
        return false;
    }

    bool File::isBlockFile(){
        return false;
    }

    bool File::isCharacterFile(){
        return false;
    }

    bool File::isSocket(){
        return false;
    }

    bool File::isSymlink(){
        return false;
    }

    bool File::isOther(){
        return false;
    }

    bool File::exist() const noexcept{
        return access(m_path.c_str(),F_OK) == 0;
    }

    File::operator bool() const noexcept{
        return exist();
    }
}