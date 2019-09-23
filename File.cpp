#include "File.h"

#if  defined(__GUNC__) || defined(__MINGW32__)
#include "FilePosix.cpp"
#endif

#if defined(_MSVC_VER)
#include "FileWindows.cpp"
#endif
