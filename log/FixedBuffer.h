#pragma once

#include <cstring>

const int kSmallBuffer=4000;
const int kLargeBuffer=4000*1024;

template<int SIZE>
class FixedBuffer{
private:
    const char* end()const;
    char data_[SIZE];
    char* cur;

public:
    FixedBuffer():	cur(data_){}
    ~FixedBuffer(){}
    void append(const char *buf,int len){  //往缓冲区中添加消息
		if(avail()>len){
			memcpy(cur,buf,len);
			cur+=len;
		}
	}
    const char* data()const{return data_;}
    int length()const{return cur-data_;} // 当前缓冲区长度
    char* current(){return cur;} // 当前位置
    int avail()const{return data_+SIZE-cur;} // 当前可用长度
    void add(int len){cur+=len;} // 往缓冲区中添加数据
    void reset(){cur=data_;} //重置
    void bzero(){memset(data_,0,SIZE);} //初始化
};
