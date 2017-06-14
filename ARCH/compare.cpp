//
//  main.cpp
//  compare
//
//  Created by Jason Manshad on 2017-05-23.
//  Copyright © 2017 Jason Manshadi. All rights reserved.
//

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>
using std::endl;
using std::string;
using std::cerr;
using std::cout;
#include <sstream>

//1   2   :   5   6
//4   3   2   1   0

void convertTime( int& time, string& timeStr){
	//cout<<"time: "<<time<<endl;
	//cout<<"timeStr: "<<timeStr<<endl;
	//cout<<.1<<endl;
	time=0;
	//cout<<.2<<endl;
	int mult=1000;
	//cout<<.3<<endl;
	//std:://cout<<"time: "<<timeStr<<"\n";
	for (int i = 0 ; i < timeStr.length() ; i++){
		//cout<<.4<<endl;
		const char * timeChar=timeStr.c_str();
		//cout<<1<<endl;
		if (timeChar[4- (4-i) ] != ':'){
			//cout<<.5<<endl;
			int numb= ( (int)timeChar[4- (4-i) ] -48 )* mult;
			//cout<<.6<<endl;
			time+=numb;
			//cout<<.7<<endl;
			mult/=10;
			//std:://cout<<"i: "<<i<<"\ttimeChar[4-i]:"<<timeChar[4- (4-i) ]<<"\tnumb:"<<numb<<endl;
		}
	}
	//std:://cout<<"time\t\t"<<time<<"\t\t"<<timeStr<<endl;
	
}

void newFilesInDropbox(ifstream & DropBoxFin, ofstream & fout, string googleFile, ifstream & googleFin){
	//cout<<"..1"<<endl;
	string  dropboxFileNames;
	//cout<<"..2"<<endl;
	while (! DropBoxFin.eof() ){//checks for any files that are in DropBox but don't exist in Google Drive
		//cout<<"..3"<<endl;
		string garbage;
		//cout<<"..4"<<endl;
		getline(DropBoxFin,dropboxFileNames);
		//cout<<"..5"<<endl;
		getline(DropBoxFin, garbage);
		//cout<<"..6"<<endl;
		fout<<dropboxFileNames<<endl;
	}
	cerr<<"There are no files in the Google Drive folder so all files in Dropbox are being imported over"<<googleFile<<endl;
	//cout<<"..7"<<endl;
	googleFin.close();
	//cout<<"..8"<<endl;
	DropBoxFin.close();
}

void newFilesInDropBoxwithCrossCheck(ifstream & DropBoxFin, ifstream & googleFin, ofstream & fout){
	//cout<<"....1"<<endl;
	string googleFileNames, googleTimeStr, dropboxFileNames, dropboxTimeStr;
	//cout<<"....2"<<endl;
	int googleMonth, googleDay, dropboxMonth, dropboxDay;
	//cout<<"....3"<<endl;
	while (! DropBoxFin.eof() ){//checks for any files that are in DropBox but don't exist in Google Drive
		//cout<<"....4"<<endl;
		string garbage;
		//cout<<"....5"<<endl;
		getline(DropBoxFin,dropboxFileNames);
		//cout<<"....6"<<endl;
		DropBoxFin>>dropboxMonth>>dropboxDay>>dropboxTimeStr;
		//cout<<"....7"<<endl;
		getline(DropBoxFin, garbage);
		//cout<<"....8"<<endl;
		bool fileNameMatched=false;
		//cout<<"....9"<<endl;
		while (! googleFin.eof() ) {
			//cout<<"....10"<<endl;
			getline(googleFin, googleFileNames);
			//cout<<"....11"<<endl;
			googleFin>>googleMonth>>googleDay>>googleTimeStr;
			//cout<<"....12"<<endl;
			getline(googleFin, garbage);
			//cout<<"....13"<<endl;
			if (googleFileNames == dropboxFileNames){
				//cout<<"....14"<<endl;
				////cout<<googleFileNames<<" matched"<<endl;
				//cout<<"....15"<<endl;
				fileNameMatched=true;
				//cout<<"....16"<<endl;
			}
		}
		//cout<<"....17"<<endl;
		if (fileNameMatched==false){
			//cout<<"....18"<<endl;
			fout<<dropboxFileNames<<endl;
			//cout<<"....19"<<endl;
		}
		//cout<<"....20"<<endl;
		googleFin.clear();
		//cout<<"....21"<<endl;
		googleFin.seekg(0, std::ios::beg);
	}
}

