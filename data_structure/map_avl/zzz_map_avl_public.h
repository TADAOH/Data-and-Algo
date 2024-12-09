#ifndef ZZZ_MAP_AVL_PUBLIC
#define ZZZ_MAP_AVL_PUBLIC

#include "zzz_hh_map_avl.h"

/*
size_t size();
bool empty();
void clear();

iterator begin();
iterator end();
reverse_iterator rbegin();
reverse_iterator rend();

iterator find(const KeyT &key);
ValueT& operator[](const KeyT& key);
std::pair<iterator, bool> insert(const MapT& key_val);
bool erase(const KeyT& k);
*/

namespace zzz {

template <typename KeyT, typename ValueT, typename Comp>
size_t map_avl<KeyT, ValueT, Comp>::size() {
    return map_size;
}


template <typename KeyT, typename ValueT, typename Comp>
bool map_avl<KeyT, ValueT, Comp>::empty() {
    return map_size == 0;
}


template <typename KeyT, typename ValueT, typename Comp>
void map_avl<KeyT, ValueT, Comp>::clear(){
    delete_all_nodes(map_root);
    map_root = NULL;
    map_size = 0;
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::iterator  map_avl<KeyT, ValueT, Comp>::begin() {
    return iterator(find_min_node(), this);
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::reverse_iterator  map_avl<KeyT, ValueT, Comp>::rbegin() {
    return reverse_iterator(find_max_node(), this);
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::iterator map_avl<KeyT, ValueT, Comp>::end(){
    return iterator(NULL, this);
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::reverse_iterator map_avl<KeyT, ValueT, Comp>::rend(){
    return reverse_iterator(NULL, this);
}


template <typename KeyT, typename ValueT, typename Comp>
typename map_avl<KeyT, ValueT, Comp>::iterator map_avl<KeyT, ValueT, Comp>::find(const KeyT& key) {
    node* parent = NULL;
    return iterator(find_node(key, map_root, parent), this);
}


template <typename KeyT, typename ValueT, typename Comp>
ValueT& map_avl<KeyT, ValueT, Comp>::operator [] (const KeyT& key) {
    node* that_node =  insert_node(key);
    return that_node->data.second;
}


template <typename KeyT, typename ValueT, typename Comp>
std::pair<typename map_avl<KeyT, ValueT, Comp>::iterator, bool>  map_avl<KeyT, ValueT, Comp>::insert(const MapT& key_val) {
    size_t init = map_size;
    node* that_node = insert_node(key_val.first);
    if(map_size == init) { return std::make_pair( iterator(that_node, this),false ); }
    that_node->data.second = key_val.second;
    return std::make_pair(iterator(that_node, this), true);
}


template <typename KeyT, typename ValueT, typename Comp>
bool map_avl<KeyT, ValueT, Comp>::erase(const KeyT& key) {
    int init = map_size;
    erase_node(key, map_root);
    return init != map_size;
}


}
#endif
