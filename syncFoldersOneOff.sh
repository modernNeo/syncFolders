#phil part
ls -l ~/Dropbox/Apps/Papyrus\ App/Nexus\ 9/PDFs/1PHIL\ 105/ > philDropFileList.txt

./fileName.awk philDropFileList.txt philDBFileNames.txt

ls -l ~/Google\ Drive/School/Current\ Classes/1PHIL\ 105/Lecture\ Notes/ > philGoogleFiles.txt

./fileName.awk philGoogleFiles.txt philGoogleFileNames.txt


#cmpt 397 part
ls -l ~/Dropbox/Apps/Papyrus\ App/Nexus\ 9/PDFs/2CMPT\ 379/ > 379DropFileList.txt

./fileName.awk 379DropFileList.txt 379DBFileNames.txt

ls -l ~/Google\ Drive/School/Current\ Classes/2CMPT\ 379/Lecture\ Notes/ > 379GoogleFiles.txt

./fileName.awk 379GoogleFiles.txt 379GoogleFileNames.txt

#cmpt 307
ls -l ~/Dropbox/Apps/Papyrus\ App/Nexus\ 9/PDFs/3CMPT\ 307/ > 307DropFileList.txt

./fileName.awk 307DropFileList.txt 307DBFileNames.txt

ls -l ~/Google\ Drive/School/Current\ Classes/3CMPT\ 307/Lecture\ Notes/ > 307GoogleFiles.txt

./fileName.awk 307GoogleFiles.txt 307GoogleFileNames.txt


now="$(date +%y-%m-%d-%T)"
printf "last date & time file sync: %s\n" "$now" >> logs/"$now"
printf "Files Synced:\n" >> logs/"$now"

./compare philGoogleFileNames.txt philDBFileNames.txt syncPhil.txt
./compare 379GoogleFileNames.txt 379DBFileNames.txt sync379.txt
./compare 307GoogleFileNames.txt 307DBFileNames.txt sync307.txt
if [ $? == 0 ]; then

	cat syncPhil.txt | while read line
	do
		printf "PHIL 105/$line\n" >> logs/"$now"
		cp ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/1PHIL 105/$line" ~/Google\ Drive/School/Current\ Classes/1PHIL\ 105/Lecture\ Notes/
		rm ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/1PHIL 105/$line"
	done

	cat sync379.txt | while read line
	do
		printf "CMPT 379/$line\n" >> logs/"$now"
		cp ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/2CMPT 379/$line" ~/Google\ Drive/School/Current\ Classes/2CMPT\ 379/Lecture\ Notes/
		rm ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/2CMPT 379/$line"
	done

	cat sync307.txt | while read line
	do
		printf "CMPT 307/$line\n" >> logs/"$now"
		cp ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/3CMPT 307/$line" ~/Google\ Drive/School/Current\ Classes/3CMPT\ 307/Lecture\ Notes/
		rm ~/"Dropbox/Apps/Papyrus App/Nexus 9/PDFs/3CMPT 307/$line"
	done
fi

rm philDropFileList.txt philDBFileNames.txt philGoogleFiles.txt philGoogleFileNames.txt 379DropFileList.txt 379DBFileNames.txt 379GoogleFiles.txt 379GoogleFileNames.txt 307DropFileList.txt 307DBFileNames.txt 307GoogleFiles.txt 307GoogleFileNames.txt syncPhil.txt sync379.txt sync307.txt nohup.out
