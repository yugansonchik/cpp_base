#pragma once

#include <iterator>


template <typename Iterator1, typename Iterator2>
class Zipped {
private:
    struct ZippedIterator {
        using iterator1 = typename std::iterator_traits<Iterator1>::value_type;
        using iterator2 = typename std::iterator_traits<Iterator2>::value_type;

        std::pair<Iterator1, Iterator2> cur_;

        ZippedIterator(Iterator1 a, Iterator2 b) : cur_{a, b} {}

        std::pair<iterator1, iterator2> operator*() {
            return {*cur_.first, *cur_.second};
        }

        ZippedIterator& operator++() {
            ++cur_.first;
            ++cur_.second;
            return *this;
        }

        bool operator!=(const ZippedIterator& other) const {
            return cur_.first != other.cur_.first && cur_.second != other.cur_.second;
        }
    };

    ZippedIterator beg_;
    ZippedIterator end_;

public:
    Zipped(Iterator1 a_begin, Iterator1 a_end, Iterator2 b_begin, Iterator2 b_end) : beg_{a_begin, b_begin}, end_{a_end, b_end} {}

    ZippedIterator begin() const {
        return beg_;
    }

    ZippedIterator end() const {
        return end_;
    }
};


template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Zipped(std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
}