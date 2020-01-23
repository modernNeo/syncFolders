#include "file.h"

#include <sys/stat.h>

File::File(string theFilePath){
    struct stat buf;
    stat(theFilePath.c_str(), &buf);
    filePath = theFilePath;
    ftime = buf.st_mtime;
    name = theFilePath.substr(theFilePath.find_last_of("/")+1);
}

bool operator>(const File & left, const File & right){
    return left.ftime > right.ftime;
}

string File::getFilePath(){
    return filePath;
}

string File::getFileName(){
    return name;
}

std::time_t File::getTime(){
    return ftime;
}
