rm src/*~
rm headers/*~
rm *~

if [ -f BlackJackSimulator ]; then
rm BlackJackSimulator
fi

clear

g++ -Wall -Wextra -o BlackJackSimulator src/*.cpp

if ! [ -f BlackJackSimulator ]; then
printf '\033[1;31;40m'
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
printf '\033[0m'
exit
fi

printf '\033[1;34;40m'
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
printf '\033[0m'

if [ "$1" = "v" ]; then
valgrind ./BlackJackSimulator
else
./BlackJackSimulator
fi


echo ""

printf '\033[1;31;40m'
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
printf '\033[0m'


