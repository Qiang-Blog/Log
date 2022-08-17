# muduo 双缓冲日志系统
## Introduction
模仿muduo日志库实现的异步日志库
## Build

```c++
make
./out
```
## 实现
- 基础类：noncopyable、MutexLock、Conditicon、CurrentThread、Thread

- 文件工具类：FileUtil、LogFile、LogStream

- 逻辑实现类：AsyncLogging

- 对外接口类：Logging

基础类主要是对一些API进行封装，我在项目中直接调用了API。详细实现细节可以到muduo库中查看。

### FileUtil.h & FileUtil.cpp

FileUtil 文件实现了AppenFile类，实现底层对文件的打开，append和write操作，这里自己对文件描述符设置一个新的缓冲区buffer， 每次需要保证把所有的内容全部写入文件，需要处理一下。

### LogFile.h & LogFile.cpp

LogFile 实现LogFile类，该类持有一个FileUtil实现的AppendFile，为了保证线程安全，还需要一个互斥锁，然后提供appendn次去flush一次，这个通过一个计数器实现，当counter到达flushEveryN的时候就会去触发flush操作，将内容刷入硬盘。

### AsyncLogging.h & AsyncLogging.cpp

AsyncLogging 实现AsyncLogging类，是该双缓冲异步日志的关键类，他持有一个LogFile，以及几个缓冲区（这里用到多个缓冲区，但是目的和双缓冲是一样的)，另外，该类持有一个Thread来执行日志的写入操作，同样主要实现append和flush操作。

详细细节参考博客：[这是个链接](https://blog.csdn.net/daaikuaichuan/article/details/86500108)

### LogStream.h & LogStream.cpp

LogStream 实现了FixedBuffer类（可以理解为一个比较灵活的buffer，底层还是数组），然后LogStream类主要对<<运算符进行重载，通过格式化的方式写入buffer，此时通过LogStream写入的日志全部缓存到FixedBuffer中，当需要写入的时候需要需要通过Logger对外接口调用全部写入Buffer中，然后去调用AsyncLogging写入，这里初始话AsyncLogging使用了PTHREAD_ONCE_INIT属性。

### Logging.h & Logging.cpp

Logging 实现了Logger类以及对外的Impl接口类，接口内主要是对LogStream的描述，Logging.cpp中声明一个AsyncLogging对象，首先会将日志写入stream中，然后在logger类析构的时候将日志写入调用线程异步写入硬盘。


