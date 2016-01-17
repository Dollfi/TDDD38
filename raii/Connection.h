#include "Network.h"

#include <stdexcept>
#include <string>

class Network_Stream_Error: public std::runtime_error
{
public: 
  explicit Network_Stream_Error(std::string const & msg)
    : runtime_error { msg }
  {}
  explicit Network_Stream_Error(char const * msg)
    : runtime_error { msg }
  {}
};

class Connection_Error: public std::runtime_error
{
public:
  using runtime_error::runtime_error; // inheriting constructors
};

// A wrapper for the protocol specific functions. By having a Connection_Wrapper
// object to handle the Connection and calling connect in constructor + disconnect
// in destructor we use RAII (Resource Acquisition Is Initialization). See
// https://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization  and
// http://www.stroustrup.com/bs_faq2.html#finally

class Network_Stream 
{
public:
  explicit Network_Stream(std::string const & server) 
  {
    if ( connect( cw.connection(), server.c_str() ) != 0 )
    {
      throw Network_Stream_Error{"Can't open connection"};
    }
  }

  ~Network_Stream() noexcept
  {
    disconnect(cw.connection());
  }

  void exceptions(bool t = true)
  {
    should_throw = t;
  }

  int send(std::string const & message)
  {
    // using :: to access send at global namespace
    int sent_len { ::send(cw.connection(), message.c_str(), message.length()) };
   
    // will get warning when comparing int and unsigned (possible narrowing conversion)
    // => static_cast
    if (should_throw && sent_len != static_cast<int>(message.length()))
      throw Network_Stream_Error{"Couldn't send entire message"};
    
    return sent_len;
  }

  int recv(std::string & msg)
  {
    char buf[255];
    int len { ::recv(cw.connection(), buf) };
    if ( should_throw && len < 0 )
      throw Network_Stream_Error{"Error in recieving"};

    msg = std::string{buf};
    return len;
  }

private:


  // A nested type to wrapp a Connection pointer. By calling init
  // in constructor and close in destructor we'll remove any leaks
  // of the Connection object 
  class Connection_Wrapper 
  {
  public:

    Connection_Wrapper()
      : con {}
    {
      if ( init(&con) != 0 )
      {
	throw Connection_Error{"Couldn't initialize connection"};
      }
    }

    ~Connection_Wrapper() noexcept
    {
      close(&con);
    }

    Connection * connection() & noexcept
    {
      return &con;
    }

  private:
    Connection con;
  };

  Connection_Wrapper cw {};
  bool should_throw {false};
};
