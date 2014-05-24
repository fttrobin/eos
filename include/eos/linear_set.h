/**
 * @author Gracjan Olbinski <gracjan.olbinski@gmail.com>
 */


#ifndef EOS_LINEAR_SET_H_
#define EOS_LINEAR_SET_H_

#include <vector>
#include <algorithm>
#include <functional>
#include <initializer_list>

namespace eos
{

template <
    typename Key,
    typename Compare = std::less<Key>,
    typename Alloc = std::allocator<Key>
    >
class linear_set
{
    typedef          std::vector<Key, Alloc>                storage_type;
public:
    typedef typename storage_type::value_type               key_type;
    typedef typename storage_type::value_type               value_type;
    typedef          Compare                                key_compare;
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

    explicit linear_set(const key_compare& comp = key_compare(),
                        const allocator_type& alloc = allocator_type())
    : comp_(comp)
    , storage_(alloc)
    {
    }

    template <class InputIterator>
    linear_set(InputIterator first, InputIterator last,
               const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
    : comp_(comp)
    , storage_(alloc)
    {
        std::copy(first, last, std::inserter(*this, begin()));
    }

    linear_set(const linear_set& other)
    : comp_(other.comp_)
    , storage_(other.storage_)
    {
    }

    linear_set(std::initializer_list<value_type> il,
               const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
    : comp_(comp)
    , storage_(il, alloc)
    {
        std::stable_sort(begin(), end(), comp_);
    }

    ~linear_set()
    {
    }

    linear_set& operator=(const linear_set& other)
    {
        comp_    = other.comp_;
        storage_ = other.storage_;
    }

    linear_set& operator=(std::initializer_list<value_type> il)
    {
        storage_type(il).swap(storage_);
        std::stable_sort(begin(), end(), comp_);
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

    bool empty() const noexcept
    {
        return storage_.empty();
    }

    size_type size() const noexcept
    {
        return storage_.size();
    }

    size_type max_size() const noexcept
    {
        return storage_.max_size();
    }

    std::pair<iterator, bool> insert(const value_type& val)
    {
        iterator it = lower_bound(val);
        if ( it == end() )
        {
            storage_.push_back(val);
            return std::make_pair(--end(), true);
        }
        if ( !comp_(val, *it) )
        {
            return std::make_pair(it, false);
        }
        else
        {
            it = insert_at(it, val);
            return std::make_pair(it, true);
        }
    }

    iterator insert(iterator position, const value_type& val)
    {
        position = insert_at(position, val);
        std::stable_sort(begin(), end(), comp_);
        if ( *position == val )
        {
            return position;
        }
        else
        {
            return find(val);
        }
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        std::copy(first, last, std::inserter(*this, begin()));
    }

    void erase(iterator position)
    {
        storage_.erase(position);
    }

    size_type erase(const value_type& val)
    {
        iterator it = find(val);
        if ( it != end() )
        {
            erase(it);
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void erase(iterator first, iterator last)
    {
        storage_.erase(first, last);
    }

    void swap(linear_set& other)
    {
        storage_.swap(other.storage_);
    }

    void clear()
    {
        storage_.clear();
    }

    iterator find(const value_type& val)
    {
        iterator it = lower_bound(val);
        if ( it != end() && !(val < *it) )
        {
            return it;
        }
        else
        {
            return end();
        }
    }
    
    const_iterator find(const value_type& val) const
    {
        const_iterator it = lower_bound(val);
        if ( it != end() && !(val < *it) )
        {
            return it;
        }
        else
        {
            return end();
        }
    }

    size_type count(const value_type& val) const
    {
        return ( find(val) != end() ) ? 1 : 0;
    }

    key_compare key_comp() const
    {
        return comp_;
    }

    value_compare value_comp() const
    {
        return comp_;
    }

    iterator lower_bound(const value_type& val)
    {
        return std::lower_bound(begin(), end(), val, comp_);
    }

    const_iterator lower_bound(const value_type& val) const
    {
        return std::lower_bound(begin(), end(), val, comp_);
    }

    iterator upper_bound(const value_type& val)
    {
        return std::upper_bound(begin(), end(), val, comp_);
    }

    const_iterator upper_bound(const value_type& val) const
    {
        return std::upper_bound(begin(), end(), val, comp_);
    }

    std::pair<iterator, iterator> equal_range(const value_type& val)
    {
        return std::equal_range(begin(), end(), val, comp_);
    }

    std::pair<const_iterator, const_iterator> equal_range(const value_type& val) const
    {
        return std::equal_range(begin(), end(), val, comp_);
    }

    allocator_type get_allocator() const
    {
        return storage_.get_allocator();
    }

private:
    iterator insert_at(iterator position, const value_type& val)
    {
        difference_type count = std::distance(begin(), position);
        storage_.emplace_back();
        position = begin();
        std::advance(position, count);
        std::copy_backward(position, --end(), end());
        *position = val;
        return position;
    }

    key_compare     comp_;
    storage_type    storage_;
};  // class linear_set

}  // namespace eos

#endif  // EOS_LINEAR_SET_H_
