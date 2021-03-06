#ifndef NETWORKWRAPPER_H
#define NETWORKWRAPPER_H

#pragma once
#include <string>
#include <QString>
#include <vector>
#include <functional>

#include <cstdio> /// FILE
#include <string>
using namespace std;

QString s2q(const string &s);
string q2s(const QString &s);
#define USER_AGENT "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.79 Safari/537.36"
int CheckURL(const string& url,string vastr,string unstr,vector<string>errdic);

class Cookie
{
public:
    std::string domain;
    bool flag;
    std::string path;
    bool secure;
    int expiration;
    std::string name;
    std::string value;
};

class HTTPConnection
{
public:
    HTTPConnection();
    ~HTTPConnection();

    bool isReady() const;

    /// Behavior Options
    int setVerbos(bool v);/// disabled by default.
    int setErrStream(FILE* stream);
    int setSSLVerifyPeer(bool enable);/// enabled by default.
    int setSSLVerifyHost(bool enable);/// enabled by default.

    int setHeaderInBody(bool enable);/// disabled by default.
    int setSignal(bool hasSignal);/// enabled by default.

    /// Set the progress meter will automatically enable progress.
    /// The callback set by setProgressMeter() must return 0. If a non-zero value is returned, the data transfer process will be aborted.
    int enableProgress(bool hasProgress);/// disabled by default.
	int setProgressMeter(const std::function<int(long long, long long, long long, long long)>& fn);

    /// If set...OutputBuffer() is called, then an internal data writer function will be used to fill it.
    /// So don't use set...OutputBuffer() and set...Writer() together.
    /// If ptr is nullptr and maxsz is not 0, then a new buffer will be created with given size to contain the data. Return -2 on not enough memory.
    /// If ptr is nullptr and maxsz is 0, then the buffer will be created after received data size is calculated. If there's not enough memory, get...OutputBuffer() will return nullptr.
    /// get...OutputBuffer() will return internal buffer if used. DO NOT call free or delete on it.
    int setHeaderWriter(const std::function<int(char*,int)>& fn);
    int setHeaderOutputBuffer(void* ptr,int maxsz);
    int setHeaderOutputFile(const std::string& filename);

    int setDataWriter(const std::function<int(char*,int)>& fn);
    int setDataOutputBuffer(void* ptr,int maxsz);
    int setDataOutputFile(const std::string& filename);

    int setDataReader(const std::function<int(char*,int)>& fn);
    int setDataInputFile(const std::string& filename);

    int enableCookieEngine();
    int setCookieInputFile(const std::string& filename);
    int setCookieOutputFile(const std::string& filename);
    int setCookieSession(bool new_session);

    int addCookie(const std::string& raw_cookie);
    int clearCookie();
    int clearSessionCookie();
    int flushCookie();
    int reloadCookie();

    int setTimeout(int second);

    /// HTTP Option
    int setAcceptEncoding(const std::string& encoding);
    int setAcceptEncodingAll();
    int setTransferEncoding(bool enable);/// disabled by default
    int setUserAgent(const std::string& user_agent);
    int setReferer(const std::string& referer);
    int setOrigin(const std::string& origin);
    int setPostData(const void* data,int sz);
    int setPostData(const std::string& data);
    int setFollowLocation(bool enable);/// disabled by default

    enum class Method
    {
        Get,Post
    };

    int setMethod(Method m);/// Method::Get by default.
    int setURL(const std::string& URL);

    /// KeepAlive is disabled by default.
    int setKeepAlive(long idle_second,long interval_second);
    int disableKeepAlive();

    int perform();

    /// Response
    int getResponseCode();
    std::vector<Cookie> getCookies();
    const void* getHeaderOutputBuffer();
    const int getHeaderOutputBufferLength();
    const void* getDataOutputBuffer();
    const int getDataOutputBufferLength();
    std::string getRedirectURL();

    /// Error handling
    int getLastErrCode();
    std::string getLastError();

    /// NetworkWrapper Debug API
    /// Define NETWORKE_WRAPPER_DEBUG to enable internal debug utilities.
    /// Otherwise, debug functions will not be usable.

    /// Length of debug queue used to traceback.
    class debug_info
    {
    public:
        std::string libfn; /// function name of libcurl
        std::string callfn; /// function name of NetworkWrapper
        int ret; /// return value of libcurl function
        int callid; /// call id of NetworkWrapper
    };
    int setDebugQueueLength(int length);
    int traversalDebugQueue(const std::function<int(const debug_info&)>& fn);
private:
    class _impl;
    _impl* _p;
};
#endif
