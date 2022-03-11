#ifndef __VECTOR__H__
#define __VECTOR__H__
// https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators
namespace master {
template <typename T>
class vector {
 private:
  T *_begin, *_end, *_capacity;
  // constructors and destructor
 public:
  vector() : _begin(nullptr), _end(nullptr), _capacity(nullptr) {}
  vector(size_t size, const T& value = T())
      : _begin(nullptr), _end(nullptr), _capacity(nullptr) {
    //_begin = (T*)malloc(size * sizeof(T));
    reserve(size);
    if (_capacity == nullptr) {
      std::cout << "vector failed to construct\n";
    }
    while (size--) {
      *_end++ = value;
    }
  }
  vector(const std::initializer_list<T>& l)
      : _begin(nullptr), _end(nullptr), _capacity(nullptr) {
    size_t size = l.size();
    reserve(size);
    if (_capacity == nullptr) {
      std::cout << "vector failed to construct\n";
    }
    for (auto iter = l.begin(); iter != l.end(); ++iter) {
      *_end++ = *iter;
    }
  }
  vector(const vector<T>& v)
      : _begin(nullptr), _end(nullptr), _capacity(nullptr) {
    reserve(v.size());
    if (_capacity == nullptr) {
      std::cout << "vector failed to construct\n";
    }
    for (int i = 0; i < v.size(); ++i) {
      *_end++ = *(v._begin + i);
    }
  }
  vector(vector<T>&& v) : _begin(nullptr), _end(nullptr), _capacity(nullptr) {
    std::swap(_begin, v._begin);
    std::swap(_end, v._end);
    std::swap(_capacity, v._capacity);
  }
  virtual ~vector() {
    if (_begin) {
      delete[] _begin;
    }
  }
  // operators
 public:
  T& operator[](const size_t ind) { return *(_begin + ind); }
  vector<T>& operator=(const std::initializer_list<T>& l) {
    size_t size = this->size(), capacity = this->capacity();
    T* prebegin = _begin;
    _begin = nullptr;
    reserve(l.size());
    if (_capacity == nullptr) {
      std::cerr << "operator=(const std::initializer_list<T>& l) failed, data "
                   "rollbacked\n";
      _begin = prebegin;
      _end = _begin + size;
      _capacity = _begin + capacity;
      return *this;
    }
    for (auto iter : l) {
      *_end++ = iter;
    }
    delete[] prebegin;
    return *this;
  }
  vector<T>& operator=(const vector<T>& v) {
    if (this == &v) {
      return *this;
    }
    size_t size = this->size(), capacity = this->capacity();
    T* prebegin = _begin;
    _begin = nullptr;
    reserve(v.size());
    if (_capacity == nullptr) {
      std::cerr << "operator=(const vector<T>& v) failed, data rollbacked\n";
      _begin = prebegin;
      _end = _begin + size;
      _capacity = _begin + capacity;
      return *this;
    }
    for (int i = 0; i < v.size(); ++i) {
      *_end++ = *(v._begin + i);
    }
    delete[] prebegin;
    return *this;
  }
  vector<T>& operator=(vector<T>&& v) {
    delete[] _begin;
    _begin = _end = _capacity = nullptr;
    std::swap(_begin, v._begin);
    std::swap(_end, v._end);
    std::swap(_capacity, v._capacity);
    return *this;
  }
  //  functions
 public:
  inline size_t size() const { return _end - _begin; }
  inline size_t capacity() const { return _capacity - _begin; }
  void reserve(const size_t& size) {
    if (size <= capacity()) {
      return;
    }
    T* p = nullptr;
    if (_begin) {
      p = (T*)realloc(_begin, size * sizeof(T*));
    } else {
      p = (T*)malloc(size * sizeof(T));
    }
    _begin = _end = p, _capacity = p == nullptr ? nullptr : _begin + size;
  }
  void push_back(const T& x) {
    bool flag = true;
    if (_end == _capacity) {
      size_t len;
      if (size() == 0) {
        len = 1;
      } else {
        len = size() * 2;
      }
      size_t size = this->size(), capacity = this->capacity();
      T* prebegin = _begin;
      reserve(len);
      if (_capacity == nullptr) {
        std::cerr << "operator=(const vector<T>& v) failed, data rollbacked\n";
        _begin = prebegin;
        _end = _begin + size;
        _capacity = _begin + capacity;
        flag = false;
      }
      if (flag) {
        *_end++ = x;
      }
    }
  }
  void pop_back() {
    if (_end > _begin) {
      --_end;
    }
  }
  inline T& at(size_t ind) { return *(_begin + ind); }
  inline void clear() { _end = _begin; }
  inline bool empty() { return size() == 0; }
  inline T& front() { return *(_begin); }
  inline T& back() { return *(_end - 1); }
  void swap(vector<T>& v) {
    std::swap(_begin, v._begin);
    std::swap(_end, v._end);
    std::swap(_capacity, v._capacity);
  }
  void resize(size_t size, const T& value = T()) {
    if (size <= capacity()) {
      if (size <= this->size()) {
        _end = _begin + size;
      } else {
        T* temp_end = _begin + size;
        while (_end != temp_end) {
          *_end++ = value;
        }
      }
    } else {
      size_t presize = this->size(), capacity = this->capacity();
      T* prebegin = _begin;
      reserve(size);
      if (_capacity == nullptr) {
        std::cerr << "resize function failed, data rollbacked\n";
        _begin = prebegin;
        _end = _begin + size;
        _capacity = _begin + capacity;
        return;
      }
      _end = _begin + presize;
      T* temp_end = _begin + size;
      while (_end != temp_end) {
        *_end++ = value;
      }
    }
  }
  inline unsigned long long max_size() { return ULLONG_MAX / sizeof(T); }

