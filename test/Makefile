all:
	@make -C ..
	c++ -g -o tests tests.cpp LagATest.cpp -L.. -I../include -llam -mavx -mavx2
clean:
	@rm -rf tests output.log

run:
	@make -C ..
	@c++ -g -o tests tests.cpp LagATest.cpp -L.. -I../include -llam -mavx -mavx2
	@./tests > output.log
