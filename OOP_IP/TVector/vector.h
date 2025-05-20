#pragma once
#include <cstddef>
#include <iostream>
#include <Windows.h>

enum State {EMPTY, BUSY, DELETED};

template <class T>

class TVector {
private:
    T* _data;
	size_t _capacity;
	size_t _size;
	size_t _deleted;
	State* _states;
	
	bool is_full() const noexcept;
	void reallocate(size_t new_capacity);
	size_t find_free_spot() const;

    size_t calculate_capacity(size_t required_capacity) const;
    void reallocate_for_deleted();
    size_t find_first_busy() const;
public:
	class Iterator {
        T* _ptr;
        size_t _pos;
    public:
        Iterator(T* p, State* states, size_t pos, size_t cap);

        T& operator*();

        Iterator& operator++() {
            do {
                ++_pos;
                ++_ptr;
            } while ((_pos < _capacity) && (_states[_pos] != BUSY));
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
        
        /*Iterator operator+(Iterator it, size_t offset) {
            auto temp = it;
            for (size_t i = 0; i < offset; ++i) {
                ++temp;
            }
            return temp;
        }*/

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
                _capacity = other._capacity;
            }   
            return *this;
        } 

        size_t get_index() const noexcept {
            return _pos;
        }
    };

    class ConstIterator {
        T* _ptr;
        size_t _pos;
    public:
        ConstIterator(const T* p, const State* states, size_t pos, size_t cap);

        const T& operator*() const;

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

        /*ConstIterator operator+(ConstIterator it, size_t offset) {
            auto temp = it;
            for (size_t i = 0; i < offset; ++i) {
                ++temp;
            }
            return temp;
        }*/

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

   
    TVector();
    TVector(size_t size);
	TVector(const T* arr, size_t n);
    TVector(std::initializer_list<T> init, size_t n);
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
	
    void push_back(const T& value);
    void push_front(const T& value);
    void insert(size_t pos, const T& value);
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

    template <class U>
    friend void fisher_yates_shuffle(TVector<U>& vec);

    template <class U>
    friend void quick_sort(TVector<U>& vec);

    template <class U>
    friend int find_first(const TVector<U> &vec, const U& value);

    template <class U>
    friend int find_last(const TVector<U>& vec, const U& value);

    template <class U>
    friend int* find_all(const TVector<U>& vec, const U& value, size_t& out_size);
};



// ŒÕ—“–” “Œ–€ ¬≈ “Œ–¿

template <class T>
TVector<T>::TVector() : _data(nullptr), _capacity(0), _size(0), _deleted(0), _states(nullptr) {
    reserve(15);
}

template <class T>
TVector<T>::TVector(size_t size) : TVector() {
    resize(size);
}

template <class T>
TVector<T>::TVector(const T* arr, size_t n) : TVector() {
    reserve(calculate_capacity(n));
    for (size_t i = 0; i < n; ++i) {
        push_back(arr[i]);
    }
}

template <class T>
TVector<T>::TVector(std::initializer_list<T> init, size_t n) : TVector() {
    reserve(calculate_capacity(n));
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
        //else { throw std::invalid_argument("other is null"); }
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
                new (_data + i) T(other._data[i]); 
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
T& TVector<T>::operator[](size_t logical_index) {
    if (logical_index >= _size) {
        throw std::out_of_range("Index is out of range");
    }

    size_t current = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            if (current == logical_index) {
                return _data[i];
            }
            current++;
        }
    }
    throw std::logic_error("Internal error in operator[]");
}

template <class T>
const T& TVector<T>::operator[](size_t logical_index) const {
    if (logical_index >= _size) {
        throw std::out_of_range("Index is out of range");
    }

    size_t current = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            if (current == logical_index) {
                return _data[i];
            }
            current++;
        }
    }
    throw std::logic_error("Internal error in operator[]");
}


//»“≈–¿“Œ–

