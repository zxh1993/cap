#ifndef CPCAP_H
#define CPCAP_H


#include <pcap.h>
#include <iostream>
#include <string>

using std::string;

class CPcap
{
public:
    CPcap() = default;

    static void findAllDevs();
    void start(pcap_handler pcapHandler, u_char *user);

    static void pcapHandler(u_char *count, const struct pcap_pkthdr *capInfo, const u_char *packet);

    void setDevice(const string &device);
    void setFilterExp(const string &value);
    void setCapNums(int capNums);



private:
    //捕获的数据包数量
    string device;
    int capNums = -1;
    //过滤器配置
    string filterExp;

};

#endif // CPCAP_H
