/* An example of a c-style network connection
 * A connection has to be initialized with init
 * and a connection has to be established with connect before
 * the send and recv functions can be called. A connection will
 * be maintained (server will lock) until disconnect is called.
 */
#ifndef NETWORK_H
#define NETWORK_H

#include <string.h>
#include <stdio.h>
typedef struct
{
/* Some big and complicated structure to represent a connection */
} Connection;

/* Must be called to create a valid connection.
 * return 0 on ok inintialization, negative values for different failures
 */
int init(Connection *) { 
  printf("Connection intitialized\n");
  return 0;
}

/* Must be called with an initialized connection 
 * returns 0 on ok, 1 for invalid address, 2 for unreachable host
*/
int connect(Connection *, char const * host) { 
  printf("Connected to \"%s\"\n", host);
  return 0;
}

/* Must be called to terminate the connection (according to protocol)
 * return 0 on ok, 1 for invalid connection
 */ 
int disconnect(Connection *) { 
  printf("Disconnected!\n");
  return 0; 
}

/* Releases the connection object, must be called on an inactive connection
 */
void close(Connection *) {
  printf("Connection closed\n");
}

/* returns number of bytes sent/recieved.
 * returns negative values for errors
 * must be called with an active connection 
 */
int send(Connection *, char const * /* msg */, int msg_len)
{
  return msg_len;
}
int recv(Connection *, char * msg)
{
  strcpy(msg, "Hello");
  return 6;
}

#endif
