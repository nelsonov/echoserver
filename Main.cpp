#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cerrno>

#include <fcntl.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "ConnectHandler.h"

using namespace std;

/* How many pending connections will be hold */
const int backlog = 10;

/* Listening flag */
static int listening = 1;

void ctrl_c(int dummy) {
	/* Set listening flag to zero */
	listening = 0;
}

int main(int argv, char** argc){

	/* Check the arguments */

	/* Listening port */
    int host_port= 8080;

    /* Local listening socket */
    int local_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(local_sock == -1){
    	perror("[@] Error initializing server socket: ");
    	exit(1);
    }

    /* Generic integer */
    int *p_int = new int;
    *p_int = 1;

    /* Set sockets options */
    if( (setsockopt(local_sock, SOL_SOCKET, SO_REUSEADDR, p_int, sizeof(int)) == -1 )||
        (setsockopt(local_sock, SOL_SOCKET, SO_KEEPALIVE, p_int, sizeof(int)) == -1 ) ){
    	perror("[@] Error setting server socket options: ");
        delete p_int;
    	exit(1);
    }

    delete p_int;

    /* Local Address structure */
    sockaddr_in my_addr;

    my_addr.sin_family = AF_INET;                           /* Set socket family */
    my_addr.sin_port = htons(host_port);                    /* Set port */
    my_addr.sin_addr.s_addr = INADDR_ANY ;                  /* Set local IP address */
    memset(my_addr.sin_zero, 0, sizeof(my_addr.sin_zero));  /* Fill with zeros */

    /* Bind socket */
    if(bind(local_sock, (sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
    	perror("[@] Error binding socket : ");
    	exit(1);
    }

    /* Listen */
    if(listen(local_sock, backlog) == -1 ){
    	perror("[@] Error listening socket : ");
    	exit(1);
    }

    /* Initialize mutex variable */
    pthread_mutex_init(&HostInfo::mutex, NULL);

    /* Now lets do the server stuff */
    while(listening){

        cout << "[#] Waiting for a connection..." << endl;

        socklen_t addr_size = sizeof(sockaddr_in);
        /* Remote socket descriptor */
        int remote_sock;
        /* Remote Address structure */
        sockaddr_in remote_addr;
        /* Thread ID */
        pthread_t thread_id;

        if(( remote_sock = accept(local_sock, (sockaddr*)&remote_addr, &addr_size))!= -1 ) {
        	/* Get IP address of the host connected */
        	string remote_ip_address(inet_ntoa(remote_addr.sin_addr));
        	/* Get the port of the remote host */
        	unsigned short int remote_port = ntohs(remote_addr.sin_port);
        	/* Get IP address of the local host */
        	string local_ip_address(inet_ntoa(my_addr.sin_addr));
        	/* Get the port of the local host */
        	unsigned short int local_port = ntohs(my_addr.sin_port);
        	/* Print some information */
        	cout << "[#] Received connection from: " << remote_ip_address << ":" << remote_port << endl;

            /* New host info structure */
            HostInfo *host_info = new HostInfo(remote_sock, remote_ip_address, remote_port, local_ip_address, local_port);

            /* Cast to void */
            void* thread_arg = static_cast<void*>(host_info);

            /* Spawn thread */
            pthread_create(&thread_id, 0, &ConnectHandler, thread_arg);
            /* Detach thread */
            pthread_detach(thread_id);
        }
        else
            perror("[@] Error accepting connection: ");

    }

    /* Destroy mutex variable */
    pthread_mutex_destroy(&HostInfo::mutex);

    /* Close local socket descriptor */
    close(local_sock);

}
