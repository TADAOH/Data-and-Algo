#ifndef ZZZ_MAP_AVL_HEAD_HEAD
#define ZZZ_MAP_AVL_HEAD_HEAD

#include <iostream>

namespace zzz {
template <typename KeyT, typename ValueT, typename Comp = std::less<KeyT>>    
class map_avl {
    protected:    
        typedef std::pair<KeyT, ValueT> MapT;
        class  node {
            friend class map_avl;
            protected:
                MapT data;
                node* left;
                node* right;
                node* parent;
                int height;
                
                node():
                    data( MapT() ), left(NULL), right(NULL), parent(NULL), height(0)  {}
                node(const MapT& m):
                    data( m ), left(NULL), right(NULL), parent(NULL), height(0) {}
                node(const MapT& m, node* l, node* r, node* p):
                    data( m ), left(l), right(r), parent(p) { set_height(); } 

                void set_height(){
                    this->height = 1 + std::max( get_height(this->left), get_height(this->right) );
                }
                int get_height(node* n){
                    return n ? n->height : -1;
                }
                int balance_value(){
                    return get_height(this->right) - get_height(this->left);
                }
                void set_left(node* n){
                    this->left = n;
                    if(n){ this->left->parent = this; }
                }
                void set_right(node* n){
                    this->right = n;
                    if(n){ this->right->parent = this; }
                }
                void set_parent(node* _parent, node* n){
                    if(_parent){
                        if(_parent->left == n) {
                            _parent->left = this;
                        }else{
                            _parent->right = this;
                        }
                    }
                    this->parent = _parent;
                }                    
        };

        class tree_iterator {
            protected:
                node* ptr;
                map_avl* container;
            public:
                tree_iterator(node* p, map_avl* c):
                    ptr(p), container(c) {}
                
                MapT& operator * (){
                    return ptr->data;
                }
                MapT* operator -> (){
                    return &(ptr->data);
                }
                bool  operator == (const tree_iterator& other){
                    return ptr == other.ptr;
                }
                bool  operator != (const tree_iterator& other){
                    return ptr != other.ptr;
                }

                tree_iterator& operator++(){
                    if(!ptr){
                        ptr = container->find_min_node();
                        return *this;
                    }
                    if(ptr->right){
                        ptr = ptr->right;
                        while(ptr->left){
                            ptr = ptr->left;
                        }
                    }else{
                        node* _parent = ptr->parent;
                        while(_parent && _parent->right == ptr){
                            ptr  = _parent;
                            _parent = _parent->parent;
                        }
                        ptr = _parent;
                    }
                    return *this;                   
                }
                tree_iterator& operator--(){
                    if(!ptr){
                        ptr = container->find_max_node();
                        return *this;
                    }
                    if(ptr->left){
                        ptr = ptr->left;
                        while(ptr->right){
                            ptr = ptr->right;
                        }
                    }else{
                        node* _parent = ptr->parent;
                        while(_parent && _parent->left == ptr){
                            ptr = _parent;
                            _parent = _parent->parent;
                        }
                        ptr  = _parent;
                    }
                    return *this;                  
                }
                tree_iterator operator++(int){
                    tree_iterator tmp(*this);
                    operator++();
                    return tmp;                    
                }   
                tree_iterator operator--(int){
                    tree_iterator tmp(*this);
                    operator--();
                    return tmp;                    
                }    
        };   

        class reverse_tree_iterator {
            protected:
                node* ptr;
                map_avl* container;
            public:
                reverse_tree_iterator(node* p, map_avl* c): ptr(p), container(c) {}

                MapT& operator * () { return ptr->data; }
                MapT* operator -> () { return &(ptr->data);}
                bool  operator == (const reverse_tree_iterator& other) { return ptr == other.ptr; }
                bool  operator != (const reverse_tree_iterator& other) { return ptr != other.ptr; }   

