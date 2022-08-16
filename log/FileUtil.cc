#include "FileUtil.h"

FileUtil::FileUtil(std::string filename)
:	fp(fopen(filename.c_str(),"ae"))
{
	setbuffer(fp,buffer,sizeof(buffer));
}

// �ر��ļ�
FileUtil::~FileUtil(){
	fclose(fp);
}

// ���ļ���д��
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


// ˢ�»�����
void FileUtil::flush(){
	fflush(fp);
}

// ���ļ���д��
int FileUtil::write(const char *logline,int len){
	return fwrite_unlocked(logline,1,len,fp);
}
