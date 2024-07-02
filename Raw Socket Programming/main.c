/**
 * @brief Example program to demonstrate raw sockets programming in C.
 *
 * This program demonstrates the use of raw sockets to send and receive raw
 * Ethernet frames. It provides low-level access to network packets at the
 * protocol level, allowing for tasks such as network monitoring, packet
 * filtering, protocol development, and network security testing.
 *
 * Prerequisites:
 * - Linux Environment: Raw sockets are typically supported on Unix-like
 *   systems such as Linux.
 * 
 * - Root/Administrator Privileges: Required to create raw sockets and send/receive
 *   packets.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <sys/ioctl.h>

/**
 * @brief Structure to represent an Ethernet frame.
 */
struct ether_frame {
    struct ethhdr header;  ///< Ethernet header
    unsigned char data[ETH_FRAME_LEN - sizeof(struct ethhdr)];  ///< Payload
};

/**
 * @brief Calculate the checksum of a buffer.
 *
 * @param b Pointer to the buffer.
 * @param len Length of the buffer.
 * @return The checksum.
 */
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

/**
 * @brief Create a raw socket.
 *
 * @return The file descriptor of the raw socket, or -1 on error.
 */
int create_raw_socket() {
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

/**
 * @brief Send a raw Ethernet frame.
 *
 * @param sockfd The file descriptor of the raw socket.
 * @param dest_mac The destination MAC address.
 * @param src_mac The source MAC address.
 * @param ether_type The Ethernet type.
 * @param payload The payload.
 * @param payload_len The length of the payload.
 */
void send_raw_ethernet(int sockfd, const unsigned char *dest_mac, const unsigned char *src_mac,
                       unsigned short ether_type, const unsigned char *payload, int payload_len) {
    struct ether_frame frame;
    struct sockaddr_ll socket_address;

    // Prepare Ethernet header
    memcpy(frame.header.h_dest, dest_mac, ETH_ALEN);
    memcpy(frame.header.h_source, src_mac, ETH_ALEN);
    frame.header.h_proto = htons(ether_type);

    // Prepare payload
    memcpy(frame.data, payload, payload_len);

    // Zero out socket address struct
    memset(&socket_address, 0, sizeof(struct sockaddr_ll));

    // Set socket family
    socket_address.sll_family = AF_PACKET;

    // Set packet interface index
    struct ifreq ifr;
    strncpy((char *)ifr.ifr_name, "eth0", IFNAMSIZ); // Change "eth0" to your network interface
    ioctl(sockfd, SIOCGIFINDEX, &ifr);
    socket_address.sll_ifindex = ifr.ifr_ifindex;

    // Send packet
    if (sendto(sockfd, &frame, sizeof(struct ethhdr) + payload_len, 0, (struct sockaddr *)&socket_address, sizeof(struct sockaddr_ll)) < 0) {
        perror("Packet send failed");
    } else {
        printf("Packet sent successfully\n");
    }
}

/**
 * @brief Receive a raw Ethernet frame.
 *
 * @param sockfd The file descriptor of the raw socket.
 */
void receive_raw_ethernet(int sockfd) {
    struct ether_frame frame;
    struct sockaddr_ll socket_address;
    socklen_t sll_len = sizeof(socket_address);
    ssize_t recv_size;

    // Receive packet
    recv_size = recvfrom(sockfd, &frame, sizeof(struct ether_frame), 0, (struct sockaddr *)&socket_address, &sll_len);
    if (recv_size < 0) {
        perror("Packet receive failed");
    } else {
        printf("Packet received successfully\n");

        // Print Ethernet header info
        printf("Destination MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
               frame.header.h_dest[0], frame.header.h_dest[1], frame.header.h_dest[2],
               frame.header.h_dest[3], frame.header.h_dest[4], frame.header.h_dest[5]);
        printf("Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
               frame.header.h_source[0], frame.header.h_source[1], frame.header.h_source[2],
               frame.header.h_source[3], frame.header.h_source[4], frame.header.h_source[5]);
        printf("Ethernet Type: %04x\n", ntohs(frame.header.h_proto));

        // Print payload (data)
        printf("Payload (first 20 bytes): ");
        for (int i = 0; i < 20 && i < recv_size - sizeof(struct ether_frame); ++i) {
            printf("%02x ", frame.data[i]);
        }
        printf("\n");
    }
}

int main() {
    int sockfd = create_raw_socket();

    // Example: Send a raw Ethernet frame
    unsigned char dest_mac[] = {0x00, 0x0c, 0x29, 0xb1, 0x1e, 0x1f}; // Destination MAC address
    unsigned char src_mac[] = {0x00, 0x0c, 0x29, 0x73, 0x6d, 0x3b};  // Source MAC address
    unsigned short ether_type = ETH_P_IP; // Ethernet type (IPv4)
    unsigned char payload[] = "Hello, raw Ethernet!"; // Payload
    int payload_len = strlen(payload);

    send_raw_ethernet(sockfd, dest_mac, src_mac, ether_type, payload, payload_len);

    // Example: Receive a raw Ethernet frame
    receive_raw_ethernet(sockfd);

    close(sockfd);
    return 0;
}

