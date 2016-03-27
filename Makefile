###################################################################
#  Jason Stumbaugh
#  CSE 7343 Operating Systems
#  Makefile
###################################################################

# makefile targets
all : main.exe

main.exe : main.cpp PCB.cpp queue.cpp scheduler.cpp
		g++ main.cpp -std=c++11 -o main.exe
		./main.exe

clean :
		\rm -f *.exe *~

####### End of Makefile #######
