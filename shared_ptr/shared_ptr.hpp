#pragma once

#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#define ON_LOGS 0

#include <cstddef>
#include <memory>
#include <iostream>

#include "stack_allocator.hpp"

// TODO: Think about own control block when we copying shared_ptrs and move
// TODO: add logs control here

namespace custom
{
	// default value for allocator - 30 bytes
    template <typename T, typename Alloc = stack_allocator<void, 30>>
    class shared_ptr
    {
        // shared_ptr typedef's
        private:
            typedef T* pointer;
            typedef T value_type;
            typedef T& reference;
		
        // allocator typedef's
        private:
            Alloc m_alloc;
            typedef std::allocator_traits<Alloc> m_alloc_traits;
			
        // control block typedef's
        private:
            struct control_block
            {
                std::size_t m_counter = -1;
                pointer m_root_ptr = nullptr;
            };
			
            typedef control_block* cb_ptr;
            typedef control_block cb_type;
			
            constexpr static std::size_t cb_size = sizeof(cb_type);
			
            // control block pointer
            cb_ptr cb;
		
        public:
            constexpr shared_ptr() noexcept
            {
#if ON_LOGS
                std::cout << "default ctor called\n";
#endif
                cb = static_cast<cb_ptr>(m_alloc_traits::allocate(m_alloc, cb_size));
                cb->m_counter = 1;
			}

            explicit shared_ptr(pointer ptr) 
            {
                cb = static_cast<cb_ptr>(m_alloc_traits::allocate(m_alloc, cb_size));

                cb->m_root_ptr = ptr;
                cb->m_counter = 1;
            }
			
            // think about own control_block 
            explicit shared_ptr(const shared_ptr& other) noexcept
            {
                cb = other.cb;
                ++cb->m_counter;
            }
			
            ~shared_ptr() noexcept
            {
                if (cb == nullptr)
                {
#if ON_LOGS
                    std::cout << "CB == NULLPTR\n";
#endif
                    return;
                }

                --cb->m_counter;
                if(cb->m_counter == 0)
                {
#if ON_LOGS
                    printf("deallocation of shared ptr: root ptr address = %p, counter = %zu, control_block address = %p\n", cb->m_root_ptr, cb->m_counter, cb);
#endif			
                    delete cb->m_root_ptr;
                    m_alloc_traits::deallocate(m_alloc, cb, cb_size);
                    return;
                }

#if ON_LOGS
                std::cout << "dtor skipped for object num: " << cb->m_counter << '\n';
#endif
            }

            explicit shared_ptr(shared_ptr&& other) noexcept
            {
#if ON_LOGS
                printf("move operator called, cb = %p, other.cb = %p\n", cb, other.cb);
#endif		
                cb = other.cb;
                other.cb = nullptr;
#if ON_LOGS			
                printf("move operator called, cb = %p, other.cb = %p\n", cb, other.cb);
#endif
            }

            explicit operator bool() const noexcept
            {
                return cb->m_root_ptr != nullptr;
            }

            shared_ptr<T, Alloc>& operator=(const shared_ptr<T, Alloc>& other) noexcept
            {
#if ON_LOGS
                std::cout << "operator=\n";
#endif		
                cb = other.cb;
                ++cb->m_counter;

                return *this;
            }

            reference operator*() const noexcept
            {
                return *cb->m_root_ptr;
            }

            pointer operator->() const noexcept
            {
                return cb->m_root_ptr;
            }
			
            pointer get() const noexcept 
            {
                return cb->m_root_ptr;
            }
			
            std::size_t use_count() const noexcept
            {
                return cb->m_counter;
            }
	};
	
    template <typename T, typename Alloc, typename... Args>
    shared_ptr<T, Alloc> make_shared(Args&&... args)
    {
        return shared_ptr<T, Alloc>(new T(std::forward<Args>(args)...));
    }

    template <typename T, typename Alloc, typename... Args>
    shared_ptr<T, Alloc> make_shared(Alloc alloc = Alloc(), Args&&... args)
    {
        T* ptr = static_cast<T*>(alloc.allocate(sizeof(T)));
        return shared_ptr<T, Alloc>(::new (ptr) T(std::forward<Args>(args)...));
    }
}

#endif
