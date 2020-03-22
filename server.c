#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Cannot create socket.\n");
        return 0;
    }
    struct sockaddr_in address;
    const int PORT = 8080; // where clients connect to

    // htonl converts a long int, such as an address, to network form
    // htons converts a short int, such as a port, to network form

    memset((char*)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    if(bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0){
        perror("Bind failed\n");
        return 0;
    }

    return 0;
}
