#include "FileUtil.h"

FileUtil::FileUtil(std::string filename)
:	fp(fopen(filename.c_str(),"ae"))
{
	setbuffer(fp,buffer,sizeof(buffer));
}

// 关闭文件
FileUtil::~FileUtil(){
	fclose(fp);
}

// 往文件中写入
void FileUtil::append(const char *logline,int len){
	while(len){
		size_t x=this->write(logline,len);
		if(!x){
			if(ferror(fp))
				perror("FileUtil::append() failed!");
			break;
		}
		logline+=x;
		len-=x;
	}
}


// 刷新缓冲区
void FileUtil::flush(){
	fflush(fp);
}

// 往文件中写入
int FileUtil::write(const char *logline,int len){
	return fwrite_unlocked(logline,1,len,fp);
}
