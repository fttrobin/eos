/**
 * @author Gracjan Olbinski <gracjan.olbinski@gmail.com>
 */

#include <vector>

namespace eos
{

template <
    typename T,
    typename Compare = std::equal<T>,
    typename Alloc = std::allocator<T>
    >
class unique_vector
{
    typedef          std::vector<T, Alloc>                storage_type;
public:
    typedef typename storage_type::value_type             value_type;
    typedef          Compare                              value_compare;
    typedef typename storage_type::allocator_type         allocator_type;
    typedef typename allocator_type::reference            reference;
    typedef typename allocator_type::const_reference      const_reference;
    typedef typename allocator_type::pointer              pointer;
    typedef typename allocator_type::const_pointer        const_pointer;
    typedef typename storage_type::iterator               iterator;
    typedef typename storage_type::const_iterator         const_iterator;
    typedef typename storage_type::reverse_iterator       reverse_iterator;
    typedef typename storage_type::const_reverse_iterator const_reverse_iterator;
    typedef typename storage_type::difference_type        difference_type;
    typedef typename storage_type::size_type              size_type;

    explicit unique_vector(const value_compare& comp = value_compare(),
                           const allocator_type& alloc = allocator_type())
    : comp_(comp)
    , storage_(storage)
    {
    }

    template <class InputIterator>
    unique_vector(InputIterator first, InputIterator last,
                  const value_compare& comp = value_compare(),
                  const allocator_type& alloc = allocator_type())
    : comp_(comp)
    , storage_(storage)
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

    iterator end()
    {
        return storage_.end();
    }

    const_iterator end() const
    {
        return storage_.end();
    }

    std::pair<iterator, bool> push_back(const value_type& val)
    {
        return std::make_pair(begin(), true);
    }

    

private:
    value_compare comp_;
    storage_type  storage_;
};  // class unique_vector

}  // namespace eos
