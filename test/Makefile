all:
	@make -C ..
	c++ -o tests tests.cpp LagATest.cpp -L.. -I../include -llam -mavx -mavx2
clean:
	@rm -rf tests
