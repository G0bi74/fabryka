#include <iomanip>
#include <iostream>

void merge(int arr[], int left, int mid, int right, int exp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] / exp <= R[j] / exp) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
    delete[] L;
    delete[] R;
}


void mergeSort(int arr[], int left, int right, int exp) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, exp);
        mergeSort(arr, mid + 1, right, exp);

        merge(arr, left, mid, right, exp);
    }
}

class MyList {
private:
    int *list;
    int size;
    int capacity;

    void Resize() {
        capacity *= 2;
        int* new_list = new int[capacity];
        for (int i = 0; i < size; i++) {
            new_list[i] = list[i];
        }
        delete[] list;
        list = new_list;
    }

public:
    MyList(int n) : size(0), capacity(n) {
        list = new int[n];
    }
    ~MyList() {
        delete[] list;
    }

    void Addlast(int val) {
        if (size == capacity) {
            Resize();
        }
        list[size++] = val;
    }
    int* Front() {
        return list;
    }
    int GetSize() const {
        return size;
    }

    void PrintList() {
        for (int i = 0; i < size; i++) {
            std::cout << list[i] << " ";
        }std::cout << "\n";
    }
    float FindMaxDiff() {
        int max= 0;
        int last = list[size - 1];
        for (int i = size-2; i >= 0; i--) {
            if (max < last - list[i] ) {
                max = last - list[i];
            }
            last = list[i];
        }
        return max;
    }
    int getMax() {
        int max = 0;
        for (int i = 0; i < size; i++) {
            if (max < list[i]) {
                max = list[i];
            }
        }return max;
    }

    void radixsort()
    {
        int m = getMax();

        for (int exp = 1; m / exp > 0; exp *= 10)
            mergeSort(list, 0, size - 1, exp);
    }

};



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    MyList list(n);
    for (int i = 0; i < n; i++) {
        float val;
        std::cin >> val ;
        int x = val * 10000;
        list.Addlast(x);
    }

    //list.PrintList();
    list.radixsort();
    //list.PrintList();
    std::cout << std::setprecision(4) << std::fixed << list.FindMaxDiff() / 10000;
    return 0;
}
