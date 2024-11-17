#include <vector>

// find max element and put it in the back
template <typename T, typename C = std::less<T>>
void selection_sort(std::vector<T>& arr, C less = C()){
    for(size_t back_index = arr.size()-1; back_index > 0; --back_index){
        
        size_t max_index = back_index; // find the index of the max element
        
        for(size_t i=0; i<back_index; ++i){
            if(less(arr[max_index], arr[i])){ max_index = i; }
        }
        
        std::swap(arr[max_index], arr[back_index]); // put the max element to the back
    
    }
}
