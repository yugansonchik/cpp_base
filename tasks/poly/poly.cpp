#include "poly.h"

#include <vector>

Poly::Poly() {
    poly_.clear();
}
Poly::Poly(const std::initializer_list<int64_t>& initializer_list) {
    size_t i = 0;
    for (int64_t a : initializer_list) {
        if (a != 0) {
            poly_[i] = a;
        }
        i++;
    }
}
Poly::Poly(const std::initializer_list<std::pair<int64_t, int64_t>>& initializer_pair_list) {
    for (auto [i, a] : initializer_pair_list) {
        if (a != 0) {
            poly_[i] = a;
        }
    }
}
int64_t Poly::operator()(int64_t x) const {
    int64_t y = 0;
    size_t j = 0;
    int64_t xj = 1;
    for (auto [i, a] : poly_) {
        while (j < i) {
            xj *= x;
            j++;
        }
        y += static_cast<int64_t>(a) * xj;
    }
    return y;
}
bool Poly::operator==(const Poly& other) const {
    return poly_ == other.poly_;
}
bool Poly::operator!=(const Poly& other) const {
    return poly_ != other.poly_;
}
Poly Poly::operator-(const Poly& other) const {
    Poly res(*this);
    res -= other;
    return res;
}
const Poly& Poly::operator-=(const Poly& other) {
    for (auto [i, a] : other.poly_) {
        if (!poly_.contains(i)) {
            poly_[i] = -a;
        } else {
            poly_[i] -= a;
            if (poly_[i] == 0) {
                poly_.erase(i);
            }
        }
    }
    return *this;
}
Poly Poly::operator+(const Poly& other) const {
    Poly res(*this);
    res += other;
    return res;
}
const Poly& Poly::operator+=(const Poly& other) {
    for (auto [i, a] : other.poly_) {
        if (!poly_.contains(i)) {
            poly_[i] = +a;
        } else {
            poly_[i] += a;
            if (poly_[i] == 0) {
                poly_.erase(i);
            }
        }
    }
    return *this;
}
Poly Poly::operator-() const {
    Poly res(*this);
    for (auto [i, a] : poly_) {
        res.poly_[i] = -a;
    }
    return res;
}
Poly Poly::operator*(const Poly& other) const {
    Poly res;
    for (auto [i, a] : poly_) {
        for (auto [j, b] : other.poly_) {
            res.poly_[i + j] += a * b;
        }
    }
    res.Normalize();
    return res;
}
const Poly& Poly::operator*=(const Poly& other) {
    return *this = *this * other;
}
void Poly::Normalize() {
    erase_if(poly_, [](const auto& item) { return item.second == 0; });
}
std::ostream& operator<<(std::ostream& os, const Poly& poly) {
    os << "y = ";
    if (poly.poly_.empty()) {
        os << '0';
        return os;
    }
    auto it = poly.poly_.rbegin();
    size_t i = 0u;
    int64_t a = 0;
    std::tie(i, a) = *it;
    os << a << (i == 0 ? "" : "x^" + std::to_string(i));

    for (++it; it != poly.poly_.rend(); ++it) {
        std::tie(i, a) = *it;
        os << ' ';
        if (a < 0) {
            os << "- " << -a;
        } else {
            os << "+ " << a;
        }
    }
    return os;
}