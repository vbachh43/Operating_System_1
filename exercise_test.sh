set -f
ANS_exist=false
#create history file
if [ ! -f ex_his.txt ]; then
	touch ex_his.txt
fi

#create ANS
if [ ! -f ANS ]; then
	echo 0 > ANS
fi

#History func
HIST(){
tail -n 5 ex_his.txt
}

while true; do
read -p ">> " input
if [[ $input == "HIST" ]]; then
	HIST
	continue
elif [[ $input == "EXIT" ]]; then
	exit 0
else
operand1=${operand1/ANS/$(cat ANS)}
operand2=${operand2/ANS/$(cat ANS)}

operand1=$(echo $input | cut -d' ' -f1)
operator=$(echo $input | cut -d' ' -f2)
operand2=$(echo $input | cut -d' ' -f3)

if [[ $operand1 == "ANS" ]]; then
	ANS_exist=true
	operand1=$ANS
fi

case $operator in
"+")
	((res=operand1+operand2 | bc))
	echo "$res"
	;;
"-")
	((res=operand1-operand2 | bc))
	echo "$res"
	;;
"*")
	((res=operand1*operand2 | bc))
	echo "$res"
	;;
"/")
	if [ $operand2 -eq 0 ]; then
		echo "MATH ERROR"
	else
		res=$(echo "scale=2; $operand1 / $operand2" | bc)
		if [[ $res == *".00" ]]; then
			res=${res%%".00"}
		fi
	echo "$res"
	fi
	;;
"%")
	if [ $operand2 -eq 0 ]; then
		echo "MATH ERROR"
	else
		res=$(( operand1/operand2 ))
		echo "$res"
	fi
	;;
*)
	echo "SYNTAX ERROR"
	continue
	;;
esac

ANS=$res

if [[ "$ANS_exist" = true ]]; then
	ANS_exist=false
	echo "ANS $operator $operand2 = $res" >> ex_his.txt
else
	echo "$operand1 $operator $operand2 = $res" >> ex_his.txt
fi

fi
done
