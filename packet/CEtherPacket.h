#ifndef CETHERPACKET_H
#define CETHERPACKET_H

#include <netinet/ether.h>
#include <string.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#define RETURN_NULL_PACKET     if (packet == nullptr){return nullptr;}

using ustring = std::basic_string<u_char>;
using std::string;
class CEtherPacket
{
public:
    static void printPacket(const ustring &packet);

    CEtherPacket() = default;

    const u_char* unPack(const u_char* packet);

    ustring getEtherDhost();
    ustring getEtherShost();
    uint16_t getEtherType();

    void printEtherHeader();
    void printAll();


private:
    ether_header _etherHeader;
};

#endif // CETHERPACKET_H
