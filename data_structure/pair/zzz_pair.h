#ifndef ZZZ_PAIR_HEAD_INCLUDE
#define ZZZ_PAIR_HEAD_INCLUDE

#include "zzz_hh_pair.h"


// constructor
template <typename F, typename S>
zzz::pair<F,S>::pair(): first(), second() {}

template <typename F, typename S>
zzz::pair<F,S>::pair(const F& f, const S& s): first(f), second(s) {}

// comparator
template <typename F, typename S>
bool zzz::pair<F,S>::operator == (const pair<F, S>& other) const {
    return (first == other.first) && (second == other.second);
}

template <typename F, typename S>
bool zzz::pair<F,S>::operator != (const pair<F, S>& other) const {
    return (first != other.first) || (second != other.second);
}

template <typename F, typename S>
bool zzz::pair<F,S>::operator < (const pair<F, S>& other) const {
    return (first < other.first) || (first == other.first && second < other.second);
}

template <typename F, typename S>
bool zzz::pair<F,S>::operator > (const pair<F, S>& other) const {
    return (first > other.first) || (first == other.first && second > other.second);
}

template <typename F, typename S>
bool zzz::pair<F,S>::operator >= (const pair<F, S>& other) const {
    return !((first < other.first) || (first == other.first && second < other.second));
}

template <typename F, typename S>
bool zzz::pair<F,S>::operator <= (const pair<F, S>& other) const {
    return !( (first > other.first) || (first == other.first && second > other.second) );
}

#endif