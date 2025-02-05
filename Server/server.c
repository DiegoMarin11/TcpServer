/* Basic TCP Server in C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <Interface.h>
//#include <MongoInterface.c>
#include <tokenizer.h>

#define PORT 8080
#define BUFFER_SIZE 1024




void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        printf("Connection closed or error.\n");
        close(client_socket);
        return;
    }
    buffer[bytes_received] = '\0';

    printf("Received: %s\n", buffer);



    char *fields[MAX_BUFFER];
    int count = tokenize(buffer, fields);

     if (count != 3) { 
        send(client_socket, "ERROR", 5, 0);
        close(client_socket);
        return;
    }


   if (strcmp(fields[0], "INSERT") == 0) {
        int response = 1;
        insert_data(fields[1], fields[2], response);

        if (response == 1) {
            send(client_socket, "OK", 2, 0);
        } else {
            send(client_socket, "ERROR", 5, 0);
        }

    } else if (strcmp(fields[0], "FETCH") == 0) {
        fetch_data();
        send(client_socket, "FETCH_DONE", 10, 0);
    }

    close(client_socket);
}

int main() {

    init_mongo();


    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }
        printf("Client connected.\n");
        handle_client(client_socket);
    }

    close(server_socket);
    close_mongo();
    return 0;
}
