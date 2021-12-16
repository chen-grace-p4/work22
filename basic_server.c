#include "pipe_networking.h"

int main() {

  int to_client;
  int from_client;

  //from_client = server_handshake( &to_client );

  //after client disconnect handshake starts again
  while(1) {
    //handshake
    from_client = server_handshake( &to_client );
    //continuously recieves data, process, sends back
    while(1) {
      //recieve data
      char input[100];
      int r = read(from_client, input, sizeof(input));
      if (r == 0) break;

      //process
      input[strlen(input)-1] = '\0';
      strcat(input, "manipulated");

      //sends back
      write(to_client, input, sizeof(input));
    }
  }
}