void updatedExisitingFiles(ifstream & googleFin, ifstream & DropBoxFin, ofstream & fout){
	//cout<<"...1"<<endl;
	string googleFileNames, googleTimeStr, dropboxFileNames, dropboxTimeStr;
	//cout<<"...2"<<endl;
	int googleMonth, googleDay, googleTime, dropboxMonth, dropboxDay, dropboxTime;
	//cout<<"...3"<<endl;
	while (! googleFin.eof() ){//cross checks files that are in both DropBox and Google Drive to see if DropBox contains a more recent version
		//cout<<"...4"<<endl;
		string garbage;
		//cout<<"...5"<<endl;
		getline(googleFin, googleFileNames);
		//cout<<"...6"<<endl;
		googleFin>>googleMonth>>googleDay>>googleTimeStr;
		//cout<<googleMonth<<"\t"<<googleDay<<"\t"<<googleTimeStr<<endl;
		//cout<<"...7"<<endl;
		getline(googleFin, garbage);
		//cout<<"...8"<<endl;
		if (googleFileNames.length() > 0){
			//cout<<"...9"<<endl;
			//out<<"google file name: "<<googleFileNames<<endl;
			//out<<"googleMonth: "<<googleMonth<<"\tgoogleDay:"<<googleDay<<"\tgoogleTime:"<<googleTimeStr<<endl;
			while (! DropBoxFin.eof()) {
				//cout<<"...10"<<endl;
				getline(DropBoxFin, dropboxFileNames);
				//cout<<"...11"<<endl;
				DropBoxFin>>dropboxMonth>>dropboxDay>>dropboxTimeStr;
				//cout<<dropboxMonth<<"\t"<<dropboxDay<<"\t"<<dropboxTimeStr<<endl;
				//cout<<"...12"<<endl;
				//out<<"dropbox file name: "<<dropboxFileNames<<endl;
				//out<<"dropBoxMonth: "<<dropboxMonth<<"\tdropBoxDay:"<<dropboxDay<<"\tdropBoxTime:"<<dropboxTimeStr<<endl;
				getline(DropBoxFin, garbage);
				//cout<<"...13"<<endl;
				convertTime(googleTime, googleTimeStr);
				//cout<<"...14"<<endl;
				convertTime(dropboxTime, dropboxTimeStr);
				//cout<<"...15"<<endl;
				if (googleFileNames == dropboxFileNames){
					//cout<<"...16"<<endl;
					if (googleMonth == dropboxMonth && googleDay == dropboxDay && googleTime < dropboxTime){
						//cout<<"...17"<<endl;
						fout<<googleFileNames<<endl;
					}else if (googleMonth == dropboxMonth && googleDay < dropboxDay){
						//cout<<"...18"<<endl;
						fout<<googleFileNames<<endl;
					}else if (googleMonth < dropboxMonth){
						//cout<<"...19"<<endl;
						fout<<googleFileNames<<endl;
					}
				}
			}
		}
		DropBoxFin.clear();
		DropBoxFin.seekg(0, std::ios::beg);
	}
}

int main(int argc, const char * argv[]) {
	if (argc > 1){
	//cout<<1<<endl;
	//string googleFile = "macmGoogleFileNames.txt";
	string googleFile = argv[1];
	//cout<<2<<endl;
	//string dropBoxFile = "macmDBFileNames.txt";
	string dropBoxFile = argv[2];
	//cout<<3<<endl;
	//string outFileName=  "syncMacm.txt";
	string outFileName=  argv[3];
	//cout<<4<<endl;
	//string output = "output.txt";
	//cout<<5<<endl;
	ifstream googleFin,DropBoxFin;
	//cout<<6<<endl;
	string googleFileNames, googleTimeStr, dropboxFileNames, dropboxTimeStr;
	//cout<<7<<endl;
	
	ofstream fout;
	//cout<<8<<endl;
	fout.open(outFileName);
	//cout<<9<<endl;
	if (fout.fail())//check if correct name
	{
		//cout<<10<<endl;
		fout<<"Error opening output file name"<<endl;
		fout.close();
		exit(1);
	}
	
	DropBoxFin.open(dropBoxFile.c_str());
	//cout<<11<<endl;
	if (DropBoxFin.fail()){//check if correct name
		//cout<<12<<endl;
		cerr<<"No files in DropBox folder or Wrong DropBox Name for:"<<dropBoxFile<<endl;
		googleFin.close();
		DropBoxFin.close();
		return 1;
	}
	googleFin.open(googleFile.c_str());
	//cout<<13<<endl;
	if (googleFin.fail()){//check if correct name
		//cout<<14<<endl;
		newFilesInDropbox(DropBoxFin,fout, googleFile, googleFin);
		return 0;
	}
	//cout<<15<<endl;
	
	updatedExisitingFiles(googleFin, DropBoxFin, fout);
	//cout<<16<<endl;
	
	googleFin.clear();
	//cout<<17<<endl;
	googleFin.seekg(0, std::ios::beg);
	//cout<<18<<endl;
	
	//
	newFilesInDropBoxwithCrossCheck(DropBoxFin, googleFin, fout);
	//cout<<19<<endl;
	//
	
	googleFin.close();
	DropBoxFin.close();
	// insert code here...
	//}
	}
	return 0;
}
