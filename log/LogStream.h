#pragma once

#include "FixedBuffer.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <cstring>

class LogStream{
public:
	typedef FixedBuffer<kSmallBuffer> Buffer;  // 定义为Buffer类型
private:
	void staticCheck();
	template<typename T>
	void formatInteger(T);
	template<typename T>
	void formatDecimal(T);
	Buffer buffer_;
	static const int kMaxNumbericSize=32;

public:
	// 重载 << 输出
	LogStream& operator<<(bool);
	LogStream& operator<<(short);
	LogStream& operator<<(unsigned short);
	LogStream& operator<<(int);
	LogStream& operator<<(unsigned int);
	LogStream& operator<<(long);
	LogStream& operator<<(unsigned long);
	LogStream& operator<<(long long);
	LogStream& operator<<(unsigned long long);
	LogStream& operator<<(float);
	LogStream& operator<<(double);
	LogStream& operator<<(long double);
	LogStream& operator<<(char);
	LogStream& operator<<(const char*);
	LogStream& operator<<(const std::string&);
	void append(const char *data,int len);
	const Buffer& buffer()const;
	void resetBuffer();
};
