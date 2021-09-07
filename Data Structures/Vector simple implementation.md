# Introduction

Vector is a expandable array, we should maintain two variables: size and capacity. When size >= capacity, we need to delete the old space allocated, allocate a new space based on the compilers (i.e., MSVC expands 1.5 times of the old space while g++ expands 2 times of the old space), and copy the old data to the new allocated spaces.



Note that we are not willing to lose any data, therefore, when allocating new spaces, we need to judge whether it has been successfully allocated, otherwise we need to reduce the space we need and try another time. If applying for extra spaces failed, the old data should not be moved and deleted in case of losing data.



From the expanding operations can we know that if it is always triggering expanding, a better way is to allocate enough space at the beginning, since moving to new allocated space might be time consuming (especially for those huge classes).



Since the memory spaces are continuous, it is also very slow to implement insert and delete from the vector (except for the last element).



# Codes

Note that std::vector implementation uses multiple pointers but not mcapacity or msize. This is just a simplest implementation of Vector, only to illustrate how vector might work.



~~~C++
class Vector {
private:
	int msize, mcapacity, * mdata;
	bool expand() {
		int extra_size = mcapacity;
		int* p = nullptr;
		while (extra_size) {
			p = (int*)realloc(mdata, sizeof(int) * (mcapacity + extra_size));
			if (p) break;
			extra_size >>= 1;
		}
		if (p == nullptr) return false;
		mcapacity += extra_size;
		mdata = p;
		return true;
	}
public:
	Vector() :msize(0), mcapacity(1) {
		mdata = new int();
	}
	Vector(int capacity) :msize(capacity), mcapacity(capacity) {
		mdata = new int[capacity]();
	}
	Vector(int capacity, int value) :msize(capacity), mcapacity(capacity) {
		mdata = new int[capacity];
		for (int i = 0; i < capacity; ++i) {
			mdata[i] = value;
		}
	}
	~Vector() {
		delete mdata;
	}
	int back() {
		return mdata[msize - 1];
	}
	int size() {
		return msize;
	}
	int capacity() {
		return mcapacity;
	}
	bool empty() {
		return msize == 0;
	}
	void clear() {
		delete mdata;
		mdata = new int();
	}
	void pop_back() {
		--msize;
	}
	void push_back(int value) {
		if (msize >= mcapacity) {
			if (!expand()) {
				return;
			}
		}
		mdata[msize++] = value;
	}
	int& operator[](int index) {
		return mdata[index];
	}
	void insert(int index, int value) {
		if (msize == mcapacity) {
			if (!expand()) {
				return;
			}
		}
		for (int i = msize; i > index; --i) {
			mdata[i] = mdata[i - 1];
		}
		mdata[index] = value;
		++msize;
	}
	void erase(int index) {
		for (int i = index + 1; i < msize; ++i) {
			mdata[i - 1] = mdata[i];
		}
		--msize;
	}
};
~~~

There should not be any bugs.