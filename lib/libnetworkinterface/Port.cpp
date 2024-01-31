#include <exception>
#include "Port.h"

Port::Port( uint16_t port ) : port_( port )
{
    if( port_ <= 0 || port_ >= 65536 ) {
        std::__throw_out_of_range("port");
    }
}

uint16_t Port::get()
{
    return port_.get();
}
