#ifndef LIST_DUAL_LIST_H
#define LIST_DUAL_LIST_H

#include <utility>
#include <iterator>


template<class T>
struct Node {
    Node(T data, Node<T> *prev, Node<T> *next) :
            _data(std::move(data)),
            _prev(prev),
            _next(next) {}

    T _data{};
    Node *_prev = nullptr;
    Node *_next = nullptr;
};

template<class T>
class DualListIterator {
public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::bidirectional_iterator_tag;

    explicit DualListIterator(Node<T> *node) : _head(node) {}

    bool operator==(const DualListIterator<T> &other) {
        return _head == other._head;
    }

    bool operator!=(const DualListIterator<T> &other) {
        return _head != other._head;
    }

    DualListIterator<T> operator++() {
        _head = _head->_next;
        return *this;
    }

    DualListIterator<T> operator--() {
        _head = _head->_prev;
        return *this;
    }

    T &operator*() {
        return _head->_data;
    }

private:
    Node<T> *_head = nullptr;
};

template<class T>
class DualList {
public:
    DualList() = default;

    ~DualList();

    DualList(const DualList &) = delete;

    DualList &operator=(const DualList &) = delete;

    DualList(DualList &&) noexcept = delete;

    DualList &operator=(DualList &&) noexcept = delete;

    T &operator[](size_t pos);

    void insert(size_t pos, T var);

    void remove(size_t pos);

    void push_back(T var);

    void push_front(T var);

    void swap(size_t pos1, size_t pos2);

    void sort();

    DualListIterator<T> begin() {
        return DualListIterator<T>{_head};
    }

    DualListIterator<T> end() {
        return DualListIterator<T>{_tail->_next};
    }

    size_t size() {
        return _size;
    }

private:
    Node<T> *find_node(size_t pos);

    Node<T> *_head = nullptr;
    Node<T> *_tail = nullptr;
    size_t _size = 0;
};

template<class T>
T &DualList<T>::operator[](size_t pos) {
    Node<T> *target = find_node(pos);
    return target->_data;
}

template<class T>
void DualList<T>::insert(size_t pos, T var) {
    if (pos == 0) {
        push_front(std::move(var));
    } else if (pos == _size) {
        push_back(std::move(var));
    } else {
        Node<T> *target = find_node(pos);
        auto *elem = new Node<T>(std::move(var), nullptr, nullptr);
        elem->_next = target;
        elem->_prev = target->_prev;
        target->_prev->_next = elem;
        target->_prev = elem;
        ++_size;
    }
}

template<class T>
void DualList<T>::remove(size_t pos) {
    --_size;
    if (_size == 0 && pos == 0) {
        delete _head;
        _tail = nullptr;
        _head = nullptr;
        return;
    }
    if (pos == 0) {
        auto old_head = _head;
        _head = _head->_next;
        _head->_prev = nullptr;
        delete old_head;
    } else if (pos == _size) {
        auto old_tail = _tail;
        _tail = _tail->_prev;
        _tail->_next = nullptr;
        delete old_tail;
    } else {
        Node<T> *target = find_node(pos);
        target->_prev->_next = target->_next;
        target->_next->_prev = target->_prev;
        delete target;
    }
}

template<class T>
void DualList<T>::swap(size_t pos1, size_t pos2) {
    if (pos1 == pos2) {
        return;
    }
    Node<T> *elem1 = find_node(std::min(pos1, pos2));
    Node<T> *elem2 = find_node(std::max(pos1, pos2));

    if (elem1->_next == elem2) {
        if (elem1->_prev) {
            elem1->_prev->_next = elem2;
        } else {
            _head = elem2;
        }
        if (elem2->_next) {
            elem2->_next->_prev = elem1;
        } else {
            _tail = elem1;
        }

        elem1->_next = elem2->_next;
        elem2->_prev = elem1->_prev;

        elem1->_prev = elem2;
        elem2->_next = elem1;
    } else {
        if (elem1->_prev) {
            std::swap(elem1->_prev->_next, elem2->_prev->_next);
        } else {
            elem2->_prev->_next = elem1;
            _head = elem2;
        }
        if (elem2->_next) {
            std::swap(elem1->_next->_prev, elem2->_next->_prev);
        } else {
            elem1->_next->_prev = elem2;
            _tail = elem1;
        }
        std::swap(elem1->_next, elem2->_next);
        std::swap(elem1->_prev, elem2->_prev);
    }
}

template<class T>
void DualList<T>::sort() {
    auto pos_max = [this](size_t l, size_t r) {
        size_t pos_max = l;
        for (size_t i = l + 1; i < r; ++i) {
            if (operator[](i) > operator[](pos_max)) {
                pos_max = i;
            }
        }
        return pos_max;
    };

    for (size_t i = 0; i < _size - 1; ++i) {
        size_t pos = pos_max(i, _size);
        swap(i, pos);
    }
}

template<class T>
void DualList<T>::push_back(T var) {
    if (_size++ == 0) {
        _head = new Node<T>{std::move(var), nullptr, nullptr};
        _tail = _head;
    } else {
        _tail->_next = new Node<T>{std::move(var), _tail, nullptr};
        _tail = _tail->_next;
    }
}

template<class T>
void DualList<T>::push_front(T var) {
    if (_size++ == 0) {
        _head = new Node<T>{std::move(var), nullptr, nullptr};
        _tail = _head;
    } else {
        _head->_prev = new Node<T>{std::move(var), nullptr, _head};
        _head = _head->_prev;
    }
}

template<class T>
Node<T> *DualList<T>::find_node(size_t pos) {
    Node<T> *target = _head;
    for (size_t i = 0; i < pos; ++i) {
        target = target->_next;
    }
    return target;
}

template<class T>
DualList<T>::~DualList() {
    while (_tail) {
        auto old_tail = _tail;
        _tail = _tail->_prev;
        delete old_tail;
    }
}


#endif //LIST_DUAL_LIST_H
