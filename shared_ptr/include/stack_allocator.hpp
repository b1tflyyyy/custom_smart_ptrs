#pragma once

#ifndef STACK_ALLOCATOR_HPP
#define STACK_ALLOCATOR_HPP

#define ON_STACK_ALLOCATOR_LOGS 1

#include <cstdint>
#include <stdio.h>
#include <stdexcept>

template <typename T = void, std::size_t SIZE = 100> requires std::is_same_v<T, void>
class stack_allocator
{
    public:	
        typedef void* pointer;
        typedef std::size_t size_type;
		
        typedef std::uint8_t byte;
        typedef std::uint8_t value_type;
	
    private:
        byte m_memory[SIZE];
		
        byte* m_memory_ptr;
        byte* m_current_ptr;

        size_type m_memory_used;

    public:
        explicit stack_allocator() :
            m_memory_ptr(m_memory), m_memory_used(0)
        { }

        ~stack_allocator() noexcept 
        { }

        template <typename U>
        struct rebind
        {
            typedef stack_allocator<U, SIZE> other;
        };

        template <typename U>
        constexpr stack_allocator(const stack_allocator<U, SIZE>&) noexcept
        { }

        pointer allocate(size_type n)
        {	
            if (m_memory_used + n > SIZE)
            {
                throw std::runtime_error("Used all memory in allocator");
            }

#if ON_STACK_ALLOCATOR_LOGS
            printf("allocation call: address = %p, size = %zu\n", m_memory_ptr, n);	
#endif
            m_memory_used += n;

            m_current_ptr = m_memory_ptr;
            m_memory_ptr += n;

            return static_cast<pointer>(m_current_ptr);
        }
		
        // TODO: add normal deallocation
        void deallocate(pointer ptr, size_type n)
        { }
		
        template <typename U, typename... Args>
        void construct(U* ptr, Args&&... args)
        {
#if ON_STACK_ALLOCATOR_LOGS
            printf("custom construct\n");
#endif
            ::new(static_cast<pointer>(ptr)) U(std::forward<Args>(args)...);
        }	

        template <typename U, typename... Args>
        constexpr U* construct_at(byte* storage, Args&&... args)
        {
#if ON_STACK_ALLOCATOR_LOGS
            printf("custom construct_at\n");
#endif
            return ::new(static_cast<pointer>(storage)) U(std::forward<Args>(args)...);
        }
        
        template <typename U>
        constexpr void destroy_at(U* ptr)
        {
#if ON_STACK_ALLOCATOR_LOGS
            printf("custom destroy_at\n");
#endif
            ptr->~U();
        }

        template <typename U>
        void destroy(U* ptr)
        {
#if ON_STACK_ALLOCATOR_LOGS
            printf("custom destroy\n");
#endif
            ptr->~U();
        }

        const size_type get_memory_used() const 
        {
            return m_memory_used;
        }
};

template <typename T, typename U, std::size_t SIZE>
bool operator==(const stack_allocator<T, SIZE>&, const stack_allocator<U, SIZE>&)
{
    return true;
}

template <typename T, typename U, std::size_t SIZE>
bool operator!=(const stack_allocator<T, SIZE>&, const stack_allocator<U, SIZE>&)
{
    return false;
}

#endif
