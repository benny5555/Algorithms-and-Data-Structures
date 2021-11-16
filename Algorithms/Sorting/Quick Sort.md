# Simplest Implementation

~~~C++
	void quick_sort(int l, int r, vector<int>& arr) {
		__quick_sort(l, r - 1, arr);
	}
	void __quick_sort(int l, int r, vector<int>& arr) {
		if (l >= r) return;
		int left = l, right = r, pivot = arr[left];
		while (left < right) {
			while (left < right && arr[right] >= pivot) --right;
			arr[left] = arr[right];
			while (left < right && arr[left] <= pivot) ++left;
			arr[right] = arr[left];
		}
		arr[left] = pivot;
		__quick_sort(l, left - 1, arr);
		__quick_sort(left + 1, r, arr);
	}
~~~

This is the simplest implementation of quick sort. However, the efficiency is not that satisfying.



# Recursive Implementation optimized

~~~C++
	void op_quick_sort(int l, int r, vector<int>& arr) {
		srand(time(0));
		__op_quick_sort(l, r - 1, arr);
	}
	void __op_quick_sort(int l, int r, vector<int>& arr) {
		if (l >= r) return;
		int cut = re_partition(l, r, rand() % (r - l + 1) + l, arr);
		__op_quick_sort(l, cut - 1, arr);
		__op_quick_sort(cut + 1, r, arr);
	}
	int re_partition(int l, int r, int pivot, vector<int>& arr) {
		swap(arr[pivot], arr[r]);
		int left = l, right = r;
		while (left < right) {
			while (left < right && arr[left] <= arr[r]) ++left;
			while (left < right && arr[right] >= arr[r]) --right;
			swap(arr[left], arr[right]);
		}
		swap(arr[left], arr[r]);
		return left;
	}
~~~



# Iterative Implementation

~~~C++
	void it_quick_sort(int l, int r, vector<int>& arr) {
		srand(time(0));
		stack<int> stk;
		--r;
		stk.push(l);
		stk.push(r);
		while (!stk.empty()) {
			r = stk.top();
			stk.pop();
			l = stk.top();
			stk.pop();
			int cut = it_partition(l, r, rand() % (r - l + 1) + l, arr);
			if (cut - 1 > l) {
				stk.push(l);
				stk.push(cut - 1);
			}
			if (cut + 1 < r) {
				stk.push(cut + 1);
				stk.push(r);
			}
		}
	}
	int it_partition(int l, int r, int pivot, vector<int>& arr) {
		swap(arr[pivot], arr[r]);
		int left = l, right = r;
		while (left < right) {
			while (left < right && arr[left] <= arr[r]) ++left;
			while (left < right && arr[right] >= arr[r]) --right;
			swap(arr[left], arr[right]);
		}
		swap(arr[left], arr[r]);
		return left;
	}
~~~

