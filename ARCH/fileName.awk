#!/usr/bin/awk -f
BEGIN {
	out_file = ARGV[2];
	ARGV[2]="";
	theName="";
}
NF > 8{
	num_of_recs=NF;
	while (num_of_recs >= 9){
		theName=$num_of_recs" "theName;
		num_of_recs--;
	}
	#$6 = month
	#$7 = day
	#$8 = time
	if ($6 == "Jan"){
		$6="1"
	}else if ($6 == "Feb"){
		$6="2"
	}else if ($6 == "Mar"){
		$6="3"
	}else if ($6 == "May"){
		$6="5"
	}else if ($6 == "Jun"){
		$6="6"
	}else if ($6 == "Jul"){
		$6="7"
	}else if ($6 == "Aug"){
		$6="8"
	}else if ($6 == "Sep"){
		$6="9"
	}else if ($6 == "Oct"){
		$6="10"
	}else if ($6 == "Nov"){
		$6="11"
	}else if ($6 == "Dec"){
		$6="12"
	}
	print theName"\n"$7" "$6" "$8 >out_file;
	theName="";
}