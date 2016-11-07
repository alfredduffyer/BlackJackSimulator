# 
# Compiler shell script
# 
# @param:1	1/-1	Start with 1 or -1
# @param:2	n	Don't execute, just compile the sources
# @param:2	x	Don't compile, just execute the old binary file
# @param:2	v	Launch the program with Valgrind
# 

# Clean directories from temp files
rm headers/*~
rm output/*~
rm resources/*~
rm src/*~
rm *~

# Clear the screen
clear

# Compiles the sources (after removing the old binary file)
if ! [ "$2" = "x" ]; then
	if [ -f BlackJackSimulator ]; then
		rm BlackJackSimulator
	fi
	g++ -Wall -Wextra -std=gnu++0x -o BlackJackSimulator src/*.cpp
fi

# If there's an error, print the end-of-program line and exit
if ! [ -f BlackJackSimulator ]; then
	printf '\033[1;31;40m'
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	printf '\033[0m'
	exit
fi

# If the compiling went well, print the begining-of-program line
printf '\033[1;34;40m'
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
printf '\033[0m'

# Launches the compiled program
if ! [ "$2" = "n" ]; then
	if [ "$2" = "v" ]; then
#		valgrind ./BlackJackSimulator 17 2 -1 200 -1 100
		valgrind ./BlackJackSimulator $1 D
	else
#		./BlackJackSimulator 17 2 1 200 -1 10000000
		./BlackJackSimulator $1 D
	fi
fi

# Print the end-of-program line
echo ""
printf '\033[1;31;40m'
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
printf '\033[0m'

