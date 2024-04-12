#include <bits/stdc++.h>
#include<omp.h>


using namespace std;

void bubble(int array[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (array[j] > array[j + 1]) swap(array[j], array[j + 1]);
        }
    }
}

void parallel_bubblesort(int array[], int n) {

 

    for (int i = 0; i < n; i++)
    {
        int first = i % 2;

        // defining the shared data source for parallel execution.

        #pragma omp parallel for shared (array, first) num_threads(16)

        for (int j = first; j < n - 1; j += 2)
            if (array[j] > array[j + 1])
                swap(array[j], array[j + 1]);
    }

    return;
}

void printArray(int arr[], int n){
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";
}

int main(){
    // Set up variables
    int n = 100000;
    int arr[n];
    int brr[n];
    double start_time, end_time;

    // Create an array with random numbers
    for(int i = 0, j = n; i < n; i++, j--){
    		arr[i] = 1 + (rand() % 1000);
    		brr[i]=arr[i];
    }
    
    // Sequential time
    start_time = omp_get_wtime();
    bubble(arr, n);
    end_time = omp_get_wtime();     
    cout << "Sequential Bubble Sort took : " << end_time - start_time << " seconds.\n";
    // printArray(arr, n);
    
    // Reset the array
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
    
    // Parallel time
    start_time = omp_get_wtime();
    parallel_bubblesort(brr, n);
    end_time = omp_get_wtime();     
    cout << "Parallel Bubble Sort took : " << end_time - start_time << " seconds.\n";
    // printArray(arr, n);
}   