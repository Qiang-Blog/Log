#include "Logging.h"

static pthread_once_t once_control=PTHREAD_ONCE_INIT;

std::string Logger::logFileName="/ServerLog";

UP_AsyncLogging& getAsyncLogging(){
	static UP_AsyncLogging AsyncLogger(new AsyncLogging(Logger::getLogFileName()));
	return AsyncLogger;
}

void init(){
	Logger::logFileName="ServerLog";
	getAsyncLogging()->start();
}

void output(const char *msg,int len){
	pthread_once(&once_control,init);
	getAsyncLogging()->append(msg,len);
}

Impl::Impl(const char *fileName,int line)
:	line(line),
	basename(fileName)
{
	formatTime();
}

void Impl::formatTime(){
	struct timeval tv;
	time_t time;
	char str_t[26]={0};
	gettimeofday(&tv,NULL);
	time=tv.tv_sec;
	struct tm* p_time=localtime(&time);
	strftime(str_t,26,"%Y-%m-%d %H:%M:%S\n",p_time);
	stream_<<str_t;
}

int Impl::getLine(){
	return line;
}

LogStream& Impl::stream(){
	return stream_;
}

std::string Impl::getBaseName(){
	return basename;
}

Logger::Logger(const char *fileName,int line)
:	impl(fileName,line)
{
}

Logger::~Logger(){
	stream()<<" -- "<<impl.getBaseName()<<':'<<impl.getLine()<<'\n';
	const LogStream::Buffer& buf(impl.stream().buffer());
	// std::cout << "doing ??? " << std::endl;
	output(buf.data(),buf.length());
}


/*void Logger::setLogFileName(std::string fileName){
	logFileName=fileName;
}*/

std::string Logger::getLogFileName(){
	return logFileName;
}

LogStream& Logger::stream(){
	return impl.stream();
}
