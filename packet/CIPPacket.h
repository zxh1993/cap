#ifndef CIPPACKET_H
#define CIPPACKET_H
#include "CEtherPacket.h"
#include <netinet/ip.h>
class CIPPacket : public CEtherPacket
{
public:
    CIPPacket() = default;

    const u_char* unPack(const u_char* packet);

    string getIPSrc();
    string getIPDst();
    u_int8_t getIPProtocol();
    u_short getIPLen();
    u_short getIPHeadLen();

    void printIP();
    void printAll();
private:
    ip _ip;
};

#endif // CIPPACKET_H
