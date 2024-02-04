//
//  Swappable.h
//  DomainPrimitive
//
//  Created by Yoshihiro Furukawa on 2023/11/25.
//

#ifndef Swappable_h
#define Swappable_h

template< typename Derived >
struct Swappable
{
    friend void swap( Derived& lhs, Derived& rhs )
    {
        using std::swap;
        swap( lhs.get(), rhs.get() );
    }
};

#endif /* Swappable_h */
