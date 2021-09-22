Only to Implement the simplest smallest-largest element version.

~~~C++
	void insert_sort(int l, int r, vector<int>& arr) {
		for (int i = l + 1; i < r; ++i) {
			for (int j = i; j > l && arr[j] < arr[j - 1]; --j) {
				swap(arr[j], arr[j - 1]);
			}
		}
	}
~~~

