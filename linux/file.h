
#ifndef _FILE_H_
#define _FILE_H_

#include <chrono>
using std::chrono::system_clock;

#include <iostream>
using std::string;

class File {
    private:
        std::time_t ftime;
        string name;
        string filePath;

    public:
        File(string theFilePath);
        friend bool operator>(const File & left, const File & right);
        string getFilePath();
        string getFileName();
        std::time_t getTime();
};

#endif
