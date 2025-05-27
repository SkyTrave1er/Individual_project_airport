#pragma once
#include <cstddef>
#include <iostream>
#include <Windows.h>

#define STEP_OF_CAPACITY 15

enum State {EMPTY, BUSY, DELETED};

template <class T>

class TVector { 
private:
    T* _data = nullptr;
	size_t _capacity = 0;
	size_t _size = 0;
	size_t _deleted = 0;
	State* _states = nullptr;
	
    size_t calculate_capacity(size_t required_capacity) const; 
public:
    class Iterator {
        T* _ptr;
        size_t _pos;
        size_t _finish;
        State* _states;
    public:
        Iterator(T* p, State* states, size_t pos, size_t cap) 
            : _ptr(p), _states(states), _pos(pos), _finish(cap) {}
        

        T& operator*() {
            if (_pos > _finish) {
                throw std::out_of_range("Invalid pos");
            }
            return *_ptr;
        }

        Iterator& operator++() {
            do {
                ++_pos;
                ++_ptr;
            } while ((_pos < _finish) && (_states[_pos] != BUSY));
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            do {
                --_pos;
                --_ptr;
            } while ((_pos > 0) && (_states[_pos] != BUSY));
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        Iterator operator+(size_t k) const {
            Iterator temp = *this;;
            for (size_t i = 0; i < k; ++i) {
                ++temp;
            }
            return temp;
        }


        bool operator!=(const Iterator& other) const {
            return (_ptr != other._ptr);
        }

        bool operator==(const Iterator& other) const {
            return (_ptr != other._ptr);
        }

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                _ptr = other._ptr;
                _states = other._states;
                _pos = other._pos;
                _finish = other._finish;
            }
            return *this;
        }

        size_t get_index() const noexcept {
            return _pos;
        }
    };

    friend class Iterator;

    class ConstIterator {
        T* _ptr;
        size_t _pos;
        size_t _capacity;
        State* _states;
    public:
        ConstIterator(const T* p, const State* states, size_t pos, size_t cap) 
            : _ptr(p), _states(states), _pos(pos), _capacity(cap) {
            while (_pos < _capacity && _states[_pos] != BUSY) {
                ++_pos;
                ++_ptr;
            }
        }

        const T& operator*() const {
            if (_pos > _capacity) {
                throw std::out_of_range("Invalid pos");
            }
            return *_ptr;
        }

        ConstIterator& operator++() {
            do {
                ++_pos;
                ++_ptr;
            } while ((_pos < _capacity) && (_states[_pos] != BUSY));
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ConstIterator& operator--() {
            do {
                --_pos;
                --_ptr;
            } while ((_pos > 0) && (_states[_pos] != BUSY));
            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator tmp = *this;
            --(*this);
            return tmp;
        }

        ConstIterator operator+(size_t k) const {
            ConstIterator temp = *this;
            for (size_t i = 0; i < k; ++i) {
                ++temp;
            }
            return temp;
        }

        bool operator!=(const ConstIterator& other) const {
            return (_ptr != other._ptr);
        }

        bool operator==(const ConstIterator& other) const {
            return (_ptr == other._ptr);
        }

        ConstIterator& operator=(const ConstIterator& other) {
            if (this != &other) {
                _ptr = other._ptr;
                _states = other._states;
                _pos = other._pos;
                _capacity = other._capacity;
            }
            return *this;
        }

    };

    friend class ConstIterator;
   
    TVector();
    TVector(size_t size);
	TVector(const T* arr, size_t n);
    TVector(std::initializer_list<T> init, size_t n = 0);
	TVector(const TVector<T>& other);
	~TVector();

	
	T* data() noexcept; //ÒÂÚÚÂ
	const T* data() const noexcept; //„ÂÚÚÂ

    Iterator begin() noexcept;
    ConstIterator begin() const noexcept;

    Iterator end() noexcept;
    ConstIterator end() const noexcept;

	T& front() noexcept;
    const T& front() const noexcept;

    T& back() noexcept;
	const T& back() const noexcept;
	size_t size() const noexcept;
	size_t capacity() const noexcept;

	bool is_empty() const noexcept;
    bool is_full() const noexcept;
	
    void push_back(const T& value);
    void push_front(const T& value);
    void insert(size_t pos, const T& value);
    void insert(const Iterator& it, const T& value);
    void insert(Iterator start, size_t count, const T& value);
    void pop_back();
    void pop_front();
    void erase(size_t pos);
    void erase(const Iterator& it);
    void erase(Iterator start, Iterator end);
    void erase(Iterator start, size_t count);

    void emplace(size_t pos, const T& value);
    void assign(const T* arr, size_t n);
    void clear() noexcept;

    
    void reserve(size_t new_capacity);
    void shrink_to_fit();
    void resize(size_t new_size, const T& filler = T());

    
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;

    TVector<T>& operator=(const TVector<T>& other);
    bool operator==(const TVector<T>& other) const;
    bool operator!=(const TVector<T>& other) const;

    template <class T>
    friend void fisher_yates_shuffle(TVector<T>& vec);

    template <class T>
    friend void quick_sort(TVector<T>& vec);

    template <class T>
    friend int find_first(const TVector<T> &vec, const T& value);

    template <class T>
    friend int find_last(const TVector<T>& vec, const T& value);

    template <class T>
    friend int* find_all(const TVector<T>& vec, const T& value);
};



