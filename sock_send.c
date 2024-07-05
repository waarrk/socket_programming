#include <arpa/inet.h>
#include <unistd.h>

int main() {
  int sock;
  struct sockaddr_in addr;
  char msg[] = "Hello, World!\n";

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8000);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *)&addr, sizeof(addr));
  close(sock);

  return 0;
}