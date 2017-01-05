#include "CUDPPacket.h"
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


const u_char *CUDPPacket::unPack(const u_char *packet)
{
    packet = CIPPacket::unPack(packet);
    RETURN_NULL_PACKET;
    if (getIPProtocol() != IPPROTO_UDP)
    {
        return nullptr;
    }
    memcpy(&_udphdr, packet, sizeof(udphdr));
    packet += sizeof(udphdr);
    int dataSize = ntohs(_udphdr.len) - sizeof(udphdr);
    _data.clear();
    _data.append(packet, dataSize);
    return packet + dataSize;
}



u_int16_t CUDPPacket::getSrcPort()
{
    return ntohs(_udphdr.source);
}

u_int16_t CUDPPacket::getDstPort()
{
    return ntohs(_udphdr.dest);
}

u_int16_t CUDPPacket::getUDPLen()
{
    return ntohs(_udphdr.len);
}

u_int16_t CUDPPacket::getUDPChecksum()
{
    return ntohs(_udphdr.check);
}

std::basic_string<u_char> CUDPPacket::getData() const
{
    return _data;
}

void CUDPPacket::printUDPHdr()
{
    printf("   Src port: %d\n", getSrcPort());
    printf("   Dst port: %d\n", getDstPort());
    printf(" UDP length: %d\n", getUDPLen());
    printf("   Checksum: %d\n", getUDPChecksum());
}

void CUDPPacket::printData()
{
    printPacket(_data);
}

void CUDPPacket::printAll()
{
    CIPPacket::printAll();
    printUDPHdr();
    printData();
}


