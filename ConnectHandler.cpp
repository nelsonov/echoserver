#include "ConnectHandler.h"

using namespace std;

/* Global map were the connections are saved */
std::map<std::string,int> HostInfo::connections;
/* Mutex variable */
pthread_mutex_t HostInfo::mutex;

static string IntToString(int number) {
   stringstream ss;
   ss << number;
   return ss.str();
}

HostInfo::HostInfo(int remote_sock, const string& remote_ip_address, unsigned short int remote_port,
		const string& local_ip_address, unsigned short int local_port) :
         remote_sock(remote_sock),
         remote_ip_address(remote_ip_address),
         remote_port(remote_port),
         local_ip_address(local_ip_address),
         local_port(local_port) {

	/* Grab information of the host connected */
	string sremote_port = IntToString(this->remote_port);
	/* Grab information of the local host */
	string slocal_port = IntToString(this->local_port);

	/* Create a string of remote host information */
	remote_info = this->remote_ip_address + ":" + sremote_port;
	/* Create a string of local host information */
	local_info = this->local_ip_address + ":" + slocal_port;

	/* Add the new connection information into the static map */
	pthread_mutex_lock(&mutex);
	connections[remote_info] = this->remote_sock;
	pthread_mutex_unlock(&mutex);
}

void* ConnectHandler(void* thread_arg) {
	/* Get information of the proxy connection */
	HostInfo* host_info = static_cast<HostInfo*>(thread_arg);

	/* Get the socket descriptor of the remote host */
	int remote_sock = host_info->remote_sock;

	/* Grab information of the local and remote hosts */
	string remote_info = host_info->remote_info;
	string local_info = host_info->local_info;

    /* Buffer for receiving data */
    const int buffer_len = 65536;
    char* buffer = new char[buffer_len];

    /* Set the buffer to zero */
    memset(buffer, 0, buffer_len);

    /* Count of bytes received */
    int bytecount;
    /* Count of bytes send */
    int sendcount;

    while(1) {

		/* Set the buffer to zero */
		memset(buffer, 0, buffer_len);

		/* Receive data */
		bytecount = recv(remote_sock, buffer, buffer_len, 0);
		if(bytecount == -1){
			string message = "[@] Error receiving data from host " + remote_info;
			perror(message.c_str());
			delete [] buffer;
			delete host_info;
			return 0;
		} else if( bytecount == 0) {
			cout << "[@] Connection closed from " + remote_info << endl;
			delete [] buffer;
			delete host_info;
			return 0;
		}

		/* Data to send */
		string data(buffer);
		/* Put extra information */
		data = local_info + "->" + remote_info + ":" + data;
		/* Send the data back to the client */
		if((sendcount = send(remote_sock, data.c_str(), data.size(), 0))== -1){
			string message = "[@] Error sending data to client " + remote_info;
			perror(message.c_str());
			delete [] buffer;
			delete host_info;
			return 0;
		}

    }

    return 0;
}

HostInfo::~HostInfo() {
	/* Remove the connection information from the static map */
	pthread_mutex_lock(&mutex);
	connections.erase(remote_info);
	pthread_mutex_unlock(&mutex);
}
