
#include <vector>

template <typename T, typename C>
void fix_down(std::vector<T>& array, size_t parent, size_t size, C less){
    while(true){
        size_t max_i = parent;
        size_t left = 2*parent + 1;
        size_t right = left+1;
        if(left < size && less(array[max_i], array[left])){
            max_i = left;
        }
        if(right < size && less(array[max_i], array[right])){
            max_i = right;
        }
        if(max_i == parent){ break; }
        std::swap(array[max_i], array[parent]);
        parent = max_i;
    }
}

template <typename T, typename C = std::less<T>>
void heap_sort(std::vector<T>& array, C less = C()){
    for(size_t parent=(array.size()-1) / 2; parent > 0; --parent){
        fix_down(array, parent-1, array.size(), less);
    }
    size_t pos = array.size();
    while(pos > 0){
        std::swap(array[0], array[pos-1]);
        --pos;
        fix_down(array, 0, pos, less);
    }
}