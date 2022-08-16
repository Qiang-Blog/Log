out:test.o LogStream.o Logging.o LogFile.o FileUtil.o AsyncLogging.o
	g++ -o out test.o LogStream.o Logging.o LogFile.o FileUtil.o AsyncLogging.o -g -pthread -lmysqlclient -lcrypto
test.o:test.cpp
	g++ -c -o test.o test.cpp
LogStream.o:LogStream.cc
	g++ -c -o LogStream.o LogStream.cc
Logging.o:Logging.cc
	g++ -c -o Logging.o Logging.cc -pthread
LogFile.o:LogFile.cc
	g++ -c -o LogFile.o LogFile.cc
FileUtil.o:FileUtil.cc
	g++ -c -o FileUtil.o FileUtil.cc
AsyncLogging.o:AsyncLogging.cc
	g++ -c -o AsyncLogging.o AsyncLogging.cc
clean:
	rm *.o
