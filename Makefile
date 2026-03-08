run:
	g++ -Wall -Wextra -pedantic -march=native -O3 -std=c++20 -Iinclude main.cpp src/resources.cpp src/scheduler.cpp -o memsched && ./memsched
build:
	g++ -Wall -Wextra -pedantic -march=native -O3 -std=c++20 -Iinclude main.cpp src/resources.cpp src/scheduler.cpp -o memsched
