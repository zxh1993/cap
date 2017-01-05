#include <iostream>
#include "cap/CPcap.h"

using namespace std;

int main()
{
    CPcap cap;
    CPcap::findAllDevs(); //找所有设备
    cap.setCapNums(-1); //设置捕获数,-1 一直捕获
    cap.setDevice("default"); // 设置网卡
    cap.setFilterExp("udp or tcp"); //过滤规则
    int count = 0; //包计数
    cap.start(CPcap::pcapHandler, (u_char *) &count);
    return 0;
}

