#include "CEtherPacket.h"

void CEtherPacket::printPacket(const ustring &packet)
{
    const u_char *payload = packet.c_str();
    int len = packet.size();
    printf("  Data size: %d\n", len);
    auto printHex= [](const u_char *payload, int len, int offset)
    {
        int i;
        int gap;
        const u_char *ch;

        printf("%05d   ", offset);

        ch = payload;
        for(i = 0; i < len; i++)
        {
            printf("%02x ", *ch);
            ch++;
            if (i == 7)
                printf(" ");
        }

        if (len < 8)
            printf(" ");

        if (len < 16)
        {
            gap = 16 - len;
            for (i = 0; i < gap; i++)
            {
                printf("   ");
            }
        }
        printf("   ");

        ch = payload;
        for(i = 0; i < len; i++)
        {
            if (isprint(*ch))
                printf("%c", *ch);
            else
                printf(".");
            ch++;
        }
        printf("\n");
    };

    int lenRem = len;
    int lineWidth = 16;
    int lineLen;
    int offset = 0;
    const u_char *ch = payload;

    if (len <= 0)
        return;

    if (len <= lineWidth)
    {
        printHex(ch, len, offset);
        return;
    }

    while (true)
    {
        lineLen = lineWidth % lenRem;
        printHex(ch, lineLen, offset);
        lenRem = lenRem - lineLen;
        ch = ch + lineLen;
        offset = offset + lineWidth;
        if (lenRem <= lineWidth)
        {
            printHex(ch, lenRem, offset);
            break;
        }
    }
}

const u_char *CEtherPacket::unPack(const u_char *packet)
{
    RETURN_NULL_PACKET;
    memcpy(&_etherHeader, packet, sizeof(ether_header));
    return packet + sizeof(ether_header);
}


ustring CEtherPacket::getEtherDhost()
{
    return ustring(_etherHeader.ether_dhost, ETH_ALEN);
}

ustring CEtherPacket::getEtherShost()
{
    return ustring(_etherHeader.ether_shost, ETH_ALEN);
}

uint16_t CEtherPacket::getEtherType()
{
    return ntohs(_etherHeader.ether_type);
}

void CEtherPacket::printEtherHeader()
{
    printf("  From addr: ");
    for (int i = 0; i < 6; i++)
    {
        printf("%02x", _etherHeader.ether_shost[i]);
    }
    printf("\n");

    printf("    To addr: ");
    for (int i = 0; i < 6; i++)
    {
        printf("%02x", _etherHeader.ether_dhost[i]);
    }
    printf("\n");
    printf(" Ether type: %d\n", _etherHeader.ether_type);
}

void CEtherPacket::printAll()
{
    printEtherHeader();
}

