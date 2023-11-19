#pragma once

#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <memory>
#include <iostream>
#include <cstdint>

#include "stack_allocator.hpp"

// TODO: add version for array

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

                ~control_block() noexcept
                {
                    m_counter = -1;
                    m_root_ptr = nullptr;
                }
            };
			
            typedef control_block* cb_ptr;
            typedef control_block cb_type;
			
            constexpr static std::size_t cb_size = sizeof(cb_type);
			
            // control block pointer
            cb_ptr cb = nullptr;
		
        public:
            constexpr shared_ptr() noexcept
            {
                cb = reinterpret_cast<cb_ptr>(m_alloc_traits::allocate(m_alloc, cb_size));
                cb->m_counter = 1;
			}

            explicit shared_ptr(pointer ptr) 
            {
                cb = reinterpret_cast<cb_ptr>(m_alloc_traits::allocate(m_alloc, cb_size));

                cb->m_root_ptr = ptr;
                cb->m_counter = 1;
            }
			
            explicit shared_ptr(const shared_ptr& other) noexcept
            {
                cb = other.cb;
                ++cb->m_counter;
            }
			
            ~shared_ptr() noexcept
            {
                if (cb == nullptr)
                {
                    return;
                }

                --cb->m_counter;
                if(cb->m_counter == 0)
                {
                    delete cb->m_root_ptr;

                    cb->~control_block();
                    m_alloc_traits::deallocate(m_alloc, reinterpret_cast<m_alloc_traits::pointer>(cb), cb_size);

                    return;
                }
            }

            explicit shared_ptr(shared_ptr&& other) noexcept
            {
                cb = other.cb;
                other.cb = nullptr;
            }

            explicit operator bool() const noexcept
            {
                return cb->m_root_ptr != nullptr;
            }

            shared_ptr& operator=(const shared_ptr& other) noexcept
            {
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
	
    // standard make_shared
    namespace sta
    {
        template <typename T, typename Alloc = stack_allocator<void, 30>, typename... Args>
        shared_ptr<T, Alloc> make_shared(Args&&... args)
        {
            return shared_ptr<T, Alloc>(new T(std::forward<Args>(args)...));
        }
    }
    
    // make shared with custom allocator (experimental implementation)
    namespace alc
    {
        template <typename T, typename Alloc = stack_allocator<void, 30>, typename... Args>
        shared_ptr<T, Alloc> make_shared(Alloc& alloc, Args&&... args)
        {
            T* storage = reinterpret_cast<T*>(alloc.allocate(sizeof(T)));
            return shared_ptr<T, Alloc>(::new (storage) T(std::forward<Args>(args)...));   
        }
    }
}

#endif