                reverse_tree_iterator& operator++() {
                    if(!ptr){
                        ptr = container->find_max_node();
                        return *this;
                    }
                    if(ptr->left){
                        ptr = ptr->left;
                        while(ptr->right){
                            ptr = ptr->right;
                        }
                    }else{
                        node* _parent = ptr->parent;
                        while(_parent && _parent->left == ptr){
                            ptr = _parent;
                            _parent = _parent->parent;
                        }
                        ptr  = _parent;
                    }
                    return *this;
                }
                reverse_tree_iterator& operator--() {
                    if(!ptr){
                        ptr = container->find_min_node();
                        return *this;
                    }
                    if(ptr->right){
                        ptr = ptr->right;
                        while(ptr->left){
                            ptr = ptr->left;
                        }
                    }else{
                        node* _parent = ptr->parent;
                        while(_parent && _parent->right == ptr){
                            ptr  = _parent;
                            _parent = _parent->parent;
                        }
                        ptr = _parent;
                    }
                    return *this;                    
                }
                reverse_tree_iterator operator++(int) {
                    reverse_tree_iterator temp = (*this);
                    ++(*this);
                    return temp;                    
                }  
                reverse_tree_iterator operator--(int){
                    reverse_tree_iterator temp = (*this);
                    --(*this);
                    return temp;                    
                }  
        };

    protected:
        node* map_root;
        size_t map_size;
        Comp lesser;
        
        int compare(const KeyT& k1, const KeyT& k2){
            if(lesser(k1, k2)) { return -1; }
            if(lesser(k2, k1)) { return 1; }
            return 0;
        }
        node* find_node(const KeyT& key,node* pointer, node*& _parent){
            while(pointer){
                int not_equal = compare(key, pointer->data.first);
                if(!not_equal){ return pointer; }
                _parent = pointer;
                pointer = not_equal < 0 ? pointer->left : pointer->right;
            }
            return NULL;
        }
        node* find_min_node(){
            node* n = map_root;
            if(!n){ return n; }
            while(n->left) { n = n->left; }
            return n;
        }
        node* find_max_node(){
            node* n = map_root;
            if(!n){ return n; }
            while(n->right) { n = n->right; }
            return n;
        }
        node* &child_link(node* _parent, const KeyT& k){
            if(!_parent) { return map_root; }
            return lesser(k, _parent->data.first) ? _parent->left : _parent->right;
        }
        node* insert_node(const KeyT& key) {
            node* _parent = NULL;
            node* that_node = find_node(key, map_root, _parent);
            if(!that_node){
                ++map_size;
                that_node = new node(std::make_pair(key, ValueT()), NULL, NULL, _parent);
                child_link(_parent, key) = that_node;
                while(_parent) {
                    _parent = rebalance(_parent);
                    map_root = _parent;
                    _parent = _parent->parent;
                }
            }
            return that_node;            
        }
        void erase_node(const KeyT& key, node* n) {
            while(n){
                int not_equal = compare(key, n->data.first);
                if(not_equal < 0) {
                    n = n->left;
                }else if(not_equal > 0) {
                    n = n->right;
                }else{
                    if(n->left && n->right){
                        node* replace = n->right;
                        while(replace->left){
                            replace = replace->left;
                        }
                        n->data = replace->data;
                        n = replace;
                    }
                    node* temp = n;
                    node* _parent  = n->parent;
                    node* replace = (!n->left ? n->right : n->left);
                    --map_size;
                    if(_parent) {
                        if(_parent->left == n){
                            _parent->left = replace;
                        }else{
                            _parent->right = replace;
                        }
                    }else{
                        map_root = replace;
                    }
                    if(replace){
                        replace->parent = _parent;
                    }
                    while(_parent){
                        _parent = rebalance(_parent);
                        map_root = _parent;
                        _parent = _parent->parent;
                    }
                    delete temp;
                    break;
                }
            }            
        }
        void delete_all_nodes(node *n){
            if(!n){ return; }
            delete_all_nodes(n->left);
            delete_all_nodes(n->right);
            delete n;            
        }
        node* rebalance(node* n){
            if(!n){ return n; }
            int balance_factor = n->balance_value();
            if(balance_factor > 1) {
                if(n->right->balance_value() < 0){
                    n->set_right( rotate_left_child(n->right) );
                }
                n = rotate_right_child(n);
            } else if (balance_factor < -1) {
                if(n->left->balance_value() > 0){
                    n->set_left( rotate_right_child(n->left) );
                }
                n = rotate_left_child(n);
            }
            
            n->set_height();
            return n;
        }
        node* rotate_left_child(node* old_root){
            node* new_root = old_root->left;
            new_root->set_parent(old_root->parent, old_root);
            old_root->set_left(new_root->right);
            new_root->set_right(old_root);

            new_root->right->set_height();
            new_root->set_height();
            return new_root;            
        } 
        node* rotate_right_child(node* old_root){
            node* new_root = old_root->right;
            new_root->set_parent(old_root->parent, old_root);
            old_root->set_right(new_root->left);
            new_root->set_left(old_root);

            new_root->left->set_height();
            new_root->set_height();

            return new_root;            
        }
        node* copy(node* src, node* _parent) {
            if(!src){ return NULL; }
            node* _copy = new node(src->data, NULL, NULL, _parent);
            _copy->height = src->height;
            _copy->left = copy(src->left, _copy);
            _copy->right = copy(src->right, _copy);
            return _copy;
        }
        // debug
        void show_left_right(node* n);
        void pre_order(node* r);

