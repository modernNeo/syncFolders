#include "folder.h"

#include <filesystem>
namespace fs = std::filesystem;

Folder::Folder(string theFolder) {
   folderPath = theFolder;
   for (const auto & entry : fs::directory_iterator(folderPath)){
       files.push_back(File{entry.path()});
   }
}

int Folder::getSize(){
    return files.size();
}

string Folder::getFolderPath(){
    return folderPath;
}

bool Folder::fileDoesNotExist(string fileNameToCheck){
    for (int i = 0; i < files.size(); i++){
        if (files.at(i).getFileName() == fileNameToCheck){
            return false;
        }
    }
    return true;
}

File* Folder::getFile(string fileName){
    for (int i = 0; i < files.size(); i++){
        if (files.at(i).getFileName() == fileName){
            return &files.at(i);
        }
    }
    return NULL;
}
