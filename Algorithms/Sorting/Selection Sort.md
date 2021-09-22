~~~C++
	void select_sort(int l, int r, vector<int>& arr) {
		for (int i = l; i < r - 1; ++i) {
			int ind = i;
			for (int j = i + 1; j < r; ++j) {
				if (arr[ind] > arr[j]) ind = j;
			}
			if (ind != i) swap(arr[ind], arr[i]);
		}
	}
~~~

