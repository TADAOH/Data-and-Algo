#ifndef ZZZ_MAP_AVL_NODE
#define ZZZ_MAP_AVL_NODE

/*
node();
node(const MapT& m);
node(const MapT& m, node* l, node* r, node* p);  

void set_height();
int get_height(node* n);
int balance_value();
void set_left(node* n);
void set_right(node* n); 
void set_parent(node* papa, node* n);
*/

#include "zzz_hh_map_avl.h"

namespace zzz {

template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT, ValueT, Comp>::node::node(): 
    data( MapT() ), left(NULL), right(NULL), parent(NULL), height(0)  {}


template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT, ValueT, Comp>::node::node(const typename map_avl<KeyT, ValueT, Comp>::MapT& m): 
    data( m ), left(NULL), right(NULL), parent(NULL), height(0) {}


template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT, ValueT, Comp>::node::node(const typename map_avl<KeyT, ValueT, Comp>::MapT& m, 
                                              typename map_avl<KeyT, ValueT, Comp>::node* l,
                                              typename map_avl<KeyT, ValueT, Comp>::node* r, 
                                              typename map_avl<KeyT, ValueT, Comp>::node* p): 
    data( m ), left(l), right(r), parent(p) { set_height(); }


template <typename KeyT, typename ValueT, typename Comp>
void map_avl<KeyT, ValueT, Comp>::node::set_height() {
    this->height = 1 + std::max( get_height(this->left), get_height(this->right) );
}


template <typename KeyT, typename ValueT, typename Comp>
int map_avl<KeyT, ValueT, Comp>::node::get_height(typename map_avl<KeyT, ValueT, Comp>::node* r) {
    return r ? r->height : -1;
}


template <typename KeyT, typename ValueT, typename Comp>
int map_avl<KeyT, ValueT, Comp>::node::balance_value() {
    return get_height(this->right) - get_height(this->left);
}


template <typename KeyT, typename ValueT, typename Comp>
void map_avl<KeyT, ValueT, Comp>::node::set_left(typename map_avl<KeyT, ValueT, Comp>::node* r) {
    this->left = r;
    if(r){ this->left->parent = this; }
}


template <typename KeyT, typename ValueT, typename Comp>
void map_avl<KeyT, ValueT, Comp>::node::set_right(typename map_avl<KeyT, ValueT, Comp>::node* r) {
    this->right = r;
    if(r){ this->right->parent = this; }
}


template <typename KeyT, typename ValueT, typename Comp>
void map_avl<KeyT, ValueT, Comp>::node::set_parent(node* papa, node* n) {
    if(papa){
        if(papa->left == n) {
            papa->left = this;
        }else{
            papa->right = this;
        }
    }
    this->parent = papa;
}


}
#endif