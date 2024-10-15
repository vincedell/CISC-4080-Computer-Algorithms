#include <iostream>
#include <vector>
#include <functional>
#include "lab2_funcs.h"
using namespace std;

// Read int from standard input until -1 is reached, return the values in a vector
vector<int> GenerateVectorFromInput () {
    vector<int> v;
    int input; // take in user input

    while (cin >> input && input!=-1)
        v.push_back(input);

    return v;
}


//Generate random numbers: 0...999
vector<int> GenerateRandomVector(int size)
{
        vector<int> res(size);

        for (int i=0;i<size;i++)
        {
                res[i] = rand()%10000;
        }

        return res;
}

// print vector
void PrintVector (const vector<int> & L) {
    for (auto i = L.begin(); i != L.end(); i++) {
        cout << *i << " ";
    }
    cout<<endl;
}



/*pre-condition: v1, v2 are two sorted vectors (in ascending order).
 Result might or might not be empty (i.e., you need to clear it)
 post-condition: vector result stores values from v1 and v2, in ascending order*/
void Merge (const vector<int> & list1, const vector<int> & list2, vector<int> & result)
{
    result.clear(); //clear result because it may or may not be empty
    
    int i = 0, j = 0;

    //stores elements in result in ascending order
    while (i < list1.size() && j < list2.size()) {
         if (list1[i] < list2[j]) {
            result.push_back(list1[i]);
            i++;
        } else {
            result.push_back(list2[j]);
            j++;
        }
    }
    //append remaining elements
    while (i < list1.size()) {
        result.push_back(list1[i]);
        i++;
    }
    while (j < list2.size()) {
        result.push_back(list2[j]);
        j++;
    }

}


/* sort the vector into ascending order using merge sort algorithm
 @param L: the vector to be sorted
 @pre:
 @post: elements in L have been rearranged into ascending order
*/
void MergeSort (vector<int> & L)
{
 //Note: You will use the MergeSort function implemented above
 
    // base case
    if (L.size() <= 1) return; 
    
    //general case
    int mid = L.size() / 2;  // Find the middle point to divide the vector
    
    vector<int> left(L.begin(), L.begin() + mid);  // Left half
    vector<int> right(L.begin() + mid, L.end());  // Right half

    // sort two halves using recursion
    MergeSort(left);
    MergeSort(right);

    // merge two lists into original list
    Merge(left, right, L);

}

/* Sort list[first...last] into ascending order */
void QuickSort(vector<int> & list, int first, int last)
{
    if (first < last) {
        int pivot = list[last]; // last element declared as pivot
        int i = first - 1; 
        
        // "partition" the list based on the pivot
        for (int j = first; j < last; j++) {
            if (list[j] <= pivot) {
                i++; 
                swap(list[i], list[j]);
            }
        }
        
        // Place the pivot in its correct position
        swap(list[i + 1], list[last]);
        int pi = i + 1; // Partition index
        
        // recursively call QuickSort for left and right lists
        QuickSort(list, first, pi - 1);  // left sublist
        QuickSort(list, pi + 1, last); // right sublist
    }
}


 /* Given a vector of sorted vector, merge them all into one sorted vector
  @param listOfLists: a vector of sorted vector of ints
  @param result: the merged sorted list
   @pre-condition: listOfLists contains a certain number of sorted vectors
   @post-condition: all ints are merged and saved into result, in ascending order
  */
void KWayMerge_BF (vector<vector<int>> listOfLists, vector<int> & result)
{
    result.clear();

    //iterate through listOfList and update with the merged result
    for (int i = 0; i < listOfLists.size(); i++) {
        const vector<int>& list = listOfLists[i]; 
        vector<int> temp;
        Merge(result, list, temp);
        result = temp;
    }
}

void KWayMerge_DAC (vector<vector<int>> listOfLists, vector<int> & result)
{
    //clear result
    result.clear();
    
    // base case
    if (listOfLists.size() == 1) {
        result = listOfLists[0];
        return;
    }

    //general case, split into two lists
    int mid = listOfLists.size() / 2;
    vector<vector<int>> left(listOfLists.begin(), listOfLists.begin() + mid);
    vector<vector<int>> right(listOfLists.begin() + mid, listOfLists.end());

    // merge two halves using recursion
    vector<int> leftResult, rightResult;
    KWayMerge_DAC(left, leftResult);
    KWayMerge_DAC(right, rightResult);

    // merge the two sorted results into the final result
    Merge(leftResult, rightResult, result);
}

/* Sort the given list using simplified HybridSort
  First use QuickSort algorithm to generate sorted sublists, each of #segment_length
  Then use KWayMerge function to merge these sorted sublists into one sorted list */
void HybridSort (vector<int> & list, int segment_length)
{
    vector<vector<int>> listOfRuns;
        
    for (int i = 0; i < list.size(); i += segment_length) {
     // determine the range of sublists
     int end = min(i + segment_length, (int)list.size());

     // take new sublist
     vector<int> sublist(list.begin() + i, list.begin() + end);

     // sort new sublist using QuickSort
     QuickSort(sublist, 0, sublist.size() - 1);

     // add sublist to listOfRuns
     listOfRuns.push_back(sublist);
    }

    // finally merge sorted sublists into one
    KWayMerge_DAC(listOfRuns, list);
}
