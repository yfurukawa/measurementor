//
//  Dividable.h
//  DomainPrimitive
//
//  Created by Yoshihiro Furukawa on 2023/11/25.
//

#ifndef Dividable_h
#define Dividable_h

template< typename Derived >
struct Dividable
{
    friend Derived& operator/=( Derived& lhs, Derived& rhs ) {
        lhs.get() /= rhs.get();
        return lhs;
    }
    
    friend Derived operator/( Derived const& lhs, Derived const& rhs ) {
        return Derived{ lhs.get() / rhs.get() };
    }
};

#endif /* Dividable_h */
