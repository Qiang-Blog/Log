# muduo ˫������־ϵͳ
## Introduction
ģ��muduo��־��ʵ�ֵ��첽��־��
## Build

```c++
make
./out
```
## ʵ��
- �����ࣺnoncopyable��MutexLock��Conditicon��CurrentThread��Thread

- �ļ������ࣺFileUtil��LogFile��LogStream

- �߼�ʵ���ࣺAsyncLogging

- ����ӿ��ࣺLogging

��������Ҫ�Ƕ�һЩAPI���з�װ��������Ŀ��ֱ�ӵ�����API����ϸʵ��ϸ�ڿ��Ե�muduo���в鿴��

### FileUtil.h & FileUtil.cpp

FileUtil �ļ�ʵ����AppenFile�࣬ʵ�ֵײ���ļ��Ĵ򿪣�append��write�����������Լ����ļ�����������һ���µĻ�����buffer�� ÿ����Ҫ��֤�����е�����ȫ��д���ļ�����Ҫ����һ�¡�

### LogFile.h & LogFile.cpp

LogFile ʵ��LogFile�࣬�������һ��FileUtilʵ�ֵ�AppendFile��Ϊ�˱�֤�̰߳�ȫ������Ҫһ����������Ȼ���ṩappendn��ȥflushһ�Σ����ͨ��һ��������ʵ�֣���counter����flushEveryN��ʱ��ͻ�ȥ����flush������������ˢ��Ӳ�̡�

### AsyncLogging.h & AsyncLogging.cpp

AsyncLogging ʵ��AsyncLogging�࣬�Ǹ�˫�����첽��־�Ĺؼ��࣬������һ��LogFile���Լ������������������õ����������������Ŀ�ĺ�˫������һ����)�����⣬�������һ��Thread��ִ����־��д�������ͬ����Ҫʵ��append��flush������

��ϸϸ�ڲο����ͣ�[���Ǹ�����](https://blog.csdn.net/daaikuaichuan/article/details/86500108)

### LogStream.h & LogStream.cpp

LogStream ʵ����FixedBuffer�ࣨ�������Ϊһ���Ƚ�����buffer���ײ㻹�����飩��Ȼ��LogStream����Ҫ��<<������������أ�ͨ����ʽ���ķ�ʽд��buffer����ʱͨ��LogStreamд�����־ȫ�����浽FixedBuffer�У�����Ҫд���ʱ����Ҫ��Ҫͨ��Logger����ӿڵ���ȫ��д��Buffer�У�Ȼ��ȥ����AsyncLoggingд�룬�����ʼ��AsyncLoggingʹ����PTHREAD_ONCE_INIT���ԡ�

### Logging.h & Logging.cpp

Logging ʵ����Logger���Լ������Impl�ӿ��࣬�ӿ�����Ҫ�Ƕ�LogStream��������Logging.cpp������һ��AsyncLogging�������ȻὫ��־д��stream�У�Ȼ����logger��������ʱ����־д������߳��첽д��Ӳ�̡�


