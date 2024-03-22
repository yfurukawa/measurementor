//
//  MultipliableWithNumber.h
//  DomainPrimitive
//
//  Created by Yoshihiro Furukawa on 2023/11/25.
//

#ifndef MultipliableWithNumber_h
#define MultipliableWithNumber_h

template< typename Derived >
struct MultipliableWithNumber
{
    friend Derived& operator*=( Derived& lhs, double rhs ) {
        lhs.get() *= rhs;
        return lhs;
    }
    
    friend Derived operator*( Derived const& lhs, double rhs ) {
        return Derived{ lhs.get() * rhs };
    }
    
    friend Derived operator*( double lhs, Derived const& rhs ) {
        return Derived{ lhs * rhs.get() };
    }
};

#endif /* MultipliableWithNumber_h */
