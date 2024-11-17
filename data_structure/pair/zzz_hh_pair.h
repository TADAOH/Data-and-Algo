#ifndef ZZZ_PAIR_HEAD_HEAD
#define ZZZ_PAIR_HEAD_HEAD

namespace zzz {
    template <typename F, typename S>
    class pair {
    public:
        F first;
        S second;

        pair();
        pair(const F& f, const S& s);

        bool operator == (const pair<F, S>& other) const;
        bool operator != (const pair<F, S>& other) const;
        bool operator <  (const pair<F, S>& other) const;
        bool operator >  (const pair<F, S>& other) const;
        bool operator >= (const pair<F, S>& other) const;
        bool operator <= (const pair<F, S>& other) const;
    };
}

#endif