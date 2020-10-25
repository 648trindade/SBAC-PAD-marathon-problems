#include <iostream>
#include <iterator>
#include <string>

namespace wscad {

template <typename Iter>
using DistanceType = typename std::iterator_traits <Iter> :: difference_type ;

template <typename Iter> inline auto
pred (Iter i) -> Iter
{
    return (-- i) ;
}

template <typename Iter> inline auto
dist (Iter first, Iter last) -> DistanceType <Iter>
{
    return std::distance (first, last) ;
}

template <typename T> inline auto
min (const T& a, const T& b, const T& c) -> const T&
{
    return std::min (std::min (a, b), c) ;
}

template <typename Iter> auto
lev_dist (Iter f1, Iter l1, Iter f2, Iter l2) -> DistanceType <Iter>
{
    using D = DistanceType <Iter> ;
    D cost {} ;
    if (f1 == l1) return dist (f2, l2) ;
    if (f2 == l2) return dist (f1, l1) ;
    cost = (*pred (l1) == *pred (l2)) ? D (0) : D (1) ;
    return min
        ( lev_dist (f1, pred (l1), f2,       l2 ) + D (1)
        , lev_dist (f1,       l1,  f2, pred (l2)) + D (1)
        , lev_dist (f1, pred (l1), f2, pred (l2)) + cost ) ;
}

} // end namespace wscad

int main (int argc, char const* argv [])
{
    std::string s ;
    std::string t ;
    std::getline (std::cin, s) ;
    std::getline (std::cin, t) ;
    std::cout
        << wscad::lev_dist
                ( std::begin (s)
                , std::end   (s)
                , std::begin (t)
                , std::end   (t) )
        << std::endl ;
}
