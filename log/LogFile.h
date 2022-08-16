#pragma once


#include "FileUtil.h"
#include <iostream>
#include <mutex>

class LogFile{
private:
	void append_unlocked(const char *logline,int len);
	const std::string basename;
	const int flushEveryN;
	int count; 
	std::mutex mtx;
	UP_FileUtil file;  // ????

public:
	LogFile(const std::string &Basename,int FlushEveryN=1024);
	~LogFile();
	void append(const char *logline,int len);
	void flush();
	bool rollFile();
};
