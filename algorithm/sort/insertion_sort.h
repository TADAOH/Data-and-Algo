#include <vector>

template <typename T, typename C = std::less<T>>
void insertion_sort(std::vector<T>& array, C less = C()){
    size_t n = array.size();
    for(size_t i=1; i<n; ++i){
        size_t k=i;
        int temp = array[i];
        while(k > 0 && less(temp, array[k-1])){
            array[k] = array[k-1];
            --k;
        }
        array[k] = temp;
    }
}