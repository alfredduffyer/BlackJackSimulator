# 
# Compiler shell script
# 
# @param	n	Don't execute, just compile the sources
# @param	x	Don't compile, just execute the old binary file
# @param	v	Launch the program with Valgrind
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
if ! [ "$1" = "x" ]; then
	if [ -f BlackJackSimulator ]; then
		rm BlackJackSimulator
	fi
	g++ -Wall -Wextra -std=gnu++0x -o BlackJackSimulator src/*.cpp
fi

# When there was an error, print the end-of-program line and exit
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
if ! [ "$1" = "n" ]; then
	if [ "$1" = "v" ]; then
#		valgrind ./BlackJackSimulator 17 2 -1 200 -1 100
		valgrind ./BlackJackSimulator -1
	else
#		./BlackJackSimulator 17 2 1 200 -1 10000000
		./BlackJackSimulator 1
	fi
fi

# Print the end-of-program line
echo ""
printf '\033[1;31;40m'
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
printf '\033[0m'

