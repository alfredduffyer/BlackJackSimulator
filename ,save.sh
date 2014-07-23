rm *~

clear

ns=`date --rfc-3339='ns'`
day=${ns:0:10}
hh=${ns:11:2}
ii=${ns:14:2}
ss=${ns:17:2}

zip ""$day"_"$hh"-"$ii"-"$ss".zip" *
mv ""$day"_"$hh"-"$ii"-"$ss".zip" ../backup/

echo "Created "$day"_"$hh"-"$ii"-"$ss".zip and moved to backup."
