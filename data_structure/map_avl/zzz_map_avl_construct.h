#ifndef ZZZ_MAP_AVL_CONSTRUCTOR
#define ZZZ_MAP_AVL_CONSTRUCTOR

#include "zzz_hh_map_avl.h"

/*
map_avl(const Comp& c = Comp());
~map_avl();
map_avl(const map_avl<KeyT,ValueT,Comp> & other);
map_avl<KeyT,ValueT,Comp>& operator=(map_avl<KeyT,ValueT,Comp> other);

node* copy(node* src);
*/

namespace zzz {

template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT, ValueT, Comp>::map_avl(const Comp& c): map_root(NULL), map_size(0), lesser(c) {}


template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT, ValueT, Comp>::~map_avl(){
    clear();
}


template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT, ValueT, Comp>::map_avl(const map_avl<KeyT, ValueT, Comp>& other){
    map_size = other.map_size;
    lesser = other.lesser;
    map_root = copy(other.map_root);
}


template <typename KeyT, typename ValueT, typename Comp>
map_avl<KeyT,ValueT,Comp>& map_avl<KeyT, ValueT, Comp>::operator = (map_avl<KeyT,ValueT,Comp> other){
    std::swap(this->map_root, other.map_root);
    std::swap(this->lesser, other.lesser);
    std::swap(this->map_size, other.map_size);
    return *this;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::node*  map_avl<KeyT, ValueT, Comp>::copy(node* src) {
    if(!src){ return src; }
    node* copy_node = new node(src->data, NULL, NULL, src->parent);
    copy_node->height = src->height;
    copy_node->left = copy(src->left);
    copy_node->right = copy(src->right);
    return copy_node;
}



}

#endif