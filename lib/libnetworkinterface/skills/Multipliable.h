//
//  Multipliable.h
//  DomainPrimitive
//
//  Created by Yoshihiro Furukawa on 2023/11/25.
//

#ifndef Multipliable_h
#define Multipliable_h

template< typename Derived >
struct Multipliable
{
    friend Derived& operator*=( Derived& lhs, Derived& rhs ) {
        lhs.get() *= rhs.get();
        return lhs;
    }
    
    friend Derived operator*( Derived const& lhs, Derived const& rhs ) {
        return Derived{ lhs.get() * rhs.get() };
    }

};

#endif /* Multipliable_h */
