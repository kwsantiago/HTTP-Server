#include <stdio.h>
#include <sys/socket.h>

int main(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Cannot create socket.\n");
        return 0;
    }
    return 0;
}
