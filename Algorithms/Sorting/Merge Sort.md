# Recursive Version

~~~C++
	void re_merge_sort(int l, int r, vector<int>& arr) {
		return __re_merge_sort(l, r - 1, arr);
	}
	void __re_merge_sort(int l, int r, vector<int>& arr) {
		if (l == r) return;
		int mid = (l + r) >> 1;
		__re_merge_sort(l, mid, arr);
		__re_merge_sort(mid + 1, r, arr);
		int x = l, y = mid + 1, loc = 0;
		vector<int> temp(r - l + 1);
		while (x <= mid || y <= r) {
			if (y > r || x <= mid && arr[x] <= arr[y]) {
				temp[loc++] = arr[x++];
			}
			else {
				temp[loc++] = arr[y++];
			}
		}
		for (int i = l; i <= r; ++i) {
			arr[i] = temp[i - l];
		}
	}
~~~



# Iterative Version

~~~C++
	void it_merge_sort(int l, int r, vector<int>& arr) {
		int n = r - l + 1;
		vector<int> temp(n);
		--r;
		for (int size = 1; size < n; size <<= 1) {
			for (int left = l; left < r; left += (size << 1)) {
				int mid = min(r, left + size - 1), right = min(r, left + (size << 1) - 1);
				int loc = 0;
				int x = left, y = mid + 1;
				while (x <= mid || y <= right) {
					if (y > right || x <= mid && arr[x] <= arr[y]) {
						temp[loc++] = arr[x++];
					}
					else {
						temp[loc++] = arr[y++];
					}
				}
				for (int i = left; i <= right; ++i) {
					arr[i] = temp[i - left];
				}
			}
		}
	}
~~~



