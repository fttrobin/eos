/**
 * @author Gracjan Olbinski <gracjan.olbinski@gmail.com>
 */

#include <vector>
#include <algorithm>
#include <functional>

namespace eos
{

template <
    typename T,
    typename Compare = std::equal_to<T>,
    typename Alloc = std::allocator<T>
    >
class unique_vector
{
    typedef          std::vector<T, Alloc>                  storage_type;
public:
    typedef typename storage_type::value_type               value_type;
    typedef          Compare                                value_compare;
    typedef typename storage_type::allocator_type           allocator_type;
    typedef typename allocator_type::reference              reference;
    typedef typename allocator_type::const_reference        const_reference;
    typedef typename allocator_type::pointer                pointer;
    typedef typename allocator_type::const_pointer          const_pointer;
    typedef typename storage_type::iterator                 iterator;
    typedef typename storage_type::const_iterator           const_iterator;
    typedef typename storage_type::reverse_iterator         reverse_iterator;
    typedef typename storage_type::const_reverse_iterator   const_reverse_iterator;
    typedef typename storage_type::difference_type          difference_type;
    typedef typename storage_type::size_type                size_type;

    explicit unique_vector(const value_compare& comp = value_compare(),
                           const allocator_type& alloc = allocator_type())
    : comp_(comp)
    , storage_(alloc)
    {
    }

    template <class InputIterator>
    unique_vector(InputIterator first, InputIterator last,
                  const value_compare& comp = value_compare(),
                  const allocator_type& alloc = allocator_type())
    : comp_(comp)
    , storage_(alloc)
    {
    }

    iterator begin() noexcept
    {
        return storage_.begin();
    }

    const_iterator begin() const noexcept
    {
        return storage_.begin();
    }

    const_iterator cbegin() const noexcept
    {
        return storage_.begin();
    }

    iterator end() noexcept
    {
        return storage_.end();
    }

    const_iterator end() const noexcept
    {
        return storage_.end();
    }

    const_iterator cend() const noexcept
    {
        return storage_.end();
    }

    reverse_iterator rbegin() noexcept
    {
        return storage_.rbegin();
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return storage_.rbegin();
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return storage_.crbegin();
    }

    reverse_iterator rend() noexcept
    {
        return storage_.rend();
    }

    const_reverse_iterator rend() const noexcept
    {
        return storage_.rend();
    }

    const_reverse_iterator crend() const noexcept
    {
        return storage_.crend();
    }

    size_type size() const noexcept
    {
        return storage_.size();
    }

    size_type max_size() const noexcept
    {
        return storage_.max_size();
    }

    bool empty() const noexcept
    {
        return storage_.empty();
    }

    size_type capacity() const noexcept
    {
        return storage_.capacity();
    }

    void reserve(size_type n)
    {
        storage_.reserve(n);
    }

    void shrink_to_fit()
    {
        storage_.shrink_to_fit();
    }

    reference operator[](size_type n)
    {
        return storage_[n];
    }

    const_reference operator[](size_type n) const
    {
        return storage_[n];
    }

    reference at(size_type n)
    {
        return storage_.at(n);
    }

    const_reference at(size_type n) const
    {
        return storage_.at(n);
    }

    reference front()
    {
        return storage_.front();
    }

    const_reference front() const
    {
        return storage_.front();
    }

    reference back()
    {
        return storage_.back();
    }

    const_reference back() const
    {
        return storage_.back();
    }

    value_type* data() noexcept
    {
        return storage_.data();
    }

    const value_type* data() const noexcept
    {
        return storage_.data();
    }

    std::pair<iterator, bool> push_back(const value_type& val)
    {
        iterator position = find(val);
        if ( position == end() )
        {
            storage_.push_back(val);
            return std::make_pair(--end(), true);
        }
        else
        {
            return std::make_pair(position, false);
        }
    }

    void pop_back()
    {
        storage_.pop_back();
    }

    iterator find(const value_type& val)
    {
        iterator first = begin(), last = end();
        for ( ; first != last; ++first )
        {
            if ( comp_(val, *first) )
            {
                return first;
            }
        }
        return last;
    }

    const_iterator find(const value_type& val) const
    {
        const_iterator first = begin(), last = end();
        for ( ; first != last; ++first )
        {
            if ( comp_(val, *first) )
            {
                return first;
            }
        }
        return last;
    }

private:
    value_compare   comp_;
    storage_type    storage_;
};  // class unique_vector

}  // namespace eos
