#!/bin/bash

COMPARE=0

while [ $COMPARE == 0 ]
do
	ls -l ~/Dropbox/Apps/Papyrus\ App/Nexus\ 9/PDFs/1MACM\ 201/ > macmDropFileList.txt
	ls -l ~/Dropbox/Apps/Papyrus\ App/Nexus\ 9/PDFs/2CMPT\ 276/ > cmptDropFileList.txt

	./fileName.awk macmDropFileList.txt macmDBFileNames.txt
	./fileName.awk cmptDropFileList.txt cmptDBFileNames.txt

	ls -l ~/Google\ Drive/School\ Files/Current\ Classes/1MACM\ 201/Lecture\ Notes/ > macmGoogleFiles.txt
	ls -l ~/Google\ Drive/School\ Files/Current\ Classes/2CMPT\ 276/Lecture\ Notes/ > cmptGoogleFiles.txt

	./fileName.awk macmGoogleFiles.txt macmGoogleFileNames.txt
	./fileName.awk cmptGoogleFiles.txt cmptGoogleFileNames.txt

	./compare macmGoogleFileNames.txt macmDBFileNames.txt syncMacm.txt
	./compare cmptGoogleFileNames.txt cmptDBFileNames.txt syncCmpt.txt

	now="$(date +%y-%m-%d-%T)"
	printf "last date & time file sync: %s\n" "$now" >> logs/"$now"
	printf "Files Synced:\n" >> logs/"$now"
	
	cat syncMacm.txt | while read line
	do
		printf "MACM 201/$line\n" >> logs/"$now"
		cp ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/1MACM 201/$line" ~/Google\ Drive/School\ Files/Current\ Classes/1MACM\ 201/Lecture\ Notes/
		rm ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/1MACM 201/$line"
	done

	cat syncCmpt.txt | while read line
	do
		printf "CMPT 276/$line\n" >> logs/"$now"
		cp ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/2CMPT 276/$line" ~/Google\ Drive/School\ Files/Current\ Classes/2CMPT\ 276/Lecture\ Notes/
		rm ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/2CMPT 276/$line"
	done
	rm cmptDropFileList.txt macmDropFileList.txt macmDBFileNames.txt cmptDBFileNames.txt macmGoogleFiles.txt cmptGoogleFiles.txt macmGoogleFileNames.txt cmptGoogleFileNames.txt syncMacm.txt syncCmpt.txt nohup.out
sleep 3600
done