#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc, char *argv[] ){
    
    float sum = 0;
    float avg;
    if(argc <= 1){
        cout << "Please input numbers to find average.";
    }else{
        for(int i = 1; i < argc ; i++){
            sum += atoi(argv[i]);
        }
        avg = sum/(argc-1);
        cout << "---------------------------------" << endl;
        cout << "Average of " << argc-1 << " numbers = " << avg << endl;
        cout << "---------------------------------";
    }
    return 0;
}