// ŒÕ—“–” “Œ–€ ¬≈ “Œ–¿

template <class T>
TVector<T>::TVector() : _data(nullptr), _capacity(0), _size(0), _deleted(0), _states(nullptr) {
    reserve(STEP_OF_CAPACITY);
}

template <class T>
TVector<T>::TVector(size_t size) : TVector() {
    if (size == 0) {
        reserve(STEP_OF_CAPACITY);
    }
    else if (size < 0) {
        throw std::out_of_range("size can't be minus");
    }
    else if (size > 0) {
        resize(size);
    }
}

template <class T>
TVector<T>::TVector(const T* arr, size_t n) : TVector() {
    reserve(n);
    for (size_t i = 0; i < n; ++i) {
        push_back(arr[i]);
    }
}

template <class T>
TVector<T>::TVector(std::initializer_list<T> init, size_t n) : TVector() {
    if (n == 0) {
        n = init.size();
    }
    reserve(n);
    for (const auto& item : init) {
        push_back(item);
    }
}

template <class T>
TVector<T>::TVector(const TVector<T>& other) : TVector() {
    reserve(other._size);
    for (size_t i = 0; i < other._capacity; ++i) {
        if (other._states[i] == BUSY) {
            push_back(other._data[i]);
        }
    }
}

template <class T>
TVector<T>::~TVector() {
    delete[] _data;
}

//œ≈–≈√–”« » Œœ≈–¿“Œ–Œ¬ ¬≈ “Œ–¿

template <class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
    if (this != &other) {
        clear(); 
        reserve(other._capacity); 
        for (size_t i = 0; i < other._capacity; ++i) {
            if (other._states[i] == BUSY) {
                _data[i] = other._data[i];
                _states[i] = BUSY;
                _size++;
            }
            else {
                _states[i] = other._states[i];
            }
        }
        _deleted = other._deleted;
    }
    return *this;
}

template <class T>
bool TVector<T>::operator==(const TVector<T>& other) const {
    if (_size != other._size) return false;

    auto it_this = begin();
    auto it_other = other.begin();
    while (it_this != end() && it_other != other.end()) {
        if (*it_this != *it_other) return false;
        ++it_this;
        ++it_other;
    }
    return true;
}

template <class T>
bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

template <class T>
T& TVector<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index is out of range");
    }

    size_t c = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            if (c == index) {
                return _data[i];
            }
            c++;
        }
    }
    throw std::logic_error("Internal error in operator[]");
}

template <class T>
const T& TVector<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index is out of range");
    }

    size_t current = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            if (current == index) {
                return _data[i];
            }
            current++;
        }
    }
    throw std::logic_error("Internal error in operator[]");
}


//»“≈–¿“Œ– 


template <class T>
typename TVector<T>::Iterator TVector<T>::begin() noexcept {
    size_t first_busy_pos = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            first_busy_pos = i;
            break;
        }
    }
    return Iterator(_data + first_busy_pos, _states + first_busy_pos, 0, _size + _deleted);
}

template <class T>
typename TVector<T>::ConstIterator TVector<T>::begin() const noexcept {
    size_t first_busy_pos = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            first_busy_pos = i;
            break;
        }
    }
    return Iterator(_data + first_busy_pos, _states + first_busy_pos, 0, _size + _deleted);
}

