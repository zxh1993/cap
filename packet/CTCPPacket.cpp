#include "CTCPPacket.h"

const u_char *CTCPPacket::unPack(const u_char *packet)
{
    packet = CIPPacket::unPack(packet);
    RETURN_NULL_PACKET;
    if (getIPProtocol() != IPPROTO_TCP)
    {
        return nullptr;
    }
    memcpy(&_tcphdr, packet, sizeof(tcphdr));
    packet += getTCPHeadLen();
    int dataSize = getIPLen() - getIPHeadLen() - getTCPHeadLen();
    _data.append(packet, dataSize);
    return packet + dataSize;
}

u_short CTCPPacket::getTCPHeadLen()
{
    return _tcphdr.th_off * 4;
}

u_int16_t CTCPPacket::getSrcPort()
{
    return ntohs(_tcphdr.th_sport);
}

u_int16_t CTCPPacket::getDstPort()
{
    return ntohs(_tcphdr.th_dport);
}

void CTCPPacket::printTCPHdr()
{
    printf("   Src port: %d\n", getSrcPort());
    printf("   Dst port: %d\n", getDstPort());
}

void CTCPPacket::printData()
{
    printPacket(_data);
}

void CTCPPacket::printAll()
{
    CIPPacket::printAll();
    printTCPHdr();
    printData();
}

