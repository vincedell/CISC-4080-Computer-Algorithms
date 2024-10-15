#include <iostream>
#include <vector>
using namespace std;


vector<int> ReadVector() {
 /* Read in an integer which specifies how many numbers are to be added
    Read in those integers one-by-one, and add each into the vector
    Return the vector
*/
/* initialize a vector */
    vector<int> vector;
    int n, value;

    cin >> n;

    //enter each element
    for (int i = 0; i < n; i++) {
        cin >> value;
        vector.push_back(value);
    }
    
    return vector;
}
/* bubble: iterative bubble sort function
@param: vector a 
@post-condition: vector a is arranged into ascending order */
void BubbleSort (vector<int> & a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}


/* iterative selection sort function
@param: vector a
@post-condition: vector a is arranged into ascending order */
void SelectionSort (vector<int> & a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int smallestElement = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[smallestElement]) {
                smallestElement = j;
            }
        }
        swap(a[i], a[smallestElement]);
    }
}

/* recursive implementation of bubble sort function
@param: vector a
@param: last, specify the range of vector a to be sorted, i.e., a[0...last] is to be sorted
@post-condition: vector a[0...last] is arranged into ascending order */
void RecursiveBubble (vector<int> & a, int last) {
    //base case
    if (last <= 0) {
        return;
    }
    //general case
    for (int i = 0; i < last; i++) {
        if (a[i] > a[i + 1]) {
            swap(a[i], a[i + 1]);
        }
    }
    RecursiveBubble(a, last - 1);
}

/* recursive selection sort function
@param: vector a
@param: first, specify the range of vector a to be sorted to be a[first...n-1] is to be sorted, where n is the size of vector a
@post-condition: vector a[first...n-1] is arranged into ascending order */
void RecursiveSelection (vector<int> & a, int first) {
    int n = a.size();
    //base case
    if (first >= n - 1) {
        return;
    }

    // general case
    int smallestElement = first;
    for (int i = first + 1; i < n; i++) {
        if (a[i] < a[smallestElement]) {
            smallestElement = i;
        }
    }
    swap(a[first], a[smallestElement]);
    RecursiveSelection(a, first + 1);
}

int main() {
    vector<int> vector;
    string command;
    
    //read vector
    vector = ReadVector();
    cin >> command; 
 
    if(command == "bubble")
        BubbleSort(vector);
    else if(command == "selection")
        SelectionSort(vector);
    else if(command == "rbubble")
        RecursiveBubble(vector, vector.size() - 1);
    else if(command == "rselection")
        RecursiveSelection(vector, 0);
 
    for(int i = 0; i < vector.size(); i++) //print elements
    {
        cout << vector[i] << " ";
    }
    cout << endl;

    return 0;
}
