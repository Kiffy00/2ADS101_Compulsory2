#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

/// <summary>
/// Merges two halves of a subarray.
/// </summary>
/// <param name="arr">The array to sort.</param>
/// <param name="l">The starting index of the left subarray.</param>
/// <param name="m">The ending index of the left subarray.</param>
/// <param name="r">The ending index of the right subarray.</param>
void Merge(std::vector<int>& arr, int l, int m, int r) {
    std::vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    std::vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else 
            arr[k++] = right[j++];
    }
    while (i < left.size())
        arr[k++] = left[i++];
    while (j < right.size())
        arr[k++] = right[j++];
}

/// <summary>
/// Recursively sorts a subarray using the MergeSort algorithm.
/// </summary>
/// <param name="arr">The array to sort.</param>
/// <param name="l">The starting index of the subarray.</param>
/// <param name="r">The ending index of the subarray.</param>
void MergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }
}

/// <summary>
/// Recursively sorts a subarray using the QuickSort algorithm.
/// </summary>
/// <param name="arr">The array to sort.</param>
/// <param name="low">The starting index of the subarray.</param>
/// <param name="high">The ending index of the subarray.</param>
void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);

        QuickSort(arr, low, i);
        QuickSort(arr, i + 2, high);
    }
}

/// <summary>
/// Checks if an array is sorted.
/// </summary>
/// <param name="arr">The array to check.</param>
/// <param name="n">The number of elements in the array.</param>
/// <returns>Returns true if the array is sorted, false otherwise.</returns>
bool IsSorted(int arr[], int n)
{
    while (--n > 0)
    {
        if (arr[n] < arr[n - 1])
            return false;
    }
    return true;
}

/// <summary>
/// Shuffles an array.
/// </summary>
/// <param name="arr">The array to shuffle.</param>
/// <param name="n">The number of elements in the array.</param>
void Shuffle(int arr[], int n) 
{
    for (int i = 0; i < n; i++)
        std::swap(arr[i], arr[rand() % n]);
}

/// <summary>
/// Sorts an array using the BogoSort algorithm.
/// </summary>
/// <param name="arr">The array to sort.</param>
/// <param name="n">The number of elements in the array.</param>
void BogoSort(int arr[], int n)
{
    while (!IsSorted(arr, n))
        Shuffle(arr, n);
}

/// <summary>
/// Prints the contents of an array.
/// </summary>
/// <param name="arr">The array to print.</param>
/// <param name="n">The number of elements in the array.</param>
void PrintArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";

    std::cout << "\n";
}
/// <summary>
/// Clears the input buffer, ensuring previous input does not affect subsequent inputs.
/// </summary>
void ClearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    while (true) {
        int size;
        std::cout << "Enter array size: ";
        while (!(std::cin >> size) || size <= 0) {
            std::cout << "Please enter a valid size: ";
            ClearInput();
        }

        int* arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 100; // Generates random numbers between 0 and 99
        }

        std::cout << "New array: ";
        PrintArray(arr, size);

        int choice;
        std::cout << "\nChoose a sorting function (1-MergeSort, 2-QuickSort, 3-BogoSort, 4-Exit): ";
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter an integer (1-MergeSort, 2-QuickSort, 3-BogoSort, 4-Exit): ";
            ClearInput();
        }

        // Timer starts here
        auto start = std::chrono::high_resolution_clock::now();

        switch (choice) {
        case 1:
        {
            std::vector<int> vec(arr, arr + size);
            MergeSort(vec, 0, size - 1);
            for (int i = 0; i < size; i++) {
                arr[i] = vec[i];
            }
        }
        break;
        case 2:
            QuickSort(arr, 0, size - 1);
            break;
        case 3:
            BogoSort(arr, size);
            break;
        case 4:
            delete[] arr;
            return 0;
        default:
            std::cout << "Invalid choice! Using QuickSort by default.\n";
            QuickSort(arr, 0, size - 1);
            break;
        }

        // Timer Ends here
        auto end = std::chrono::high_resolution_clock::now();
        auto microDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // Cast to microseconds
        double milliDuration = static_cast<double>(microDuration.count()) / 1000.0; // Cast to high definition milliseconds in form of double
        std::cout << "\nTime taken: " << std::fixed << std::setprecision(3) << milliDuration << " milliseconds\n";

        std::cout << "Sorted array: ";
        PrintArray(arr, size);

        delete[] arr; // Better safe
        std::cout << "\n------------------------------\n";
    }

    return 0;
}
