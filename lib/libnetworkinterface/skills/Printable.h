//
//  Printable.h
//  DomainPrimitive
//
//  Created by Yoshihiro Furukawa on 2023/11/25.
//

#ifndef Printable_h
#define Printable_h

template< typename Derived >
struct Printable
{
    friend std::ostream& operator<<( std::ostream& os, const Derived& d )
    {
        os << d.get();
        return os;
    }
};

#endif /* Printable_h */
