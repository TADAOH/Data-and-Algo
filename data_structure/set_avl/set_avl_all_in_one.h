#ifndef ZZZ_SET_AVL_HEAD_HEAD
#define ZZZ_SET_AVL_HEAD_HEAD

#include <iostream>

namespace zzz {
template <typename KeyT, typename Comp = std::less<KeyT>>
class set_avl {
    protected:
        class node {
            friend class set_avl;
            protected:
                KeyT data;
                node* left;
                node* right;
                node* parent;
                int height;

                node(): data( KeyT() ), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
                node(const KeyT& k): data(k), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
                node(const KeyT& k, node* l, node* r, node* p): data(k), left(l), right(r), parent(p) {
                    set_height();
                } 

                int get_height(node* n) {
                    return n ? n->height : -1;
                }
                void set_height() {
                    int left_h = get_height(this->left);
                    int right_h = get_height(this->right);
                    this->height = 1 + (left_h > right_h ? left_h : right_h);
                }
                int balance_value() {
                    return get_height(this->right) - get_height(this->left);
                }
                void set_left(node* n) {
                    this->left = n;
                    if(n) { n->parent = this; }
                }           
                void set_right(node* n) {
                    this->right = n;
                    if(n) { n->parent = this; }
                }            
                void set_parent(node* _parent, node* n) {
                    this->parent = _parent;
                    if(_parent){
                        if(_parent->left == n){
                            _parent->left = this;
                        }else{
                            _parent->right = this;
                        }
                    }
                }
        };
         
        class tree_iterator {
            protected:
                node* ptr;
                set_avl* container;
            public:
                tree_iterator(node* p, set_avl* c): ptr(p), container(c) {}            

                KeyT& operator * () { return ptr->data; }          
                KeyT* operator -> () { return &(ptr->data); }            
                bool  operator == (const tree_iterator& other) { return ptr == other.ptr; }        
                bool  operator != (const tree_iterator& other) { return ptr != other.ptr; }            
                
                tree_iterator& operator++() {
                    if(!ptr) {
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
                            ptr = _parent;
                            _parent = _parent->parent;
                        }
                        ptr = _parent;
                    }
                    return *this;
                }
                tree_iterator& operator--() {
                    if(!ptr) {
                        ptr = container->find_max_node();
                        return *this;
                    }
                    if(ptr->left) {
                        ptr = ptr->left;
                        while(ptr->right) {
                            ptr = ptr->right;
                        }
                    } else {
                        node* _parent = ptr->parent;
                        while(_parent && _parent->left == ptr){
                            ptr = _parent;
                            _parent = _parent->parent;
                        }
                        ptr = _parent;
                    }
                    return *this;
                }
                tree_iterator operator++(int) {
                    tree_iterator temp = *this;
                    ++(*this);
                    return temp;
                } 
                tree_iterator operator--(int) {
                    tree_iterator temp = *this;
                    --(*this);
                    return temp;
                }
        };

        class reverse_tree_iterator {
            protected:
                node* ptr;
                set_avl* container;
            public:
                reverse_tree_iterator(node* p, set_avl* c): ptr(p), container(c) {}

                KeyT& operator * () { return ptr->data; }
                KeyT* operator -> () { return &(ptr->data); }
                bool  operator == (const reverse_tree_iterator& other) { return ptr == other.ptr; }
                bool  operator != (const reverse_tree_iterator& other) { return ptr != other.ptr; }   

