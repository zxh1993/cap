#ifndef CTCPPACKET_H
#define CTCPPACKET_H
#include "CIPPacket.h"
#include "netinet/tcp.h"

class CTCPPacket : public CIPPacket
{
public:
    CTCPPacket() = default;

    const u_char* unPack(const u_char* packet);

    u_short getTCPHeadLen();
    u_int16_t getSrcPort();
    u_int16_t getDstPort();

    void printTCPHdr();
    void printData();
    void printAll();
private:
    tcphdr _tcphdr;
    ustring _data;
};

#endif // CTCPPACKET_H
