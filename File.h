#ifndef MAIEVERTIAS_FILE_H
#define MAIEVERTIAS_FILE_H

#if  defined(__GUNC__) || defined(__MINGW32__)
#include "FilePosix.h"
#endif

#if defined(_MSVC_VER)
#include "FileWindows.h"
#endif

#endif //MAIEVERTIAS_FILE_H
