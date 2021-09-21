Only to Implement the simplest smallest-largest element version.

~~~C++
class InsertionSort {
public:
	void __insert__sort(vector<int>& arr) {
		int n = arr.size();
		for (int i = 1; i < n; ++i) {
			for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j) {
				swap(arr[j - 1], arr[j]);
			}
		}
	}
};
~~~

