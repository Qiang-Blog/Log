#pragma once

#include "LogStream.h"
#include "LogFile.h"
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <iostream>
#include "FixedBuffer.h"

class AsyncLogging{
private:
	void threadFunc();
	typedef FixedBuffer<kLargeBuffer> Buffer;
	typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
	typedef std::shared_ptr<Buffer> BufferPtr;
	const int flushInterval;
	bool running;
	std::string basename;
	std::thread *thread_;
	std::mutex mtx;
	std::condition_variable cond;
	BufferPtr currentBuffer;
	BufferPtr nextBuffer;
	BufferVector buffers;

public:
	AsyncLogging(const std::string logFileName,int FlushInterval=2);
	~AsyncLogging();
	void append(const char *logfile,int len);
	void start();
	void stop();	

};

typedef std::unique_ptr<AsyncLogging> UP_AsyncLogging;
