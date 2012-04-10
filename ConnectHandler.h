#ifndef CONNECTHANDLER_H_
#define CONNECTHANDLER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cerrno>

#include <fcntl.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/poll.h>

struct HostInfo {
	/* Map of connections to the server */
	static std::map<std::string,int> connections;
	/* Mutex variable */
	static pthread_mutex_t mutex;

	/* Socket descriptor of remote host */
	int remote_sock;
	/* Remote host IP address */
	std::string remote_ip_address;
	/* Remote host Port */
	unsigned short int remote_port;
	/* Local host IP address */
	std::string local_ip_address;
	/* Local host Port */
	unsigned short int local_port;

	/* Remote host information (IP+port) */
	std::string remote_info;
	/* Local host information (IP+port) */
	std::string local_info;

	HostInfo(int remote_sock, const std::string& remote_ip_address, unsigned short int remote_port,
			const std::string& local_ip_address, unsigned short int local_port);

	~HostInfo();
};

/* Thread connection handler */
void* ConnectHandler(void* thread_arg);

#endif /* CONNECTHANDLER_H_ */
