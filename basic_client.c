#include "pipe_networking.h"
static void sighandler(int signo);

int main() {
  signal(SIGINT, sighandler);

  int to_server;
  int from_server;
  char buffer[BUFFER_SIZE];
  from_server = client_handshake( &to_server );

  while (1) {
    printf("Input: ");
		fgets(buffer, sizeof(buffer), stdin);

		//replace newline with terminating null
		*strchr(buffer, '\n') = 0;

		//using sizeof is better because strlen could easily change
		write(to_server, buffer, sizeof(buffer));
		read(from_server, buffer, sizeof(buffer));

		printf("received: -%s-\n", buffer);
  }
  return 0;
}

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove(WKP);
    exit(EXIT_SUCCESS);
  }
}
