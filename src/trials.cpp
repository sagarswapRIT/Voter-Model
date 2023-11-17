#include <vector>
#include <iostream>
using namespace std;

int main(){
    std::vector<int> vect;
    vect.push_back(1);
    vect.push_back(2);
    for(int i=0;i<vect.size();i++){
        vect[i]*=-1;
    }
    for(int x:vect)
        cout<<x<<endl;
}