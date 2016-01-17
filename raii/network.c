#include "Network.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_LEN 255

int main()
{
  Connection con;
  char msg [STR_LEN];
  int msg_len;
  if ( init(&con) != 0 )
  {
    puts("Couldn't activate connection!");
    exit(EXIT_FAILURE);
  }

  if ( connect( &con, "SOME_HOST" ) != 0 )
  {
    puts("Can't connect to host!");
    goto CLEANUP_CONNECTION;
  }
  
  while ( fgets (msg, STR_LEN, stdin) )
  {
    msg_len = strlen(msg);
    if (send(&con, msg, msg_len) != msg_len)
    {
      puts("Couldn't send entire message!");
      goto CLOSE_CONNECTION;
    }
    if ( (msg_len=recv(&con, msg)) < 0)
    {
      puts("Error in recieving");
      goto CLOSE_CONNECTION;
    }
    printf("Server answer: \"%s\"", msg);
  }

CLOSE_CONNECTION:
  disconnect(&con);
CLEANUP_CONNECTION:
  close(&con);

  return 0;
}
