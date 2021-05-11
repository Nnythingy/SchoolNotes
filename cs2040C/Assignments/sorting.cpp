//MERGE SORT
void merge(int a[], int low, int mid, int high) {
  // subarray1 = a[low..mid], subarray2 = a[mid+1..high], both sorted
  int N = high-low+1;
  int b[N]; // discuss: why do we need a temporary array b?
  int left = low, right = mid+1, bIdx = 0;
  while (left <= mid && right <= high) // the merging
    b[bIdx++] = (a[left] <= a[right]) ? a[left++] : a[right++];
  while (left <= mid) b[bIdx++] = a[left++]; // leftover, if any
  while (right <= high) b[bIdx++] = a[right++]; // leftover, if any
  for (int k = 0; k < N; k++) a[low+k] = b[k]; // copy back
}

void mergeSort(int a[], int low, int high) {
  // the array to be sorted is a[low..high]
  if (low < high) { // base case: low >= high (0 or 1 item)
    int mid = (low+high) / 2;	
    mergeSort(a, low  , mid ); // divide into two halves
    mergeSort(a, mid+1, high); // then recursively sort them
    merge(a, low, mid, high); // conquer: the merge subroutine
  }
}

//QUICK SORT
int partition(int a[], int i, int j) {
  int p = a[i]; // p is the pivot
  int m = i; // S1 and S2 are initially empty
  for (int k = i+1; k <= j; k++) { // explore the unknown region
    if (a[k] < p) { // case 2
      m++;
      swap(a[k], a[m]); // C++ STL algorithm std::swap
    } // notice that we do nothing in case 1: a[k] >= p
  }
  swap(a[i], a[m]); // final step, swap pivot with a[m]
  return m; // return the index of pivot
}

void quickSort(int a[], int low, int high) {
  if (low < high) {
    int m = partition(a, low, high); // O(N)
    // a[low..high] ~> a[low..m–1], pivot, a[m+1..high]
    quickSort(a, low, m-1); // recursively sort left subarray
    // a[m] = pivot is already sorted after partition
    quickSort(a, m+1, high); // then sort right subarray
  }
}