#include "CPcap.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include "packet/CUDPPacket.h"
#include "packet/CTCPPacket.h"

#define LOG_DEBUG  printf
#define LOG_INFO   printf
#define LOG_WARN   printf
#define LOG_ERROR  printf
#define LOG_FATAL  printf
void CPcap::findAllDevs()
{

    pcap_if_t *alldevs;
    pcap_if_t *d;
    int i=0;
    char errbuf[PCAP_ERRBUF_SIZE];

    //获取本地机器设备列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        LOG_ERROR("Error in pcap_findalldevs_ex: %s\n", errbuf);
        exit(1);
    }

    //打印列表
    for(d= alldevs; d != NULL; d= d->next)
    {
        LOG_INFO("%d. %s", ++i, d->name);
        if (d->description)
            LOG_INFO(" (%s)\n", d->description);
        else
            LOG_INFO(" (No description available)\n");
    }

    if (i == 0)
    {
        LOG_INFO("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return;
    }

    /* 不再需要设备列表了，释放它 */
    pcap_freealldevs(alldevs);

}

void CPcap::start(pcap_handler pcapHandler, u_char *user)
{
    struct bpf_program fp;  //编译过滤表达示
    bpf_u_int32 mask;       //子网掩码
    bpf_u_int32 net;        //IP 地址

    char errbuf[PCAP_ERRBUF_SIZE];  //错误的缓冲区
    if (device == "default")
    {
        const char * pdev = pcap_lookupdev(errbuf); //捕获设备的名称
        if (nullptr != pdev)
        {
            device = pdev;
        }

    }

    if (device == "")
    {
        LOG_FATAL("Couldn't find default device: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }

    //获得捕获设备的网络号和掩码
    if (pcap_lookupnet(device.c_str(), &net, &mask, errbuf) == -1)
    {
        LOG_ERROR("Couldn't get netmask for device %s: %s\n", device.c_str(), errbuf);
        net = 0;
        mask = 0;
    }

    //显示捕获设备信息
    LOG_INFO("Device: %s\n", device.c_str());
    LOG_INFO("Number of packets: %d\n", capNums);
    LOG_INFO("Filter expression: %s\n", filterExp.c_str());

    //打开捕获设备
    //@1:捕获的设备;@2:每次捕获数据的最大长度;@3:1启用混杂模式;@4捕获时间,单位ms;@5:错误缓冲区
    pcap_t *handle = pcap_open_live(device.c_str(), 1518, 1, 1000, errbuf); //数据包捕获句柄
    if (handle == NULL)
    {
        LOG_FATAL("Couldn't open device %s: %s\n", device.c_str(), errbuf);
        exit(EXIT_FAILURE);
    }


    //pcap_datalink();
    //返回数据链路层类型，例如DLT_EN10MB;
    //确保我们对以太网设备捕获
    if (pcap_datalink(handle) != DLT_EN10MB)
    {
        LOG_FATAL("%s is not an Ethernet\n", device.c_str());
        exit(EXIT_FAILURE);
    }

    //编译过滤表达式
    if (pcap_compile(handle, &fp, filterExp.c_str(), 0, net) == -1)
    {
        LOG_FATAL("Couldn't parse filter %s: %s\n", filterExp.c_str(), pcap_geterr(handle));
        exit(EXIT_FAILURE);
    }

    // 应用过滤规则
    if (pcap_setfilter(handle, &fp) == -1)
    {
        LOG_FATAL("Couldn't install filter %s: %s\n", filterExp.c_str(), pcap_geterr(handle));
        exit(EXIT_FAILURE);
    }

    // 设置回高函数并开始捕获包
    pcap_loop(handle, capNums, pcapHandler, user);
    //释放
    pcap_freecode(&fp);
    pcap_close(handle);

    LOG_INFO("\nCapture complete.\n");

}


void CPcap::pcapHandler(u_char *count, const pcap_pkthdr *capInfo, const u_char *packet)
{
    (*(int *)count) ++;
    LOG_INFO("\n\n Packet num: %d\n", *(int *)count);
    if (capInfo)
    {
        LOG_INFO(" Packet len: %d\n", capInfo->len);
        LOG_INFO("    Cap len: %d\n", capInfo->caplen);
        LOG_INFO("   Cap time: %s", ctime((const time_t *)&capInfo->ts.tv_sec));
    }
    CUDPPacket pack1;
    if (nullptr != pack1.unPack(packet))
    {
        pack1.printAll();
        return;
    }
    CTCPPacket pack2;
    if (nullptr != pack2.unPack(packet))
    {
        pack2.printAll();
        return;
    }
    LOG_INFO("Other");
}


void CPcap::setDevice(const std::string &device)
{
    this->device = device.c_str();
}


void CPcap::setFilterExp(const string &value)
{
    filterExp = value;
}

void CPcap::setCapNums(int capNums)
{
    this->capNums = capNums;
}


