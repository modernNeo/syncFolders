ls -l ~/Dropbox/Apps/Papyrus\ App/Nexus\ 9/PDFs/1MACM\ 316/ > macmDropFileList.txt

./fileName.awk macmDropFileList.txt macmDBFileNames.txt

ls -l ~/Google Drive/School/Current Classes/1MACM 316/Lecture Notes/ > macmGoogleFiles.txt

./fileName.awk macmGoogleFiles.txt macmGoogleFileNames.txt

now="$(date +%y-%m-%d-%T)"
printf "last date & time file sync: %s\n" "$now" >> logs/"$now"
printf "Files Synced:\n" >> logs/"$now"

./compare macmGoogleFileNames.txt macmDBFileNames.txt syncMacm.txt
if [ $? == 0 ]; then

	cat syncMacm.txt | while read line
	do
		printf "MACM 201/$line\n" >> logs/"$now"
		cp ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/1MACM 316/$line" ~/Google Drive/School/Current Classes/1MACM 316/Lecture Notes/
		rm ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/1MACM 316/$line"
	done
fi

rm cmptDropFileList.txt macmDropFileList.txt macmDBFileNames.txt cmptDBFileNames.txt macmGoogleFiles.txt cmptGoogleFiles.txt macmGoogleFileNames.txt cmptGoogleFileNames.txt syncMacm.txt syncCmpt.txt nohup.out