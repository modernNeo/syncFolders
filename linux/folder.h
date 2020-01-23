
#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <iostream>
using std::string;

#include <vector>
using std::vector;

#include "file.h"

class Folder {
    private:
        string folderPath;

    public:
        std::vector< File > files;
        Folder(string theFolder);
        int getSize();
        string getFolderPath();
        bool fileDoesNotExist(string fileNameToCheck);
        File* getFile(string fileName);

};

#endif
