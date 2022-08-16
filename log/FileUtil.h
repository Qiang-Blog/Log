#pragma once

#include <fstream>
#include <memory>

#define BUFFERSIZE 64*1024

class FileUtil{
private:
	int write(const char *logline,int len);
	FILE *fp;
	char buffer[BUFFERSIZE];	
	
public:
	explicit FileUtil(std::string filename);
	~FileUtil();
	void append(const char *logline,int len);
	void flush();
};

typedef std::unique_ptr<FileUtil> UP_FileUtil;
