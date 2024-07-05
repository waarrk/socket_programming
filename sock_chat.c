#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void recv_thread(void);
int sock;

int main(int argc, char *argv[]) {
  pthread_t t1;
  struct sockaddr_in addr;
  char send_buf[2048];
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[1]));
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock, (struct sockaddr *)&addr, sizeof(addr));
  pthread_create(&t1, NULL, (void *)recv_thread, (void *)NULL);

  addr.sin_port = htons(atoi(argv[2]));
  if (argc == 4) addr.sin_addr.s_addr = inet_addr(argv[3]);

  while (1) {
    scanf("%s", send_buf);
    if (!strcmp(send_buf, "quit")) break;
    sendto(sock, send_buf, strlen(send_buf), 0, (struct sockaddr *)&addr,
           sizeof(addr));
  }
  close(sock);
  return 0;
}

void recv_thread(void) {
  char recv_buf[2048];

  while (1) {
    int num = recv(sock, recv_buf, sizeof(recv_buf), 0);
    recv_buf[num] = 0;
    printf("%s\n", recv_buf);
  }
}