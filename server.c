#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080 // where clients connect to

int main(int argc, char const *argv[]){
    int server_fd, new_socket; 
    long valread; 
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char *hello = "Hello from server!";

    // Socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Cannot create socket.\n");
        return 0;
    }

    // htonl converts a long int, such as an address, to network form
    // htons converts a short int, such as a port, to network form
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    // Forcing socket to port 8080
    if(bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0){
        perror("In Bind\n");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd, 10) < 0){
        perror("In listen\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        printf("\n++++++++++Waiting for new Connection++++++++++\n\n");
        if(new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen) < 0){
            perror("In accept\n");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        write(new_socket, hello, strlen(hello));
        printf("\n++++++++++Hello message sent++++++++++\n\n");
        close(new_socket);
    }
    return 0;
}
