//
//  Addable.h
//  DomainPrimitive
//
//  Created by Yoshihiro Furukawa on 2023/11/25.
//

#ifndef Addable_h
#define Addable_h

template< typename Derived >
struct Addable
{
    friend Derived& operator+=( Derived& lhs, Derived& rhs ) {
        lhs.get() += rhs.get();
        return lhs;
    }
    
    friend Derived operator+( Derived const& lhs, Derived const& rhs ) {
        return Derived{ lhs.get() + rhs.get() };
    }
};

#endif /* Addable_h */
