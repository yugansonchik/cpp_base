#pragma once

#include <string_view>
#include <string>
#include <memory>

class CowSrtring;

struct Object {
    char* store = nullptr;
    size_t size;

    Object();
    Object(std::string_view str);
    Object(Object& first, Object& second);
    ~Object();
};

struct Aproxy {
    char* m_ptr;
    std::shared_ptr<Object>* store;
    Aproxy(char& r, std::shared_ptr<Object>& cow);
    void operator=(char n);

    operator char() const;
};

class Iterator {
private:
    size_t position_;
    std::shared_ptr<Object>* store_;

public:
    Iterator(std::shared_ptr<Object>& store);
    bool operator!=(Iterator& other);
    Iterator& operator++();
    Aproxy operator*();
};

class ConstIterator {
    const std::shared_ptr<Object>* store_;
    size_t position_;

public:
    ConstIterator(const std::shared_ptr<Object>& store);
    bool operator!=(ConstIterator& other) const;
    ConstIterator& operator++();
    char operator*() const;
};

class CowString {
private:
    std::shared_ptr<Object> store_;
public:
    explicit CowString(std::string_view str);
    CowString(const CowString& other);
    CowString(CowString&& other);

    ~CowString();

    CowString& operator=(const CowString& other);
    CowString& operator=(CowString&& other);

    char** GetData() const;

    Iterator begin();  // NOLINT
    Iterator end();    // NOLINT

    ConstIterator begin() const;  // NOLINT
    ConstIterator end() const;    // NOLINT

    Aproxy operator[](size_t position);
    char At(size_t position) const;

    CowString operator+(const CowString& other);
    CowString& operator+=(const CowString& other);
    bool operator==(const CowString& other);
    bool operator!=(const CowString& other);

    CowString operator+(std::string_view str);
    CowString& operator+=(std::string_view str);
    bool operator==(std::string_view str) const;
    bool operator!=(std::string_view str);

    operator std::string_view();
};