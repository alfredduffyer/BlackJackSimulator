rm headers/*~
rm output/*~
rm resources/*~
rm src/*~
rm *~

if ! [ "$1" = "x" ]; then
if [ -f BlackJackSimulator ]; then
rm BlackJackSimulator
fi
fi

clear

if ! [ "$1" = "x" ]; then
g++ -Wall -Wextra -o BlackJackSimulator src/*.cpp
fi

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


