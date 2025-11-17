#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>

int exit_failure(const std::string& msg, int err, int sockfd, int connection) {
  std::cerr << "Error: " << msg << "\nerrno: " << err << std::endl;
  if (sockfd > -1)
    close(sockfd);
  if (connection > -1)
    close(connection);
  return EXIT_FAILURE;
}

bool readFromSocket(int connection, std::string& full_msg) {
  char buffer[10];
  ssize_t bytes_read = read(connection, buffer, sizeof(buffer) - 1);
  buffer[bytes_read] = '\0';
  if (bytes_read == 2)
    return false;
  full_msg += buffer;
  if (full_msg.back() == '\n') {
    full_msg.pop_back();
    full_msg.pop_back();
    return false;
  }
  return true;
}

int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
    return exit_failure("Failed to create socket", errno, -1, -1);

  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    return exit_failure("Failed to set socket options", errno, sockfd, -1);

  sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(9999);

  if (bind(sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    return exit_failure("Failed to bind port 9999", errno, sockfd, -1);

  if (listen(sockfd, 10) < 0)
    return exit_failure("Failed to listen on socket", errno, sockfd, -1);

  socklen_t addr_len = sizeof(addr);
  int connection = accept(sockfd, reinterpret_cast<sockaddr*>(&addr), &addr_len);
  if (connection < 0)
    return exit_failure("Failed to grab connection", errno, sockfd, -1);

  while (true) {

    std::string full_msg; 
    
    while (readFromSocket(connection, full_msg)) {}

    std::cout << "Message received:\n" << full_msg << std::endl;

    std::string response = "Message Received!\n";
    if (send(connection, response.c_str(), response.size(), 0) < 0)
      return exit_failure("Failed to send response", errno, sockfd, connection);

    if (full_msg.compare("END") == 0)
        break;
  }
  
  close(connection);
  close(sockfd);
  return EXIT_SUCCESS;
}