template <class T>
TVector<T>::Iterator::Iterator(T* p, State* states, size_t pos, size_t cap) : _ptr(p), _states(states), _pos(pos), _capacity(cap) {
    while (_pos < _capacity && _states[_pos] != BUSY) {
        ++_pos;
        ++_ptr;
    }
}

template <class T>
T& TVector<T>::Iterator::operator*() {
    if (_pos >= _capacity) {
        throw std::out_of_range("Invalid pos");
    }
    return *_ptr;
}

template <class T>
TVector<T>::ConstIterator::ConstIterator(const T* p, const State* states, size_t pos, size_t cap) : _ptr(p), _states(states), _pos(pos), _capacity(cap) {
    while (_pos < _capacity && _states[_pos] != BUSY) {
        ++_pos;
        ++_ptr;
    }
}

template <class T>
const T& TVector<T>::ConstIterator::operator*() const {
    if (_pos >= _capacity) {
        throw std::out_of_range("Invalid pos");
    }
    return *_ptr;
}




template <class T>
typename TVector<T>::Iterator TVector<T>::begin() noexcept {
    return Iterator(_data, _states, 0, _capacity);
}

template <class T>
typename TVector<T>::ConstIterator TVector<T>::begin() const noexcept {
    return ConstIterator(_data, _states, 0, _capacity);
}

template <class T>
typename TVector<T>::Iterator TVector<T>::end() noexcept {
    return Iterator(_data, _states, _capacity, _capacity);
}

template <class T>
typename TVector<T>::ConstIterator TVector<T>::end() const noexcept {
    return Iterator(_data, _states, _capacity, _capacity);
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
    Iterator it = begin();
    if (it == end()) {
        throw std::out_of_range("empty");
    }
    return *it;
}

template <class T>
const T& TVector<T>::front() const noexcept {
    ConstIterator it = begin();
    if (it == end()) {
        throw std::out_of_range("empty");
    }
    return *it;
}

template <class T>
T& TVector<T>::back() noexcept {
    Iterator it = end();
    if (it == begin()) {
        throw std::out_of_range("empty");
    }
    --it;
    return *it;
}

template <class T>
const T& TVector<T>::back() const noexcept {
    ConstIterator it = end();
    if (it == begin()) {
        throw std::out_of_range("empty");
    }
    --it;
    return *it;
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
T& TVector<T>::at(size_t logical_index) {
    if (logical_index >= _size) {
        throw std::out_of_range("Index is out of range");
    }
    return (*this)[logical_index]; 
}

template <class T>
const T& TVector<T>::at(size_t logical_index) const {
    if (logical_index >= _size) {
        throw std::out_of_range("Index is out of range");
    }
    return (*this)[logical_index]; 
}


//œ¿Ãﬂ“‹

template <class T>
void TVector<T>::reserve(size_t required_capacity) {
    size_t new_capacity = calculate_capacity(required_capacity);
    if (new_capacity <= _capacity) {
        return;
    }
    //T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));
    T* new_data = new T[new_capacity];
    
    State* new_states = new State[new_capacity];

    size_t new_size = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            new (new_data + new_size) T((_data[i])); //std::move
            new_states[new_size] = BUSY;
            new_size++;
        }
    }
    for (size_t i = new_size; i < new_capacity; ++i) {
        new_states[i] = EMPTY;
    }

    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            _data[i].~T();
        }
    }
    operator delete(_data);
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
    _deleted = 0;
}

template <class T> 
void TVector<T>::resize(size_t new_size, const T& filler) {
    if (new_size < _size) {
        for (size_t i = new_size; i < _size; ++i) {
            if (_states[i] == BUSY) {
                _data[i].~T();
                _states[i] = DELETED;
                _deleted++;
            }
        }
        _size = new_size;
    }
    else if (new_size > _size) {
        if (new_size > _capacity) {
            reserve(new_size);
        }
    }
    for (size_t i = _size; i < new_size; ++i) {
        new (_data + i) T(filler);
        _states[i] = BUSY;
    }
    _size = new_size;
}

