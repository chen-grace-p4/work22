#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  while (1) {
    //prompt user for input
    char input[100];
    printf("Enter input to send:");
    fgets(input, 100, stdin);
    //sends to server
    write(to_server, input, sizeof(input));

    //recieves response
    int r = read(from_server, input, sizeof(input));
    if(r == 0) break;
    //display response
    printf("Response from server: %s\n", input);
  }

}
