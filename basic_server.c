#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  while(1) {
    from_client = server_setup();

    int f;
    f = fork();

    //subserver
    if (f == 0) {
      //char buff[BUFFER_SIZE];
      to_client = server_connect(from_client);

      while(1) {
        //recieve data
        char buff[BUFFER_SIZE];
        int r = read(from_client, buff, sizeof(buff));
        if (!r) break;

        //process
        buff[strlen(buff)] = '\0';
        strcat(buff, "manipulated");

        //sends back
        write(to_client, buff, sizeof(buff));
      }
    }
  }
  return 0;
}