    public:
        typedef tree_iterator iterator;
        typedef reverse_tree_iterator reverse_iterator;

        map_avl(const Comp& c = Comp()):
            map_root(NULL), map_size(0), lesser(c) {} 
        ~map_avl(){
            clear();
        }
        map_avl(const map_avl<KeyT,ValueT,Comp> & other){
            map_size = other.map_size;
            lesser = other.lesser;
            map_root = copy(other.map_root, NULL);            
        }
        map_avl<KeyT,ValueT,Comp>& operator = (map_avl<KeyT,ValueT,Comp> other){
            std::swap(this->map_root, other.map_root);
            std::swap(this->lesser, other.lesser);
            std::swap(this->map_size, other.map_size);
            return *this;            
        }

        void clear(){
            delete_all_nodes(map_root);
            map_root = NULL;
            map_size = 0;            
        }
        size_t size(){
            return map_size;
        }
        bool empty(){
            return map_size == 0;
        }
        
        iterator begin(){
            return iterator(find_min_node(), this);
        }
        iterator end(){
            return iterator(NULL, this);
        }
        iterator find(const KeyT &k){
            node* _parent = NULL;
            return iterator(find_node(k, map_root, _parent), this);
        }
        reverse_iterator rbegin() {
            return reverse_iterator(find_max_node(), this);
        }
        reverse_iterator rend() {
            return reverse_iterator(NULL, this);
        }

        ValueT& operator[](const KeyT& key){
            node* that_node =  insert_node(key);
            return that_node->data.second;            
        }
        std::pair<iterator, bool> insert(const MapT& key_val){
            size_t init = map_size;
            node* that_node = insert_node(key_val.first);
            if(map_size == init) { return std::make_pair( iterator(that_node, this),false ); }
            that_node->data.second = key_val.second;
            return std::make_pair(iterator(that_node, this), true);          
        }
        bool erase(const KeyT& k){
            size_t init = map_size;
            erase_node(k, map_root);
            return init > map_size;
        } 
    
        // debug
        void show_structure(){ // pre-order travesal
            pre_order(map_root);
        }
};
}

template <typename KeyT, typename ValueT, typename Comp>
void zzz::map_avl<KeyT, ValueT, Comp>::pre_order(typename zzz::map_avl<KeyT, ValueT, Comp>::node* n) {
    if(!n){ return; }
    show_left_right(n);
    pre_order(n->left);
    pre_order(n->right);
}


template <typename KeyT, typename ValueT, typename Comp>
void zzz::map_avl<KeyT, ValueT, Comp>::show_left_right(typename zzz::map_avl<KeyT, ValueT, Comp>::node* r) {
    if(r->left){
        auto [a, b] = r->left->data;
        std::cout << "<" << a << "," << ">";
    }else{
        std::cout << "<none>";
    }
    std::cout << "[" << r->data.first << ", p = ";
    std::cout << r->height;
    if(r->parent){
        std::cout << r->parent->data.first;
    }else{
        std::cout << "_";
    }
    std::cout << "]";
    if(r->right){
        auto [a, b] = r->right->data;
        std::cout << "<" << a << ">";
    }else{
        std::cout << "<none>";
    }
    std::cout << "\n";
}


#endif
