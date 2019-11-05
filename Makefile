all:
	g++ --std=c++11 main.cpp -lncursesw

clean:
	rm -rf ./a.out