template <class T>
typename TVector<T>::Iterator TVector<T>::end() noexcept {
    size_t last_busy_pos = _size + _deleted;
    for (size_t i = _size + _deleted; i >= 0; i--) {
        if (_states[i] == BUSY) {
            last_busy_pos = i;
            break;
        }
    }
    return Iterator(_data + last_busy_pos + 1, _states + last_busy_pos + 1, last_busy_pos + 1, _size + _deleted);
}

template <class T>
typename TVector<T>::ConstIterator TVector<T>::end() const noexcept {
    size_t last_busy_pos = _size + _deleted;
    for (size_t i = _size + _deleted; i >= 0; i--) {
        if (_states[i] == BUSY) {
            last_busy_pos = i;
            break;
        }
    }
    return ConstIterator(_data + last_busy_pos + 1, _states + last_busy_pos + 1, last_busy_pos + 1, _size + _deleted);
}

//Ã≈À »≈ Ã≈“Œƒ€

template <class T>
T* TVector<T>::data() noexcept {
    return _data;
}

template <class T>
const T* TVector<T>::data() const noexcept {
    return _data;
}

template <class T>
T& TVector<T>::front() noexcept {
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == BUSY) {
            return _data[i];
        }
    }
    throw std::out_of_range("empty");
}

template <class T>
const T& TVector<T>::front() const noexcept {
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == BUSY) {
            return _data[i];
            break;
        }
    }
    throw std::out_of_range("empty");
}

template <class T>
T& TVector<T>::back() noexcept {
    for (size_t i = _capacity; i >= 0; i--) {
        if (_states[i] == BUSY) {
            return _data[i];
            break;
        }
    }
    throw std::out_of_range("empty");
}

template <class T>
const T& TVector<T>::back() const noexcept {
    for (size_t i = _capacity; i >= 0; i--) {
        if (_states[i] == BUSY) {
            return _data[i];
        }
    }
    throw std::out_of_range("empty");
}

template <class T>
size_t TVector<T>::size() const noexcept {
    return _size;
}

template <class T>
size_t TVector<T>::capacity() const noexcept {
    return _capacity;
}

template <class T>
T& TVector<T>::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index is out of range");
    }
    return (*this)[index]; 
}

template <class T>
const T& TVector<T>::at(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index is out of range");
    }
    return (*this)[index]; 
}


//œ¿Ãﬂ“‹

template <class T>
void TVector<T>::reserve(size_t required_capacity) {
    size_t new_capacity = calculate_capacity(required_capacity);
    if (new_capacity <= _capacity) {
        return;
    }
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];

    size_t new_size = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            new_data[new_size] = _data[i];
            new_states[new_size] = BUSY;
            new_size++;
        }
    }
    for (size_t i = new_size; i < new_capacity; ++i) {
        new_states[i] = EMPTY;
    }
    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
    _deleted = 0;
}


template <class T>
void TVector<T>::resize(size_t new_size, const T& filler) {
    if (new_size == _size) {
        return;
    }
    if (new_size < _size) {
        for (size_t i = new_size; i < _size; ++i) {
            if (_states[i] == BUSY) {              
                _states[i] = EMPTY;
            }
        }
    }
    else if (new_size > _size) {
        if (new_size > _capacity) {
            reserve(new_size);
        }
        for (size_t i = _size; i < new_size; ++i) {
            _data[i] = filler;
            _states[i] = BUSY;
        }
    }    
    _size = new_size;
}

template <class T>
void TVector<T>::shrink_to_fit() {
    size_t busy_count = _size;
    size_t new_capacity = (((busy_count + 15) / 15) * 15);
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];

    size_t new_size = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            new_data[new_size] = _data[i];
            new_states[new_size] = BUSY;
            new_size++;
        }
    }
    for (size_t i = new_size; i < new_capacity; ++i) {
        new_states[i] = EMPTY;
    }
    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
    _deleted = 0;
}

template <class T>
void TVector<T>::emplace(size_t pos, const T& value) {
    if (pos >= _capacity || _states[pos] != BUSY) {
        throw std::out_of_range("Invalid position or element is not busy");
    }
    _data[pos] = value; 
}

template <class T>
void TVector<T>::assign(const T* vec, size_t n) {
    clear(); 
    reserve(n); 
    for (size_t i = 0; i < n; ++i) {
        push_back(vec[i]); 
    }
}

template <class T>
void TVector<T>::clear() noexcept {
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            _states[i] = EMPTY;
        }
    }
    //delete[] _data;
    _size = 0;
    _deleted = 0;
}

