#ifndef CUDPPACKET_H
#define CUDPPACKET_H

#include "CIPPacket.h"
#include <netinet/udp.h>

class CUDPPacket : public CIPPacket
{
public:
    CUDPPacket() = default;

    const u_char* unPack(const u_char* packet);

    u_int16_t getSrcPort();
    u_int16_t getDstPort();
    u_int16_t getUDPLen();
    u_int16_t getUDPChecksum();
    std::basic_string<u_char> getData() const;

    void printUDPHdr();
    void printData();
    void printAll();
private:
    udphdr _udphdr;
    std::basic_string<u_char> _data;
};

#endif // CUDPPACKET_H