  // iterator
 public:
  class iterator {
   private:
    master::vector<T>* pVector;
    size_t pos;

   public:
    iterator(master::vector<T>* vector, size_t offset = 0)
        : pVector(vector), pos(offset) {}
    bool operator!=(const iterator& it) {
      if (pVector == it.pVector) return pos != it.pos;
      return true;
    }
    iterator& operator++() {
      ++pos;
      return *this;
    }
    iterator operator++(int) {
      iterator it(pVector, pos);
      ++pos;
      return it;
    }
    iterator& operator+=(size_t offset) {
      pos += offset;
      return *this;
    }
    iterator operator+(size_t offset) {
      return iterator(pVector, pos + offset);
    }
    iterator operator-(size_t offset) {
      return iterator(pVector, pos - offset);
    }
    iterator& operator--() {
      --pos;
      return *this;
    }
    iterator operator--(int) {
      iterator it(pVector, pos);
      --pos;
      return it;
    }
    iterator& operator-=(size_t offset) {
      pos -= offset;
      return *this;
    }
    T& operator*() { return *(pVector->_begin + pos); }
    T* operator->() { return pVector->_begin + pos; }
    T& operator[](size_t offset) { return *(pVector->_begin + offset); }
  };

 public:
  // reverse_iterator
  class reverse_iterator {
   private:
    master::vector<T>* pVector;
    size_t pos;

   public:
    reverse_iterator(master::vector<T>* vector, size_t offset = 0)
        : pVector(vector), pos(vector->size() - 1 - offset) {}
    bool operator!=(const reverse_iterator& it) {
      if (pVector == it.pVector) return pos != it.pos;
      return true;
    }
    reverse_iterator& operator++() {
      --pos;
      return *this;
    }
    reverse_iterator operator++(int) {
      reverse_iterator it(pVector, pos);
      --pos;
      return it;
    }
    reverse_iterator& operator+=(size_t offset) {
      pos -= offset;
      return *this;
    }
    reverse_iterator operator+(size_t offset) {
      return reverse_iterator(pVector, pos + offset);
    }
    reverse_iterator operator-(size_t offset) {
      return reverse_iterator(pVector, pos - offset);
    }
    reverse_iterator& operator--() {
      ++pos;
      return *this;
    }
    reverse_iterator operator--(int) {
      reverse_iterator it(pVector, pos);
      ++pos;
      return it;
    }
    reverse_iterator& operator-=(size_t offset) {
      pos += offset;
      return *this;
    }
    T& operator*() { return *(pVector->_begin + pos); }
    T* operator->() { return pVector->_begin + pos; }
    T& operator[](size_t offset) { return *(pVector->_begin + offset); }
  };
  inline iterator begin() { return iterator(this); }
  inline iterator end() { return iterator(this, size()); }
  inline reverse_iterator rbegin() { return reverse_iterator(this); }
  inline reverse_iterator rend() { return reverse_iterator(this, size()); }
};
}  // namespace master
#endif