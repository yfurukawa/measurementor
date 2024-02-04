//
//  Subtractable.h
//  DomainPrimitive
//
//  Created by Yoshihiro Furukawa on 2023/11/25.
//

#ifndef Subtractable_h
#define Subtractable_h

template< typename Derived >
struct Subtractable
{
    friend Derived& operator-=( Derived& lhs, Derived& rhs ) {
        lhs.get() -= rhs.get();
        return lhs;
    }
    
    friend Derived operator-( Derived const& lhs, Derived const& rhs ) {
        return Derived{ lhs.get() - rhs.get() };
    }
};

#endif /* Subtractable_h */
