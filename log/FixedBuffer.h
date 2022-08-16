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
    void append(const char *buf,int len){  //���������������Ϣ
		if(avail()>len){
			memcpy(cur,buf,len);
			cur+=len;
		}
	}
    const char* data()const{return data_;}
    int length()const{return cur-data_;} // ��ǰ����������
    char* current(){return cur;} // ��ǰλ��
    int avail()const{return data_+SIZE-cur;} // ��ǰ���ó���
    void add(int len){cur+=len;} // �����������������
    void reset(){cur=data_;} //����
    void bzero(){memset(data_,0,SIZE);} //��ʼ��
};