template <class T>
void TVector<T>::reallocate(size_t required_capacity) {
    size_t new_capacity = _capacity == 0 ? 15 : _capacity;
    while (new_capacity < required_capacity) {
        new_capacity += 15;
    }
    T* new_data = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
    State* new_states = new State[new_capacity];
    size_t new_size = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            new (new_data + new_size) T(std::move(_data[i]));
            new_states[new_size] = BUSY;
            new_size++;
        }
    }
    for (size_t i = new_size; i < new_capacity; ++i) {
        new_states[i] = EMPTY;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == BUSY) {
            _data[i].~T();
        }
    }
    operator delete[](_data);
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
    _deleted = 0;
}

template <class T>
void TVector<T>::shrink_to_fit() {
    reallocate_for_deleted();
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
    reserve(n + 15); 
    for (size_t i = 0; i < n; ++i) {
        push_back(vec[i]); 
    }
}

template <class T>
void TVector<T>::clear() noexcept {
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            _data[i].~T(); 
            _states[i] = EMPTY;
        }
    }
    _size = 0;
    _deleted = 0;
}


template <class T>
size_t TVector<T>::find_free_spot() const {
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == DELETED) {
            return i;
        }
    }
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == EMPTY) {
            return i;
        }
    }
    throw std::logic_error("TVector is full");
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

    size_t pos = _size;
    while (pos < _capacity && _states[pos] != EMPTY && _states[pos] != DELETED) {
        ++pos;
    }
    if (pos >= _capacity) {
        pos = find_free_spot();
    }

    _data[pos] = value;
    _states[pos] = BUSY;
    ++_size;
    if ((_deleted > 0) && (_states[pos] == DELETED)) {
        --_deleted;
    }
}

template <class T>
void TVector<T>::push_front(const T& value) {
    if (is_full()) {
        reserve(_capacity + 15);
    }

    for (size_t i = _capacity - 1; i > 0; --i) {
        if (_states[i - 1] == BUSY) {
            _data[i] = std::move(_data[i - 1]);
            _states[i] = BUSY;
            _states[i - 1] = EMPTY;
        }
    }

    _data[0] = value;
    _states[0] = BUSY;
    ++_size;
}

template <class T>
void TVector<T>::insert(size_t pos, const T& value) {
    if (pos > _size) {
        throw std::out_of_range("Invalid position");
    }
    
    if (is_full()) {
        reserve(_capacity + 15);
    }

    for (size_t i = _capacity - 1; i > pos; --i) {
        if (_states[i - 1] == BUSY) {
            _data[i] = std::move(_data[i - 1]);
            _states[i] = BUSY;
            _states[i - 1] = EMPTY;
        }
    }

    _data[pos] = value;
    _states[pos] = BUSY;
    ++_size;
}

//”ƒ¿À≈Õ»≈

template <class T>
void TVector<T>::pop_back() {
    if (is_empty()) {
        throw std::out_of_range("empty");
    }
    size_t last_busy = find_first_busy();
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            last_busy = i;
        }
    }
    if (last_busy == _capacity) {
        return;
    }
    _data[last_busy].~T();
    _states[last_busy] = EMPTY;
    _size--;
}

template <class T>
void TVector<T>::pop_front() {
    if (is_empty()) {
        throw std::out_of_range("empty");
    }
    size_t first_busy = 0;
    for (size_t i = _capacity; i > first_busy; --i) {
        if (_states[i] == BUSY) {
            first_busy = i;
        }
    }
    if (first_busy == 0) {
        return;
    }
    _data[first_busy].~T();
    _states[first_busy] = EMPTY;
    _size--;
}

