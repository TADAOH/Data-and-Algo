#include <iostream>
#include <vector>

#include "heap_sort.h"
#include "insertion_sort.h"

using namespace std;

void show_array(vector<char> const& array){
    for(auto x: array){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    int n;
    cin >> n;
    vector<char> array(n);
    for(int i=0; i<n; i++){
        cin >> array[i];
    }
    show_array(array);
    insertion_sort(array, [](const char& a, const char& b){ return a < b; });
    // heap_sort(array, greater<int>()); 
    show_array(array);
}