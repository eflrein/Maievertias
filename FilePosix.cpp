#include "FilePosix.h"

namespace maievertias{

    const Path &File::path() const noexcept{
        return m_path;
    }

    Path &File::path() noexcept{
        return m_path;
    }
}