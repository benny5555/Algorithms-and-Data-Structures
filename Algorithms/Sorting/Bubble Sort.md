Only to implement the simplest version of Bubble Sorting.

~~~C++
	void bubble_sort(int l, int r, vector<int>& arr) {
		bool swapped = 0;
		for (int i = l + 1; i < r; ++i) {
			swapped = 0;
			for (int j = l; j < l + r - i; ++j) {
				if (arr[j] <= arr[j + 1]) continue;
				swap(arr[j], arr[j + 1]);
				swapped = 1;
			}
			if (!swapped) break;
		}
	}
~~~



