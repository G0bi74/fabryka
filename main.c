#include <iomanip>
#include <iostream>

void merge(float arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    float* L = new float[n1];
    float* R = new float[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
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


void mergeSort(float arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

class MyList {
private:
    float *list;
    int size;
    int capacity;

    void Resize() {
        capacity *= 2;
        float* new_list = new float[capacity];
        for (int i = 0; i < size; i++) {
            new_list[i] = list[i];
        }
        delete[] list;
        list = new_list;
    }

public:
    MyList(int n) : size(0), capacity(n) {
        list = new float[n];
    }
    ~MyList() {
        delete[] list;
    }

    void Addlast(float val) {
        if (size == capacity) {
            Resize();
        }
        list[size++] = val;
    }
    float* Front() {
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
    float FindMax() {
        float max= 0;
        float last = list[size - 1];
        for (int i = size-2; i >= 0; i--) {
            if (max < last - list[i] ) {
                max = last - list[i];
            }
            last = list[i];
        }
        return max;
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
        std::cin >> val;
        list.Addlast(val);
    }
    mergeSort(list.Front(),0, list.GetSize()-1 );

    //list.PrintList();
    std::cout << std::setprecision(4) << std::fixed << list.FindMax();
    return 0;
}
