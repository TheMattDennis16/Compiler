'cxxflags=-Wall std=c++17'
input_file=test_input.a
output_file=output_file

build: 
	g++ -o compiler $(cxxflags) -I ./includes/ ./src/*.cpp main.cpp

tests:
	g++ -o test_runner std=c++17 -I /usr/local/include/ -I ./includes/ tests/*.cpp src/*.cpp -L~/boost/stage/lib -lboost_unit_test_framework

test:
	g++ -o single_test_runner -std=c++17 I /usr/local/include/ -I ./includes/ $(file) src/*.cpp -L~/boost/stage/lib -lboost_unit_test_framework

performance:
	g++ -o single_test_runner -std=c++17 I /usr/local/include/ -I ./includes/ $(file) src/*.cpp -L~/boost/stage/lib -lboost_unit_test_framework

asm:
	g++ -o compiler $(cxxflags) -I ./includes/ ./src/*.cpp main.cpp
	./compiler test_input.a -f $(output_file)
	objdump -d $(output_file) > $(output_file)_asm.asm

clean:
	rm -f compiler test_runner single_test_runner
