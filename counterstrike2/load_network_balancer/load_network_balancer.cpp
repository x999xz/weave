#include "../utilities/tls/tls.h"
#include "load_network_balancer.h"
#include <winsock.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <string>
#include "../utilities/xorstr.h"
#pragma comment(lib, "iphlpapi.lib")

void load_network_balancer::setup() {
    m_pools = { 3013094803, 23276037 };

    int best_ping = 9999;
    bool found = false;

    StartTCP()

    for (auto server : m_pools) {
        int ping = send_request(server);
        if (ping >= 0 && ping < best_ping) {
            best_server = server;
            best_ping = ping;
            found = true;
        }
    }

    if (!found) {
        best_server = m_pools.at(0);
    }
}

int load_network_balancer::send_request(unsigned long server) {

    HANDLE hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        return -1;
    }

    DWORD replySize = sizeof(ICMP_ECHO_REPLY) + 8;
    LPVOID replyBuffer = (VOID*)malloc(replySize);
    DWORD reply = IcmpSendEcho2(hIcmpFile, NULL, NULL, NULL, server, NULL, NULL, NULL, replyBuffer, replySize, 1000);

    int ping = -1;

    if (reply != 0) {
        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)replyBuffer;
        ping = pEchoReply->RoundTripTime;
    }

    free(replyBuffer);
    IcmpCloseHandle(hIcmpFile);
    return ping;
}

unsigned long& load_network_balancer::get_server() {
    return best_server;
}