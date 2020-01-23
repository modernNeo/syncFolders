#include "file.h"

#include <filesystem>
namespace fs = std::filesystem;

File::File(string theFilePath){
    filePath = theFilePath;
    ftime = system_clock::to_time_t(fs::last_write_time(theFilePath));
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
