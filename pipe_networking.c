#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int from_client = 0;
  printf("SERVER CREATES WKP AND WAITS FOR CONNECTION:\n");
  mkfifo(WKP, 0644);
  printf("created well known pipe\n");

  from_client = open(WKP, O_RDONLY);
  printf("opened well known pipe for reading\n");

  printf("SERVER RECIEVES MESSAGE FROM CLIENT:\n");
  char message[100];
  read(from_client, message, sizeof(message));
  printf("read well known pipe\n");

  printf("SERVER REMOVES WKP:\n");
  remove(WKP);
  printf("removed well known pipe\n");

  printf("SERVER SENDS MESSAGE TO CLIENT:\n");
  *to_client = open(message, O_WRONLY);
  printf("opened secret pipe %s\n", message);
  write(*to_client, ACK, sizeof(ACK));
  printf("sent ACK\n");

  printf("SERVER RECIEVES FINAL VERIFICATION MESSAGE:\n");
  read(from_client, message, sizeof(message));
  printf("got final message\n");

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server = 0;

  printf("CLIENT CREATES PIPE:\n");
  char pid[100];
  sprintf(pid, "%d", getpid());
  from_server = mkfifo(pid, 0644);
  printf("created secret pipe: %s\n", pid);

  printf("CLIENT SENDS MESSAGE TO SERVER:\n");
  *to_server = open(WKP, O_WRONLY);
  printf("opened well known pipe\n");
  write(*to_server, pid, strlen(pid)+1);
  printf("sent unique secret pipe message\n");

  printf("CLIENT RECIEVES RESPONSE:\n");
  from_server = open(pid, O_RDONLY);
  printf("opened secret pipe\n");

  char message[100];
  read(from_server, message, sizeof(message));
  printf("recieved ACK\n");

  printf("CLIENT REMOVES SECRET PIPE:\n");
  remove(pid);
  printf("removed secret pipe\n");

  printf("CLIENT SENDS FINAL VERIFICATION MESSAGE:\n");
  write(*to_server, ACK, sizeof(ACK));
  printf("sent final ACK\n");

  return from_server;
}