template <class T>
bool TVector<T>::is_full() const noexcept {
    return ((_size + _deleted) >= _capacity);
}

template <class T>
bool TVector<T>::is_empty() const noexcept {
    return (_size == 0);
}

//¬—“¿¬ ¿

template <class T>
void TVector<T>::push_back(const T& value) {
    if (is_full()) {
        reserve(_capacity + 15);
    }

    for (size_t i = _size; i < _capacity; ++i) {
        if (_states[i] == EMPTY || _states[i] == DELETED) {
            _data[i] = value;
            _states[i] = BUSY;
            _size++;
            if (_states[i] == DELETED) {
                _deleted--;
            }
            return;
        }
    }
}


template <class T>
void TVector<T>::push_front(const T& value) {
    if (is_full()) {
        reserve(_capacity + 15);
    }

    if (_states[0] == DELETED) {
        _data[0] = value;
        _states[0] = BUSY;
        _size++;
        _deleted--;
        return;
    }

    for (size_t i = _capacity - 1; i > 0; --i) {
        if (_states[i - 1] != EMPTY) {
            _data[i] = _data[i - 1];
            if (_states[i - 1] == BUSY) {
                _states[i] = BUSY;
            } else if (_states[i - 1] == DELETED) {
                _states[i] = DELETED;
            }
            _states[i - 1] = EMPTY;
        }
    }

    _data[0] = value;
    _states[0] = BUSY;
    _size++;
}

template <class T>
void TVector<T>::insert(size_t pos, const T& value) {
    if (pos > _size) {
        throw std::out_of_range("Invalid position");
    }
    
    if (is_full()) {
        reserve(_capacity + 15);
    }

    if (_states[pos] == DELETED) {
        _data[pos] = value;
        _states[pos] = BUSY;
        _size++;
        _deleted--;
        return;
    }

    for (size_t i = _capacity - 1; i > pos; --i) {
        if (_states[i - 1] != EMPTY) {
            _data[i] = _data[i - 1];
            if (_states[i - 1] == BUSY) {
                _states[i] = BUSY;
            }
            else if (_states[i - 1] == DELETED) {
                _states[i] = DELETED;
            }
            _states[i - 1] = EMPTY;
        }
    }

    _data[pos] = value;
    _states[pos] = BUSY;
    ++_size;
}

template <class T>
void TVector<T>::insert(const Iterator& it, const T& value) {
    if (is_full()) {
        reserve(_capacity + 15);
    }
    
    /*if (it == end()) {
        push_back(value);
        return;
    }*/
    size_t pos = it.get_index();
    if (pos >= _capacity || _states[pos] != BUSY) {
        throw std::out_of_range("Invalid position");
    }

    if (_states[pos] == DELETED) {
        _data[pos] = value;
        _states[pos] = BUSY;
        _size++;
        _deleted--;
        return;
    }

    for (size_t i = _capacity - 1; i > pos; --i) {
        if (_states[i - 1] != EMPTY) {
            _data[i] = _data[i - 1];
            if (_states[i - 1] == BUSY) {
                _states[i] = BUSY;
            }
            else if (_states[i - 1] == DELETED) {
                _states[i] = DELETED;
            }
            _states[i - 1] = EMPTY;
        }
    }

    _data[pos] = value;;
    _states[pos] = BUSY;
    _size++;
}

template <class T>
void TVector<T>::insert(Iterator start, size_t count, const T& value) {
    size_t pos = start.get_index();
    reserve(_size + count + 15);
    for (size_t i = _capacity - 1; i > pos + count - 1; --i) {
        if (_states[i - count] != EMPTY) {
            _data[i] = _data[i - count];
            if (_states[i - count] == BUSY) {
                _states[i] = BUSY;
            }
            else if (_states[i - count] == DELETED) {
                _states[i] = DELETED;
            }
            _states[i - count] = EMPTY;
        }
    }

    for (size_t i = pos; i < pos + count; ++i) {
        _data[i] = value;
        _states[i] = BUSY;
        _size++;
    }
}

//”ƒ¿À≈Õ»≈

template <class T>
void TVector<T>::pop_back() {
    if (is_empty()) {
        throw std::out_of_range("empty");
    }
    size_t last_busy = -1;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            last_busy = i;
        }
    }
    if (last_busy == _capacity) {
        return;
    }
    _states[last_busy] = EMPTY;
    _size--;
}

