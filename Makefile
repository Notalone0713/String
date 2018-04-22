test:String.cpp test.cpp
	g++ -o $@ $^  -std=c++11  -fno-elide-constructors

.PHONY:clean
clean:
	rm test
