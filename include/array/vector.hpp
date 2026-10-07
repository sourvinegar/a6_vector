#pragma once
#include <algorithm> // max
#include <stdexcept> // out_of_range and invalid_argument
#include <utility> // move

namespace dsac::array {
///Simplified version of std::vector
/// @tparam T the element type    
template <typename T>
class Vector {
    private:
        /// capacity of the array
        int cap{0};

        /// number of actual entries
        int sz{0};

        /// pointer to array of elements
        T* data{nullptr};

    public:
        /// TODO: Constructs an empty vector
        Vector() = default;
       
        

        /// TODO: Constructs a vector with the specified number of elements
        /// Each Element is Value Initialized
        /// @param n number of elements in the vector
        /// @throw std::invalid_argument if n is negative
        Vector(int n)
        {
            if(n < 0)
            {
                throw std::invalid_argument("Invalid n value");
            }
            else
            {
                data = new T[n]{};
                cap = n;
                sz = n;
            }
        }


        /// TODO: Returns the current capacity of the underlying array
        /// @return the size of the underlying array
       int capacity() const {
        return cap;
       }

        /// TODO: Returns the number of elements stored
        /// @return the number of elements stored
        int size() const
        {
            return sz;
        }


        /// TODO: Tests whether the vector is empty.
        /// @return true if the vector is empty, false otherwise
        bool empty() const
        {
            return sz == 0;
        }


        /// TODO: Returns const reference to the element at index i;
        /// behavior is undefined if i is out of bounds
        /// @param i index of desired element
        /// @return element at index i
        const T& operator[](int i) const
        {
            return data[i];
        }


        /// TODO: Returns reference to the element at index i;
        /// behavior is undefined if i is out of bounds
        /// @param i index of desired element
        /// @return element at index i
        T& operator[](int i)
        {
            return data[i];
        }


        /// TODO: Returns const reference to the element at index i;
        /// raises out_of_range exception with invalid index
        /// @param i index of desired element
        /// @return element at index i
        /// @throw out_of_range exception if index is invalid for current vector
        const T& at(int i) const
        {
            if (i < 0 || i >= sz)
            throw std::out_of_range("Invalid index");
            return data[i]; 
        }


        /// TODO: Returns reference to the element at index i;
        /// raises out_of_range exception with invalid index
        /// @param i index of desired element
        /// @return element at index i
        /// @throw out_of_range exception if index is invalid for current vector
        T& at(int i)
        {
            if (i < 0 || i >= sz)
            throw std::out_of_range("Invalid index");
            return data[i];
        }


        /// TODO: Returns a const reference to the first element;
        /// behavior is undefined if vector is empty
        /// @return reference to first element
        const T& front() const
        {
            return data[0];
        }


        /// TODO: Returns a live reference to the first element;
        /// behavior is undefined if vector is empty
        /// @return reference to first element
        T& front()
        {
            return data[0];
        }


        /// TODO: Returns a const reference to the last element;
        /// behavior is undefined if vector is empty
        /// @return reference to last element
        const T& back() const
        {
            return data[sz-1];
        }


        /// TODO: Returns a live reference to the last element;
        /// behavior is undefined if vector is empty
        /// @return reference to last element
        T& back()
        {
            return data[sz-1];
        }


        /// TODO: Inserts an element at end of the vector
        /// @param elem   the new element
        void push_back(const T& elem)
        {
            if (sz == cap)
            reserve(std::max(1, 2 * cap)); //double
            data[sz++] = elem;
        }


        /// TODO: Removes the last element from the vector
        /// Calls shrink() after removing the element to reduce unused capacity when appropriate
        /// Behavior is undefined if the vector is empty
        void pop_back()
        {
            sz--;
        }


        /// TODO: Inserts an element at index i;
        /// behavior is undefined if i is out of bounds
        /// @param i      index at which new element should be placed
        /// @param elem   the new element
        void insert(int i, const T& elem)
        {
            if (sz == cap)
            reserve(std::max(1, 2 * cap));
            for (int k{sz-1}; k >= i; k--)
            //shift right starting end(avoid overwriting)
            data[k+1] = std::move(data[k]);
            data[i] = elem;
            sz++;
        }


        /// TODO: Removes the element at index i and shifts subsequent elements left
        /// Calls shrink() after removing the element to reduce unused capacity when appropriate
        /// Behavior is undefined if i is out of bounds
        /// @param i index of element to be removed
        void erase(int i)
        {
            for (int k{i+1}; k < sz; k++)
            //shift left
            data[k-1] = std::move(data[k]);
            sz--;
            shrink();
        }


        /// TODO: Requests that the vector capacity be at least as large as the indicated capacity
        /// The function has no effect if the current capacity is already large enough
        /// @param minimum the minimum capacity after the operation
        void reserve(int minimum)
        {
            if (cap < minimum) {
            T* temp{new T[minimum]};
            for (int k{0}; k < sz; k++)
            temp[k] = std::move(data[k]);
            delete[] data; // delete old array (if any)
            data = temp; // use new array
            cap = minimum; // new capacity
            }
        }
    

        /// TODO: Changes the capacity of the vector to new_cap
        /// Existing elements are preserved in their current order
        /// new_cap must be at least as large as the current size
        /// If new_cap is 0, no array is allocated
        /// @param new_cap the new capacity of the vector
        void reallocate(int new_cap)
        {
            if ((new_cap > 0) && (new_cap >= sz)) {
            T* temp{new T[new_cap]};
            for (int k{0}; k < sz; k++)
            temp[k] = std::move(data[k]);
            delete[] data; // delete old array (if any)
            data = temp; // use new array
            cap = new_cap; // new capacity
            }
        }


        /// TODO: Reduces the capacity of the vector when there is substantial unused space
        /// If the size is at most one-fourth of the current capacity, reduces the capacity by half
        /// This function does not reduce the capacity below 1
        void shrink()
        {
            int new_cap = cap/2;
            
            if(new_cap >= 1)
            {
            if (sz <= (cap/4)) {
            T* temp{new T[new_cap]};
            for (int k{0}; k < sz; k++)
            temp[k] = std::move(data[k]);
            delete[] data; // delete old array (if any)
            data = temp; // use new array
            cap = new_cap; // new capacity
            }
            }
        }

        
        /// TODO: Removes unused capacity from the vector
        /// Reduces the capacity to match the current size
        /// If the vector is empty, the capacity becomes 0
        /// The function has no effect if capacity is already equal to size
        void shrink_to_fit()
        {
          int new_cap = sz;
            
            T* temp{new T[new_cap]};
            for (int k{0}; k < sz; k++)
            temp[k] = std::move(data[k]);
            delete[] data; // delete old array (if any)
            data = temp; // use new array
            cap = new_cap; // new capacity
        }


    public:
        /// TODO: Destructor
        ~Vector() = default;

        /// Copy constructor will be defined later
        Vector(const Vector& other) = delete;

        /// Copy assignment will be defined later
        Vector& operator=(const Vector& other) = delete;

        /// Move constructor will be defined later
        Vector(Vector&& other) = delete;

        /// Move assignment will be defined later
        Vector& operator=(Vector&& other) = delete;
    
}; // Vector class

}  // namespace dsac::array
