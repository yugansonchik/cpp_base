#include "cow_string.h"

CowString::CowString(std::string_view str) {
    store_ = std::make_shared<Object>(str);
}
CowString::CowString(const CowString& other) {
    store_ = other.store_;
}
CowString::CowString(CowString&& other) {
    std::swap(store_, other.store_);
}
CowString& CowString::operator=(const CowString& other) {
    store_ = other.store_;
    return *this;
}
CowString& CowString::operator=(CowString&& other) {
    std::swap(store_, other.store_);
    return *this;
}
char** CowString::GetData() const {
    return &store_->store;
}
Iterator CowString::begin() {
    Iterator tmp(store_);
    return tmp;
}
Iterator CowString::end() {
    Iterator tmp(store_);
    for (size_t i = 0; i < store_->size; ++i) {
        ++tmp;
    }
    return tmp;
}
ConstIterator CowString::begin() const {
    ConstIterator tmp(store_);
    return tmp;
}
ConstIterator CowString::end() const {
    ConstIterator tmp(store_);
    for (size_t i = 0; i < store_->size; ++i) {
        ++tmp;
    }
    return tmp;
}
CowString::~CowString()=default;
Aproxy CowString::operator[](size_t position) {
    return Aproxy(store_->store[position], store_);
}
char CowString::At(size_t position) const {
    return store_->store[position];
}
CowString CowString::operator+(const CowString& other) {
    CowString res(*this);
    res.store_ = std::make_shared<Object>(*store_, *other.store_);
    return res;
}
CowString& CowString::operator+=(const CowString& other) {
    std::shared_ptr<Object> tmp = std::make_shared<Object>(*store_, *other.store_);
    store_ = tmp;
    return *this;

}
bool CowString::operator==(const CowString& other) {
    if (store_->size != other.store_->size) {
        return false;
    }
    for (size_t i = 0; i < store_->size; ++i) {
        if (store_->store[i] != other.store_->store[i]) {
            return false;
        }
    }
    return true;
}
bool CowString::operator!=(const CowString& other) {
    return !(*this == other);
}
CowString CowString::operator+(std::string_view str) {
    CowString tmp(str);
    return *this + tmp;
}
CowString& CowString::operator+=(std::string_view str) {
    CowString tmp(str);
    *this += tmp;
    return *this;
}
bool CowString::operator==(std::string_view str) const {
    if (store_->size != str.size()) {
        return false;
    }
    for (size_t i = 0; i < store_->size; ++i) {
        if (store_->store[i] != str[i]) {
            return false;
        }
    }
    return true;
}
bool CowString::operator!=(std::string_view str) {
    return !(*this == str);
}
CowString::operator std::string_view() {
    return store_->store;
}
Iterator::Iterator(std::shared_ptr<Object>& store) {
    position_ = 0;
    store_ = &store;
}
bool Iterator::operator!=(Iterator& other) {
    return position_ != other.position_;
}
Iterator& Iterator::operator++() {
    position_++;
    return *this;
}
Aproxy Iterator::operator*() {
    return Aproxy((*store_)->store[position_], *store_);
}
Aproxy::Aproxy(char& r, std::shared_ptr<Object>& obj) {
    m_ptr = &r;
    store = &obj;
}
void Aproxy::operator=(char n) {
    if (*m_ptr != n) {
        if ((*store).unique()) {
            *m_ptr = n;
        } else {
            char tmp_let = *m_ptr;
            *m_ptr = n;
            std::shared_ptr<Object> tmp = std::make_shared<Object>();
            tmp->store = new char[(*store)->size];
            for (size_t i = 0; i < (*store)->size; ++i) {
                tmp->store[i] = (*store)->store[i];
            }
            tmp->size = (*store)->size;
            *m_ptr = tmp_let;
            *store = tmp;
        }
    }
}
Aproxy::operator char() const {
    return *m_ptr;
}
ConstIterator::ConstIterator(const std::shared_ptr<Object>& store) {
    position_ = 0;
    store_ = &store;
}
bool ConstIterator::operator!=(ConstIterator& other) const {
    return position_ != other.position_;
}
ConstIterator& ConstIterator::operator++() {
    position_++;
    return *this;
}
char ConstIterator::operator*() const {
    return (*store_)->store[position_];
}
Object::Object()=default;
Object::Object(std::string_view str) {
    store = new char[str.size()];
    size = str.size();
    for (size_t i = 0; i < str.size(); ++i) {
        store[i] = str[i];
    }
}
Object::~Object() {
    delete[] store;
}
Object::Object(Object& first, Object& second) {
    store = new char[first.size + second.size];
    size = first.size + second.size;
    for (size_t i = 0; i < first.size; ++i) {
        store[i] = first.store[i];
    }
    size_t j = 0;
    for (size_t i = first.size; i < first.size + second.size; ++i, ++j) {
        store[i] = second.store[j];
    }
}