template <class T>
void TVector<T>::pop_front() {
    if (is_empty()) {
        throw std::out_of_range("empty");
    }
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            _states[i] = DELETED;
            _size--;
            _deleted++;

            if (_deleted * 100 > ((_size + _deleted) * 15)) {
                shrink_to_fit();
            }
            break;
        }
    }
}

template <class T>
void TVector<T>::erase(size_t pos) {
    if (pos >= _capacity || _states[pos] != BUSY) {
        throw std::out_of_range("Invalid position");
    }
    _states[pos] = DELETED;
    _size--;
    _deleted++;
    if (_deleted * 100 > ((_size + _deleted) * 15)) {
        shrink_to_fit();
    }
}

template <class T>
void TVector<T>::erase(const Iterator& it) {
    size_t pos = it.get_index();
    if (pos >= _capacity || _states[pos] != BUSY) {
        throw std::out_of_range("invalid position");
    }

    _states[pos] = DELETED;
    _size--;
    _deleted++;
    if (_deleted * 100 > ((_size + _deleted) * 15)) {
        shrink_to_fit();
    }
}

template <class T>
void TVector<T>::erase(Iterator start, Iterator end) {
    if (start.get_index() > end.get_index()) {
        throw std::invalid_argument("Invalid range");
    }
    for (size_t i = start.get_index(); i < end.get_index(); ++i) {
        if (_states[i] == BUSY) {
            _states[i] = DELETED;
            _size--;
            _deleted++;
        }
    }
    if (_deleted * 100 > ((_size + _deleted) * 15)) {
        shrink_to_fit();
    }
}

template <class T>
void TVector<T>::erase(Iterator start, size_t count) {
    if ((start.get_index() + count) >= _capacity) {
        throw std::invalid_argument("Invalid range");
    }
    for (size_t i = start.get_index(); i < (start.get_index() + count); ++i) {
        if (_states[i] == BUSY) {
            _states[i] = DELETED;
            _size--;
            _deleted++;
        }
    }
    if (_deleted * 100 > ((_size + _deleted) * 15)) {
        shrink_to_fit();
    }
}

//¬—œŒÃŒ√¿“≈À‹Õ€≈ ‘”Õ ÷»»

template <class T>
size_t TVector<T>::calculate_capacity(size_t required_capacity) const {
    if (required_capacity == 0) {
        return 0;
    }
    return (((required_capacity + (STEP_OF_CAPACITY - 1)) / STEP_OF_CAPACITY) * STEP_OF_CAPACITY);
}

template <class T>
void fisher_yates_shuffle(TVector<T>& vec) {
    vec.shrink_to_fit();
    size_t size = vec.size();

    srand(time(0));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
    }
}

template <class T>
void quick_sort(TVector<T>& vec, int left, int right) {   
    vec.shrink_to_fit();
    int pivot = vec[(left + right) / 2];
    int i = left, j = right; 

    while (i <= j) {
        while (vec[i] < pivot) i++;
        while (vec[j] > pivot) j--;
        if (i <= j) {
            int temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quick_sort(&vec, left, j);
    }
    if (i < right) {
        quick_sort(&vec, i, right);
    }
}

template <class T>
int find_first(const TVector<T>& vec, const T& value) {
    int index = 0;
    for (size_t i = 0; i < vec._capacity; ++i) {
        if (vec._states[i] == BUSY) {
            if (vec._data[i] == value) {
                return index;
            }
            index++;
        }
    }
    return -1;
}


template <class T>
int find_last(const TVector<T>& vec, const T& value) {
    int last_found = -1;
    int index = 0;
    for (size_t i = 0; i < vec._capacity; ++i) {
        if (vec._states[i] == BUSY) {
            if (vec._data[i] == value) {
                last_found = index;
            }
            index++;
        }
    }
    return last_found;
}

template <class T>
int* find_all(const TVector<T>& vec, const T& value) {
    size_t out_size = 0;
    for (size_t i = 0; i < vec._capacity; ++i) {
        if (vec._states[i] == BUSY && vec._data[i] == value) {
            out_size++;
        }
    }

    if (out_size == 0) return nullptr;

    int* result = new int[out_size];
    int index = 0;
    size_t result_index = 0;

    for (size_t i = 0; i < vec._capacity; ++i) {
        if (vec._states[i] == BUSY) {
            if (vec._data[i] == value) {
                result[result_index++] = index;
            }
            index++;
        }
    }

    return result;
}