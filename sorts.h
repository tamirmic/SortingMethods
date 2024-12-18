#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <algorithm>
using namespace std;

/*
    This program provides a collection of sorting algorithms implemented for vectors containing integers.
    Each method can specifically sort a part of an array depending on the first and last parameters.
*/

void BubbleSort(vector<int>& items, int first, int last);
void InsertionSort(vector<int>& items, int first, int last);
void MergeSort(vector<int>& items, int first, int last);
void IterativeMergeSort(vector<int>& items, int first, int last);
void QuickSort(vector<int>& items, int first, int last);
void ShellSort(vector<int>& items, int first, int last);

bool ValidParameters(const vector<int>& items, int first, int last){
    return first >= 0 && last < items.size() && first <= last;
}

void BubbleSort(vector<int> &items, int first, int last){
    if(!ValidParameters(items, first, last)){
        return;
    }

    int n = last - first + 1;
    for(int i = 0; i < n - 1; i++){
        for(int j = first; j < last - i; j++){
            if(items[j] > items[j + 1]){
                swap(items[j], items[j + 1]);
            }
        }
    }
}

void InsertionSort(vector<int>& items, int first, int last){
    if(!ValidParameters(items, first, last)){
        return;
    }
    
    for(int i = first + 1; i < last + 1; i++){
        int temp = items[i];
        int j = i;
        while(temp < items[j-1] && j != first){
            items[j] = items[j-1];
            j--;
        }
        items[j] = temp;
    }
}

void Merge(vector<int>& items, int first, int mid, int last){
    int size = last - first + 1;
    vector<int> tmp_arr(size);
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = 0;

    //merge two subarrays
    while((first1 <= last1) && (first2 <= last2)){
        if(items[first1] < items[first2]){
            tmp_arr[index] = items[first1];
            first1++;
        } else{
            tmp_arr[index] = items[first2];
            first2++;
        }
        index++;
    }

    while(first1 <= last1){
        tmp_arr[index] = items[first1];
        first1++;
        index++;
    }

    while(first2 <= last2){
        tmp_arr[index] = items[first2];
        first2++;
        index++;
    }

    //copys merged result back to the original vector
    for(index = 0; index < size; index++){
        items[first] = tmp_arr[index];
        first++;
    }
}

void MergeSort(vector<int>& items, int first, int last){
    if(!ValidParameters(items, first, last)){
        return;
    }
    
    if (first < last){
        int mid = (first + last) / 2;
        MergeSort(items, first, mid);
        MergeSort(items, mid + 1, last);
        Merge(items, first, mid, last);
    }
}

void IterativeMergeSort(vector<int>& items, int first, int last){
    if(!ValidParameters(items, first, last)){
        return;
    }
    
    int n = last - first + 1;
    for(int curr_size = 1; curr_size <= n - 1; curr_size *= 2){
        for(int left_start = first; left_start < last; left_start += 2 * curr_size){
            int mid = min(left_start + curr_size - 1, last);
            int right_end = min(left_start + 2 * curr_size - 1, last);
            Merge(items, left_start, mid, right_end);
        }
    }
}

void QuickSort(vector<int>& items, int first, int last){
    if(!ValidParameters(items, first, last)){
        return;
    }
    
    //uses insertion sort for small partitions because it is faster
    if(last - first < 4){
        InsertionSort(items, first, last);
        return;
    }

    //median of three partitioning
    int mid = (first + last) / 2;
    if(items[first] > items[last]){
        swap(items[first], items[last]);
    }
    if(items[first] > items[mid]){
        swap(items[first], items[mid]);
    }
    else if(items[mid] > items[last]){
        swap(items[mid], items[last]);
    }

    int pivot = items[mid];
    swap(items[mid], items[last - 1]);
    int left = first + 1;
    int right = last - 2;
    bool done = false;

    while(!done){
        while(items[left] < pivot){
            left++;
        }
        while(items[right] > pivot){
            right--;
        }
        if(right > left){
            swap(items[left], items[right]);
            right--;
            left++;
        }
        else{
            done = true;
        }
    }

    swap(items[left], items[last - 1]);
    QuickSort(items, first, left - 1);
    QuickSort(items, left + 1, last);
}

void ShellSort(vector<int>& items, int first, int last){
    if(!ValidParameters(items, first, last)){
        return;
    }
    
    int n = last - first + 1;
    //starts with a large gap and reduces it over iterations
    for(int gap = n / 2; gap > 0; gap /= 2){
        for(int i = first + gap; i <= last; i++){
            int temp = items[i];
            int j;
            //shift elements in the current gap until the correct position is found
            for(j = i; j >= first + gap && items[j - gap] > temp; j -= gap){
                items[j] = items[j - gap];
            }
            items[j] = temp;
        }
    }
}

#endif