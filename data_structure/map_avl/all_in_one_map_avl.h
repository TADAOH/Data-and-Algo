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
                void set_parent(node* papa, node* n){
                    if(papa){
                        if(papa->left == n) {
                            papa->left = this;
                        }else{
                            papa->right = this;
                        }
                    }
                    this->parent = papa;
                }                    
        };

        class tree_iterator {
            protected:
                node* ptr;
            public:
                tree_iterator():
                    ptr(NULL) {}
                tree_iterator(node* p):
                    ptr(p) {}
                
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
                        return *this;
                    }
                    if(ptr->right){
                        ptr = ptr->right;
                        while(ptr->left){
                            ptr = ptr->left;
                        }
                    }else{
                        node* papa = ptr->parent;
                        while(papa && papa->right == ptr){
                            ptr  = papa;
                            papa = papa->parent;
                        }
                        ptr = papa;
                    }
                    return *this;                   
                }
                tree_iterator& operator--(){
                    if(!ptr){
                        return *this;
                    }
                    if(ptr->left){
                        ptr = ptr->left;
                        while(ptr->right){
                            ptr = ptr->right;
                        }
                    }else{
                        node* papa = ptr->parent;
                        while(papa && papa->left == ptr){
                            ptr = papa;
                            papa = papa->parent;
                        }
                        ptr  = papa;
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
            public:
                reverse_tree_iterator(): ptr(NULL) {}
                reverse_tree_iterator(node* p): ptr(p) {}

                MapT& operator * () { return ptr->data; }
                MapT* operator -> () { return &(ptr->data);}
                bool  operator == (const reverse_tree_iterator& other) { return ptr == other.ptr; }
                bool  operator != (const reverse_tree_iterator& other) { return ptr != other.ptr; }   

                reverse_tree_iterator& operator++() {
                    if(!ptr){
                        return *this;
                    }
                    if(ptr->left){
                        ptr = ptr->left;
                        while(ptr->right){
                            ptr = ptr->right;
                        }
                    }else{
                        node* papa = ptr->parent;
                        while(papa && papa->left == ptr){
                            ptr = papa;
                            papa = papa->parent;
                        }
                        ptr  = papa;
                    }
                    return *this;
                }
                reverse_tree_iterator& operator--() {
                    if(!ptr){
                        return *this;
                    }
                    if(ptr->right){
                        ptr = ptr->right;
                        while(ptr->left){
                            ptr = ptr->left;
                        }
                    }else{
                        node* papa = ptr->parent;
                        while(papa && papa->right == ptr){
                            ptr  = papa;
                            papa = papa->parent;
                        }
                        ptr = papa;
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
        node* find_node(const KeyT& k,node* pointer, node* &parent){
            while(pointer){
                int not_equal = compare(k, pointer->data.first);
                if(!not_equal){ return pointer; }
                parent = pointer;
                pointer = not_equal < 0 ? pointer->left : pointer->right;
            }
            return NULL;
        }
        node* find_min_node(node* r){
            if(!r){ return r; }
            while(r->left) { r = r->left; }
            return r;
        }
        node* find_max_node(node* r){
            if(!r){ return r; }
            while(r->right) { r = r->right; }
            return r;
        }
        node* &child_link(node* parent, const KeyT& k){
            if(!parent) { return map_root; }
            return lesser(k, parent->data.first) ? parent->left : parent->right;
        }
        node* erase_node(const KeyT &k, node*& r){
            if(!r){ return r; }
            int not_equal = compare(k, r->data.first);
            if(not_equal < 0) {
                r->set_left(erase_node(k, r->left));
            }else if(not_equal > 0) {
                r->set_right(erase_node(k, r->right));
            }else{
                if(!r->left || !r->right) {
                    node* temp_node = r;
                    r = (!r->left ? r->right : r->left);
                    delete temp_node;
                    map_size--;
                }else{
                    node* replace_node = r->right;
                    while(replace_node->left) {
                        replace_node = replace_node->left;
                    }
                    r->data = replace_node->data;
                    r->set_right(erase_node(replace_node->data.first, r->right));
                }
            }
            return r;
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

    public:
        typedef tree_iterator iterator;
        typedef reverse_tree_iterator reverse_iterator;

        map_avl(const Comp& c = Comp()):
            map_root(NULL), map_size(0), lesser(c) {} 
        ~map_avl(){
            clear();
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
            return iterator(find_min_node(map_root));
        }
        iterator end(){
            return iterator();
        }
        iterator find(const KeyT &k){
            node* parent = NULL;
            return iterator(find_node(k, map_root, parent));
        }
        reverse_iterator rebind() {
            return reverse_iterator(find_max_node(map_root));
        }
        reverse_iterator rend() {
            return reverse_iterator();
        }

        ValueT& operator[](const KeyT& key){
            node* papa = NULL;
            node* that_node = find_node(key, map_root, papa);
            if(!that_node) {
                ++map_size;
                that_node = new node(std::make_pair(key, ValueT()), NULL, NULL, papa);
                child_link(papa, key) = that_node;
                while(papa) {
                    papa = rebalance(papa);
                    map_root = papa;                   
                    papa = papa->parent;
                }
            }
            return that_node->data.second;            
        }
        std::pair<iterator, bool> insert(const MapT& key_val){
            bool success = false;
            node* papa = NULL;
            node* that_node = find_node(key_val.first, map_root, papa);
            if(!that_node) {
                success = true;
                ++map_size;
                that_node = new node(key_val, NULL, NULL, papa);
                child_link(papa, key_val.first) = that_node;

                while(papa) {
                    papa = rebalance(papa);
                    map_root = papa;
                    papa = papa->parent;
                }
            }
            return std::make_pair(iterator(that_node), success);           
        }
        bool erase(const KeyT& k){
            int init = map_size;
            erase_node(k, map_root);
            return init != map_size;
        } 
    
};
}

#endif