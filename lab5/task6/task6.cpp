#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <initializer_list>

class vector final
{
private:
    double *arr;
    size_t capacity, size;

    void _resize(size_t new_capacity){
        double *resize;
        resize = new double[new_capacity];
        auto count = std::min(size, new_capacity);
        std::copy(arr, arr + count, resize);
        delete[] arr;
        arr = resize;
        capacity = new_capacity;
        size = count;
    }

public:
    class iterator final{
    private:
        double *_ptr;

    public:
        iterator(double *ptr) : _ptr{ptr} {}
        double const &operator*() const { return *_ptr; }
        double &operator*() { return *_ptr; }

        iterator& operator++()& {
            _ptr++;
            return *this;
        }

        iterator operator++(int){
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--()& {
            _ptr--;
            return *this;
        }

        iterator operator--(int){
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        iterator operator+(size_t shift) const {
            return iterator(_ptr + shift);
        }

        iterator& operator+=(size_t shift)& {
            _ptr += shift;
            return *this;
        }

        iterator operator-(size_t shift) const {
            return iterator(_ptr - shift);
        }

        iterator& operator-=(size_t shift)& {
            _ptr -= shift;
            return *this;
        }

        double *operator->() {
            return _ptr;
        }

        double const *operator->() const {
            return _ptr;
        }

        double& operator[](size_t shift)& {
            return *(_ptr + shift);
        }

        double operator[](size_t shift) const &{
            return *(_ptr + shift);
        }

        size_t operator-(const iterator &iter) const { return _ptr - iter._ptr; }
        bool operator==(const iterator &iter) const { return _ptr == iter._ptr; };
        bool operator!=(const iterator &iter) const { return _ptr != iter._ptr; };
        bool operator>(const iterator &iter) const { return _ptr > iter._ptr; };
        bool operator>=(const iterator &iter) const { return _ptr >= iter._ptr; };
        bool operator<(const iterator &iter) const { return _ptr < iter._ptr; };
        bool operator<=(const iterator &iter) const { return _ptr <= iter._ptr; };
    };

    vector(size_t count_elements, double default_value) : arr{new double[count_elements]},
                                                          size(count_elements),
                                                          capacity(count_elements)

    {
        std::fill_n(arr, count_elements, default_value);
    }

    vector(size_t count_elements) : vector(count_elements, 0.0) {}

    template <typename Iterator>
    vector(Iterator const begin, Iterator const end){
        auto distance = end - begin;
        arr = new double[distance];
        capacity = size = distance;
        std::copy(begin, end, arr);
    }

    vector(std::initializer_list<double> init_list) : capacity{init_list.size()}, size(init_list.size()),
                                                      arr{new double[init_list.size()]}
    {
        std::copy(init_list.begin(), init_list.end(), arr);
    }

    vector(const vector &v) : vector(v.begin(), v.end()) {};

    double& at(size_t index)& {
        if (index < 0 || index >= size)
            throw std::range_error("Out of range");

        return arr[index];
    }

    double const &at(size_t index) const &{
        if (index < 0 || index >= size)
            throw std::range_error("Out of range");

        return arr[index];
    }

    double &front()& {
        if (size == 0)
            throw std::range_error("Out of range");

        return arr[0];
    }

    double const &front() const & {
        if (size == 0)
            throw std::range_error("Out of range");

        return arr[0];
    }

    double &back()& {
        if (size == 0)
            throw std::range_error("Out of range");

        return arr[size - 1];
    }

    double const &back() const & { //небезопасные методы сделать безопасными
        if (size == 0)
            throw std::range_error("Out of range");

        return arr[size - 1];
    }

    double *data(){
        return arr;
    }

    double const *data() const{
        return arr;
    }

    bool empty() const { return !size; }

    void reserve(size_t num){
        if (num <= capacity)
            return;

        _resize(num);
    }

    size_t cap() const { return capacity; }
    size_t size1() const { return size; }

    void shrink_to_fit(){
        if (capacity <= size)
            return;

        _resize(size);
    }

    void clear() { size = 0; }

    void push_back(double elem){
        if (capacity == size)
        {
            _resize(capacity * 2);
        }
        arr[size++] = elem;
    }

    void pop_back(){
        if (size > 0)
            --size;
    }

    void resize(size_t new_size, double elem){
        size_t old_size = size;
        _resize(new_size);
        if (new_size > old_size)
        {
            std::fill(arr + old_size, arr + new_size, elem);
        }
        size = new_size;
    }

    void erase(size_t index){
        if (index >= size)
            return;

        for (size_t i = index; i < size - 1; ++i)
        {
            arr[i] = arr[i + 1];
        }
        --size;
    }

    void insert(size_t index, double elem){
        if (index > size)
        {
            throw std::range_error("Out of range");
        }
        if (size == capacity)
        {
            _resize(capacity * 2);
        }
        ++size;

        for (size_t i = size - 1; i > index; --i)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = elem;
    }

    bool operator==(vector const &v) const{
        if (size != v.size)
            return false;

        for (size_t i = 0; i < size; ++i)
        {
            if (arr[i] != v.arr[i])
                return false;
        }
        return true;
    }

    int operator<=>(vector const &v) const{
        for (size_t i = 0; i < size && i < v.size; ++i)
        {
            if (arr[i] - v.arr[i] < -__DBL_EPSILON__)
                return -1;
            if (arr[i] - v.arr[i] > __DBL_EPSILON__)
                return 1;
        }
        if (size > v.size)
        {
            return 1;
        }
        if (size < v.size)
            return -1;
        return 0;
    } //ordering type должен вернуть ()

    vector &operator=(vector const &v)& {
        if (this != &v)
        {
            vector tmp(v.begin(), v.end());
            std::swap(tmp.arr, this->arr);
            std::swap(tmp.capacity, this->capacity);
            std::swap(tmp.size, this->size);
        }
        return *this;
    }

    iterator begin() { return iterator(arr); }
    iterator end() { return iterator(arr + size1()); }

    const iterator begin() const { return iterator(arr); }
    const iterator end() const { return iterator(arr + size1()); }

    ~vector()
    {
        delete[] arr;
    }
};

void test_vector() {
    // Тестирование конструктора с количеством элементов
    vector v1(5, 1.5);
    std::cout << "v1: ";
    for (auto &val : v1) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Тестирование конструктора с initializer_list
    vector v2{2.3, 4.5, 6.7};
    std::cout << "v2: ";
    for (auto &val : v2) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Тестирование push_back и pop_back
    v2.push_back(8.9);
    std::cout << "v2 after push_back: ";
    for (auto &val : v2) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    v2.pop_back();
    std::cout << "v2 after pop_back: ";
    for (auto &val : v2) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Тестирование resize
    v1.resize(7, 3.3);
    std::cout << "v1 after resize: ";
    for (auto &val : v1) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Тестирование front и back
    std::cout << "v1.front(): " << v1.front() << "\n";
    std::cout << "v1.back(): " << v1.back() << "\n";

    // Тестирование at
    try {
        std::cout << "v1.at(2): " << v1.at(2) << "\n";
        std::cout << "v1.at(10): " << v1.at(10) << "\n"; // Должен выбросить исключение
    } catch (std::range_error &e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    // Тестирование insert
    v1.insert(2, 9.9);
    std::cout << "v1 after insert: ";
    for (auto &val : v1) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Тестирование erase
    v1.erase(2);
    std::cout << "v1 after erase: ";
    for (auto &val : v1) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Тестирование оператора сравнения
    vector v3{1.5, 3.3, 4.5};
    std::cout << "v1 == v3: " << (v1 == v3) << "\n";
    std::cout << "v1 <=> v3: " << (v1 <=> v3) << "\n";

    // Тестирование оператора присваивания
    vector v4 = v2;
    std::cout << "v4 (copy v2): ";
    for (auto &val : v4) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Тестирование reserve и shrink_to_fit
    v4.reserve(20);
    std::cout << "v4.capacity() after reserve: " << v4.cap() << "\n";

    v4.shrink_to_fit();
    std::cout << "v4.capacity() after shrink_to_fit: " << v4.cap() << "\n";

    // Тестирование clear и empty
    v4.clear();
    std::cout << "v4 empty? " << v4.empty() << "\n";
}

int main() {
    try {
        test_vector();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