template <class T>
void TVector<T>::erase(size_t pos) {
    if (pos >= _capacity || _states[pos] != BUSY) {
        throw std::out_of_range("Invalid position");
    }
    _data[pos].~T();
    _states[pos] = DELETED;
    _size--;
    _deleted++;
    if (_deleted * 100 > ((_size + _deleted) * 15)) {
        reallocate_for_deleted();
    }
}

template <class T>
void TVector<T>::erase(const Iterator& it) {
    if (it == end()) {
        throw std::out_of_range("out of range");
    }
    size_t pos = it.get_index();
    if (pos >= _capacity || _states[pos] != BUSY) {
        throw std::out_of_range("invalid position");
    }

    _data[pos].~T();
    _states[pos] = DELETED;
    _size--;
    _deleted++;
    if (_deleted * 100 > ((_size + _deleted) * 15)) {
        reallocate_for_deleted();
    }
}

template <class T>
void TVector<T>::erase(Iterator start, Iterator end) {
    if (start.get_index() > end.get_index()) {
        throw std::invalid_argument("Invalid range");
    }
    for (size_t i = start.get_index(); i < end.get_index(); ++i) {
        if (_states[i] == BUSY) {
            _data[i].~T();
            _states[i] = DELETED;
            _size--;
            _deleted++;
        }
    }
    if (_deleted * 100 > ((_size + _deleted) * 15)) {
        reallocate_for_deleted();
    }
}

template <class T>
void TVector<T>::erase(Iterator start, size_t count) {
    if ((start.get_index() + count) >= _capacity) {
        throw std::invalid_argument("Invalid range");
    }
    for (size_t i = start.get_index(); i < (start.get_index() + count); ++i) {
        if (_states[i] == BUSY) {
            _data[i].~T();
            _states[i] = DELETED;
            _size--;
            _deleted++;
        }
    }
    if (_deleted * 100 > ((_size + _deleted) * 15)) {
        reallocate_for_deleted();
    }
}

//¬—œŒÃŒ√¿“≈À‹Õ€≈ ‘”Õ ÷»»

template <class T>
void TVector<T>::reallocate_for_deleted() {
    size_t busy_count = _size;
    size_t new_capacity = (((busy_count + 15) / 15) * 15);

    T* new_data = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
    State* new_states = new State[new_capacity];

    size_t new_size = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            new (new_data + new_size) T(std::move(_data[i]));
            new_states[new_size] = BUSY;
            new_size++;
        }
    }
    for (size_t i = new_size; i < new_capacity; ++i) {
        new_states[i] = EMPTY;
    }
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY || _states[i] == DELETED) {
            _data[i].~T();
        }
    }
    operator delete[](_data);
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_size;
    _deleted = 0;
}

template <class T>
size_t TVector<T>::find_first_busy() const {
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == BUSY) {
            return i;
        }
    }
    return _capacity;
}

template <class T>
size_t TVector<T>::calculate_capacity(size_t required_capacity) const {
    if (required_capacity == 0) {
        return 0;
    }
    return (((required_capacity + 14) / 15) * 15);
}

template <class U>
void fisher_yates_shuffle(TVector<U>& vec) {
    vec.shrink_to_fit();
    size_t new_size = vec.size();

    srand(time(0));
    for (int i = new_size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&vec[i], &vec[j]);
    }
}

template <class U>
void quick_sort(TVector<U>& vec) {  //???
    vec.shrink_to_fit();

    TVector<U> temp;
    for (size_t i = 0; i < vec.capacity(); i++) {
        if (vec._states[i] == BUSY) {
            temp.push_back(vec._data[i]);
        }
    }
    std::qsort(temp.begin(), temp.end());
    vec.clear();
    for (const auto& item : temp) {
        vec.push_back(item);
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

template <class U>
int find_first(const TVector<U>& vec, const U& value) {
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


template <class U>
int find_last(const TVector<U>& vec, const U& value) {
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

template <class U>
int* find_all(const TVector<U>& vec, const U& value, size_t& out_size) {
    out_size = 0;
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