                reverse_tree_iterator& operator++() {
                    if(!ptr){
                        ptr = container->find_max_node();
                        return *this;
                    }
                    if(ptr->left) {
                        ptr = ptr->left;
                        while(ptr->right) {
                            ptr = ptr->right;
                        }
                    } else {
                        node* _parent = ptr->parent;
                        while(_parent && _parent->left == ptr){
                            ptr = _parent;
                            _parent = _parent->parent;
                        }
                        ptr = _parent;
                    }
                    return *this;                    
                }
                reverse_tree_iterator& operator--() {
                    if(!ptr) {
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
                            ptr = _parent;
                            _parent = _parent->parent;
                        }
                        ptr = _parent;
                    }
                    return *this;                    
                }
                reverse_tree_iterator operator++(int) {
                    reverse_tree_iterator temp = *this;
                    ++(*this);
                    return temp;
                }   
                reverse_tree_iterator operator--(int) {
                    reverse_tree_iterator temp = *this;
                    --(*this);
                    return temp;
                }   
        };

    protected:
        node* set_root;
        size_t set_size;
        Comp lesser;

        int compare(const KeyT& k1, const KeyT& k2) {
            if(lesser(k1, k2)) { return -1; }
            if(lesser(k2, k1)) { return 1; }
            return 0;
        }         
        node* find_node(const KeyT& k,node* n, node* &_parent) {
            while(n){
                int not_equal = compare(k, n->data);
                if(!not_equal){
                    return n;
                }
                _parent = n;
                n = (not_equal < 0 ? n->left : n->right);
            }
            return nullptr;
        }        
        node* find_min_node() {
            node* n = set_root;
            if(!n){ return n; }
            while(n->left) {
                n = n->left;
            }
            return n;
        }           
        node* find_max_node() {
            node* n = set_root;
            if(!n) { return n; }
            while(n->right){
                n = n->right;
            }
            return n;
        }          
        node*& child_link(node* _parent, const KeyT& key) {
            if(!_parent){ return set_root; }
            return lesser(key, _parent->data) ? _parent->left : _parent->right;
        }           
        node* erase_node(const KeyT &key, node*& n) {
            if(!n){ return n; }
            int not_equal = compare(key, n->data);
            if(not_equal < 0) {
                n->set_left(erase_node(key, n->left));
            }else if(not_equal > 0) {
                n->set_right(erase_node(key, n->right));
            }else{
                node* temp = n;
                if (!n->left) {
                    n = n->right;
                    delete temp;
                    --set_size;
                } else if (!n->right) {
                    n = n->left;
                    delete temp;
                    --set_size;
                } else {
                    node* replace_node = n->right;
                    while (replace_node->left) {
                        replace_node = replace_node->left;
                    }
                    n->data = replace_node->data;
                    n->set_right( erase_node(replace_node->data, replace_node) );
                }
            }     

            if(n) {
                n = rebalance(n);
                n->set_height();
            }
            // n = rebalance(n);
            // n->set_height();
            return n;       
        }
        void erase_node_iterate(const KeyT& key) {
            node* n = set_root;
            node* _parent = nullptr;
            while(n){
                int not_equal = compare(key, n->data);
                if(not_equal < 0) {
                    n = n->left;
                } else if (not_equal > 0) {
                    n = n->right;
                }else{
                    --set_size;
                    if(n->left && n->right){
                        node* replace = n->right;
                        while(replace->left){
                            replace = replace->left;
                        }
                        n->data = replace->data;
                        n = replace; 
                    }
                    node* temp = n;
                    _parent = n->parent;
                    node* replace = (!n->left ? n->right : n->left);
                    if(_parent) {
                        if(_parent->left == n) {
                            _parent->left = replace;
                        }else{
                            _parent->right = replace;
                        }
                    }else{
                        set_root = replace;
                    }
                    if(replace) {
                        replace->parent = _parent;
                    }
                    delete temp;
                    break;
                }
            }
            while(_parent) {
                _parent = rebalance(_parent);
                set_root = _parent;
                _parent = _parent->parent;
            }
        }
        void delete_all_nodes(node *n) {
            if(!n){ return; }
            delete_all_nodes(n->left);
            delete_all_nodes(n->right);
            delete n;
        }          
        node* rebalance(node* n) {
            int balance_factor = n->balance_value();
// std::cout << "\n" << n->data << ", lh = " << n->get_height(n->left) << ", rh = " << n->get_height(n->right) << ", ";
// std::cout << "balance factor = " << balance_factor << "\n";
            if(balance_factor > 1) {
                if(n->right->balance_value() < 0) {
                    n->set_right( rotate_left_child(n->right) );
                }
                n = rotate_right_child(n);
            } else if(balance_factor < -1) {
                if(n->left->balance_value() > 0) {
                    n->set_left( rotate_right_child(n->left) );
                }
                n = rotate_left_child(n);
            }
            n->set_height();
            return n;
        }          
        node* rotate_left_child(node* old_root) {
            node* new_root = old_root->left;
            new_root->set_parent(old_root->parent, old_root);
            old_root->set_left(new_root->right);
            new_root->set_right(old_root);

            new_root->right->set_height();
            new_root->set_height();
            return new_root;
        }      
        node* rotate_right_child(node* old_root) {
            node* new_root = old_root->right;
            new_root->set_parent(old_root->parent, old_root);
            old_root->set_right(new_root->left);
            new_root->set_left(old_root);

            new_root->left->set_height();
            new_root->set_height();
            return new_root;
        }             
        node* copy(node* src) {
            if(!src) {
                return nullptr;
            }
            node* _copy = new node(src->data);
            _copy->height = src->height;
            _copy->set_left(copy(src->left));
            _copy->set_right(copy(src->right));
            return _copy; 
        }

    public:
        typedef tree_iterator iterator;
        typedef reverse_tree_iterator reverse_iterator; 

        set_avl(const Comp& c = Comp()):
            set_root(nullptr), set_size(0), lesser(c) {}         
        ~set_avl() {
            clear();
        }           
        set_avl(const set_avl<KeyT,Comp> & other) {
            set_size = other.set_size;
            lesser = other.lesser;
            set_root = copy(other.set_root);
        }    
        set_avl<KeyT,Comp>& operator = (set_avl<KeyT,Comp> other) {
            std::swap(set_root, other.set_root);
            std::swap(set_size, other.set_size);
            std::swap(lesser, other.lesser);
        }
        
        void clear() {
            delete_all_nodes(set_root);
            set_root = nullptr;
            set_size = 0;
        }      
        bool empty() {
            return set_size == 0;
        }          
        size_t size() {
            return set_size;
        }            
        
        iterator find(const KeyT &key) {
            node* _parent = nullptr;
            return iterator( find_node(key, set_root, _parent) );
        }           
        iterator begin() {
            return iterator( find_min_node(), this );
        }          
        iterator end() { 
            return iterator(nullptr, this); 
        }          
        reverse_iterator rbegin() {
            return reverse_iterator( find_max_node(), this );
        }            
        reverse_iterator rend() {
            return reverse_iterator(nullptr, this);
        }            
              
        std::pair<iterator, bool> insert(const KeyT& key) {
            node* _parent = NULL;
            node* insert_node = find_node(key, set_root, _parent);
            bool success = (insert_node == nullptr);
            if(success) {
                ++set_size;
                insert_node = new node(key, nullptr, nullptr, _parent);
                child_link(_parent, key) = insert_node;
                while(_parent){
                    _parent = rebalance(_parent);
                    set_root = _parent;
                    _parent = _parent->parent;
                }
            }
            return std::make_pair(iterator(insert_node, this), success);
        }          
        bool erase(const KeyT& key) {
            size_t init = set_size;
            // erase_node(key, set_root);
            erase_node_iterate(key);
            return init != set_size;
        }


        void show_structor(node* n){
            if(n->left){
                std::cout << "<" << n->left->data << ">";
            }else{
                std::cout << "<_>";
            }
            std::cout << "[" << n->data << ": p = ";
            // std::cout << n->height;
            if(n->parent){
                std::cout << n->parent->data;
            }else{
                std::cout << "_";
            }
            std::cout << "]";
            if(n->right){
                std::cout << "<" << n->right->data << ">";
            }else{
                std::cout << "<_>";
            }
            std::cout << "\n";
        }
        void pre_order(node* n){
            if(!n){ return; }
            show_structor(n);
            pre_order(n->left);
            pre_order(n->right);
        }
        void debug(){
            pre_order(set_root);
        }
};

}

#endif