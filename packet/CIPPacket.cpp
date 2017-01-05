#include "CIPPacket.h"


const u_char *CIPPacket::unPack(const u_char *packet)
{
    packet = CEtherPacket::unPack(packet);
    RETURN_NULL_PACKET;
    if (getEtherType() != ETHERTYPE_IP)
    {
        return nullptr;
    }
    memcpy(&_ip, packet, sizeof(ip));
    return packet + _ip.ip_hl * 4; //有可能有option，这些信息跳过

}


std::string CIPPacket::getIPSrc()
{
    char ip[16] = {0};
    inet_ntop(AF_INET, &_ip.ip_src, ip, 16);
    return string(ip);
}

std::string CIPPacket::getIPDst()
{
    char ip[16] = {0};
    inet_ntop(AF_INET, &_ip.ip_dst, ip, 16);
    return string(ip);
}

u_int8_t CIPPacket::getIPProtocol()
{
    return _ip.ip_p;
}

u_short CIPPacket::getIPLen()
{
    return ntohs(_ip.ip_len);
}

u_short CIPPacket::getIPHeadLen()
{
    return _ip.ip_hl * 4;
}

void CIPPacket::printIP()
{
    printf("    From IP: %s\n", getIPSrc().c_str());
    printf("      To IP: %s\n", getIPDst().c_str());
    printf("   Protocol: %d\n", getIPProtocol());
}

void CIPPacket::printAll()
{
    CEtherPacket::printAll();
    printIP();
}


