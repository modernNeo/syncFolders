#include <iostream>
using std::string;

#include <vector>
using std::vector;

#include <filesystem>
namespace fs = std::filesystem;

#include "file.h"
#include "folder.h"

#include <fstream>
using std::ofstream;

void moveNewFileToGoogle(ofstream & fout, Folder & googleFolder, Folder & dropboxFolder);

int main(int argc, const char * argv[]){

	std::time_t endTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char currentTime[20];
    std::strftime(currentTime, sizeof(currentTime), "%Y-%m-%d-%H-%M-%S", std::localtime(&endTime));
    std::string currentTimeStr(currentTime);
	string fileName = currentTimeStr + ".log";

	ofstream fout;
	fout.open(fileName);

	if (argc == 3){
		Folder googleFolder(argv[1]);
		Folder dropboxFolder(argv[2]);
		fout<<"googleFolder :"<<googleFolder.getFolderPath()<<std::endl;
		fout<<"dropboxFolder :"<<dropboxFolder.getFolderPath()<<std::endl;
		moveNewFileToGoogle(fout, googleFolder, dropboxFolder);
	}else{
		fout<<"calling ./syncer <absolute_path_to_google_folder> <absolute_path_to_dropbox_folder>"<<std::endl;
	}
	fout.close();

}

void moveNewFileToGoogle(ofstream & fout, Folder & googleFolder, Folder & dropboxFolder){
	for (auto & dropBoxFile : dropboxFolder.files){
		fout<<"Processing Dropbox File: "<<dropBoxFile.getFileName()<<std::endl;
		if (googleFolder.fileDoesNotExist(dropBoxFile.getFileName())){
			fout<<"Dropbox Filename " << dropBoxFile.getFilePath() << std::endl;
			fout<<"Dropbox Timestamp " << dropBoxFile.getTime() << std::endl;
			fout<<"moving file "<< dropBoxFile.getFileName() <<" to " << googleFolder.getFolderPath() +  "/" + dropBoxFile.getFileName() <<std::endl<<std::endl;
			fs::rename(dropBoxFile.getFilePath(), googleFolder.getFolderPath() +  "/" + dropBoxFile.getFileName());
		}
		else{
			File googleFile = *(googleFolder.getFile(dropBoxFile.getFileName()));
			fout<<"Dropbox Filename " << dropBoxFile.getFilePath() << std::endl;
			fout<<"Dropbox Timestamp " << dropBoxFile.getTime() << std::endl;
			fout<<"Google Drive Filename " << googleFile.getFilePath() << std::endl;
			fout<<"Google Drive Timestamp " << googleFile.getTime() << std::endl;

			if (dropBoxFile > googleFile){
				fout<<"moving file "<< dropBoxFile.getFileName() << " to " << googleFile.getFileName() <<std::endl<<std::endl;
				fs::rename(dropBoxFile.getFilePath(), googleFolder.getFolderPath() +  "/" + dropBoxFile.getFileName());
			}else{
				fout<<"Google's version of "<<  dropBoxFile.getFileName() << " is either the same or newer than Dropboxes" <<std::endl<<std::endl;

			}
		}
	}
}
