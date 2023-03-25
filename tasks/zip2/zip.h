#pragma once

#include <iterator>

// Реализуем шаблонный класс Zipped, который позволяет итерироваться одновременно по двум различным последовательностям
// и возвращать пары элементов, находящихся на одинаковых позициях.
// Класс принимает два итератора на начало и конец первой последовательности и
// два итератора на начало и конец второй последовательности.
// Класс также содержит функцию Zip, которая принимает на вход две последовательности и
// возвращает объект класса Zipped, созданный на основе этих последовательностей.

template<typename Iterator1, typename Iterator2>
class Zipped {
public:
    Zipped(Iterator1 begin1, Iterator1 end1, Iterator2 begin2, Iterator2 end2)
        : begin1_(begin1), end1_(end1), begin2_(begin2), end2_(end2) {}

    auto begin() const {
        return Iterator(begin1_, end1_, begin2_);
    }

    auto end() const {
        return Iterator(end1_, end1_, end2_);
    }

private:
    Iterator1 begin1_, end1_;
    Iterator2 begin2_, end2_;

    template<typename T1, typename T2>
    class Iterator {
    public:
        Iterator(T1 i1, T1 end1, T2 i2) : i1_(i1), end1_(end1), i2_(i2) {}

        bool operator!=(const Iterator& other) const {
            return i1_ != other.i1_ && i2_ != other.i2_;
        }

        auto operator*() const {
            return std::pair(*i1_, *i2_);
        }

        Iterator& operator++() {
            ++i1_;
            ++i2_;
            return *this;
        }

    private:
        T1 i1_, end1_;
        T2 i2_;
    };
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Zipped(std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
}