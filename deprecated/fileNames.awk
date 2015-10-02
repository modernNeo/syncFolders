#!/usr/bin/awk -f
BEGIN {
	out_file = ARGV[2];
	ARGV[2]="";
	theName="";
}
{
	num_of_recs=1;
	theName=$num_of_recs;
	num_of_recs++;
	while (num_of_recs < NF){
		theName=theName" "$num_of_recs;
		num_of_recs++;
	}
	print theName >out_file;
	theName="";
}