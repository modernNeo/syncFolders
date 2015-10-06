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
	#$7 = month
	#$6 = day
	#$8 = time
	if ($7 == "May"){
		$7="5"
	}else if ($7 == "Jun"){
		$7="6"
	}else if ($7 == "Jul"){
		$7="7"
	}else if ($7 == "Aug"){
		$7="8"
	}else if ($7 == "Sep"){
		$7="9"
	}else if ($7 == "Oct"){
		$7="10"
	}
	print theName"\n"$7" "$6" "$8 >out_file;
	theName="";
}