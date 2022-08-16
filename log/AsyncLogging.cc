#include "AsyncLogging.h"

// logFilename输出日志名字、
AsyncLogging::AsyncLogging(const std::string logFileName,int FlushInterval)
:	flushInterval(FlushInterval),
	running(false),
	basename(logFileName),
	thread_(new std::thread(&AsyncLogging::threadFunc,this)),
	// cond(mutex),
	currentBuffer(new Buffer()),
	nextBuffer(new Buffer())
{
	// std::cout << "AsyncLogging construct" << std::endl;
}

AsyncLogging::~AsyncLogging(){
	if(running)
		stop();
}

// 将LogStream的内容写到了AsyncLogging缓冲区
void AsyncLogging::append(const char *logline,int len){
	std::lock_guard<std::mutex> locker(mtx);
	// 如果当前缓冲区剩余的大小足够写入当条日志，则写入
	if(currentBuffer->avail()>len)
		currentBuffer->append(logline,len);
	// 否则
	else{
		buffers.emplace_back(currentBuffer);
		// 如果第二个Buffer还有数据，则直接把第二个Buffer转移给当前Buffer
		if(nextBuffer)
			currentBuffer=std::move(nextBuffer);
		// 否则的话清空当前Buffer
		else
			currentBuffer.reset(new Buffer());
		currentBuffer->append(logline,len);
		cond.notify_one();
	}
}

void AsyncLogging::threadFunc(){
	BufferPtr newBuffer1(new Buffer());
	BufferPtr newBuffer2(new Buffer());
	BufferVector buffersToWrite;
	LogFile output(basename);
	while(running){
		{
			std::unique_lock<std::mutex> locker(mtx);
			if(buffers.empty())
				cond.wait_for(locker, std::chrono::milliseconds(flushInterval*1000));

			buffers.emplace_back(currentBuffer);
			currentBuffer=std::move(newBuffer1);
			buffersToWrite.swap(buffers);
			if(!nextBuffer)
				nextBuffer=std::move(newBuffer2);
		}
		for(auto &wi:buffersToWrite)
			output.append(wi->data(),wi->length());
		if(!newBuffer1)
			newBuffer1.reset(new Buffer());
		if(!newBuffer2)
			newBuffer2.reset(new Buffer());
		buffersToWrite.clear();
		output.flush();
	}
	output.flush();
}

void AsyncLogging::start(){
	running=true;
}

void AsyncLogging::stop(){
	running=false;
	cond.notify_one();
	thread_->join();
}
