#include "quicksort.h"



int Quicksort::partition(vector<double>& vec,int start,int end){
    double pivot=vec[end];
    int index=(start-1);

    for(int i=start;i<end;i++){
        if(vec[i]<=pivot){
            index++;
            iter_swap(vec.begin()+index,vec.begin()+i);
        }
    }
    iter_swap(vec.begin()+(index+1),vec.begin()+end);
    return (index+1);
}

void Quicksort::sort(vector<double>& vec, int start,int end){
    if(start<end){
        int index=partition(vec,start,end);

        sort(vec,start,index-1);   //sort lower half
        sort(vec,index+1,end);     //sort upper half
    }
}
