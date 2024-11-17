#include <iostream>
#include <vector>

using namespace std;

void permutation(int n, int left, vector<int>& result, vector<bool>& used){
    if(left == n){
        for(int x: result){
            cout << x << " ";
        }
        cout << "\n";
        return;
    }
    for(int i=1; i<=n; i++){
        if(used[i]){ continue; }
        used[i] = true;
        result[left] = i;
        permutation(n, left+1, result, used);
        used[i] = false;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> result(n);
    vector<bool> used(n, false);
    permutation(n, 0, result, used);
}