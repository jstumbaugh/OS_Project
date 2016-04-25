###################################################################
#  Jason Stumbaugh
#  CSE 7343 Operating Systems
#  Makefile
###################################################################

# makefile targets
all : os.exe

os.exe : main.cpp PCB.cpp queue.cpp scheduler.cpp
		g++ main.cpp -std=c++11 -o os.exe
		./os.exe

clean :
		\rm -f *.exe *~

####### End of Makefile #######
