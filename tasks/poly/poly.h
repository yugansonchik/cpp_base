#pragma once

#include <cstdint>
#include <map>
#include <sstream>

class Poly {
public:
    Poly();
    Poly(const std::initializer_list<int64_t>& initializer_list);
    Poly(const std::initializer_list<std::pair<int64_t, int64_t>>& initializer_pair_list);

    int64_t operator()(int64_t x) const;

    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;

    Poly operator-(const Poly& other) const;
    const Poly& operator-=(const Poly& other);

    Poly operator+(const Poly& other) const;
    const Poly& operator+=(const Poly& other);

    Poly operator-() const;

    Poly operator*(const Poly& other) const;
    const Poly& operator*=(const Poly& other);

    friend std::ostream& operator<<(std::ostream& os, const Poly& poly);

private:
    std::map<uint64_t, int64_t> poly_;

    void Normalize();
};