#pragma once

#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <memory>
#include <iostream>
#include <cstdint>
#include <type_traits>
#include <functional>

#include "stack_allocator.hpp"

namespace custom
{
#if defined(linux) || defined(__unix__) || defined(__linux__)
    typedef stack_allocator<void, 50> default_alloc_t;
#elif defined(_WIN32) || defined(WIN32)
    typedef stack_allocator<void, 100> default_alloc_t;
#endif

	// default value for alloc - 30 bytes
    template <typename T, typename Alloc = default_alloc_t>
    class shared_ptr
    {
        // shared_ptr typedef's
        private:
            typedef T* pointer;
            typedef T value_type;
            typedef T& reference;
		
        // alloc typedef's
        private:
            Alloc m_alloc;
            typedef std::allocator_traits<Alloc> m_alloc_traits;

        private:
            typedef std::function<void(pointer, std::size_t)> deleter_t;
			
        // control block typedef's
        private:
            struct control_block
            {
                std::size_t m_counter;
                pointer m_root_ptr;

                constexpr static std::size_t m_root_object_size = sizeof(std::remove_all_extents_t<T>);
                deleter_t m_deleter;

                explicit control_block(std::size_t counter, pointer root_ptr, deleter_t&& deleter) :
                    m_counter(counter),
                    m_root_ptr(root_ptr),
                    m_deleter(std::move(deleter))
                { }

                ~control_block() noexcept
                {
                    m_counter = -1;
                    m_root_ptr = nullptr;
                    m_deleter = nullptr;
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
                ::new (cb) control_block(1, nullptr, [](pointer ptr, std::size_t sz) -> void { delete ptr; });
			}

            explicit shared_ptr(pointer ptr, deleter_t&& deleter = [](pointer ptr, std::size_t sz) -> void { delete ptr; }) noexcept
            {
                cb = reinterpret_cast<cb_ptr>(m_alloc_traits::allocate(m_alloc, cb_size));
                ::new (cb) control_block(1, ptr, std::move(deleter));
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
                    cb->m_deleter(cb->m_root_ptr, cb->m_root_object_size);

                    cb->~control_block();
                    m_alloc_traits::deallocate(m_alloc, reinterpret_cast<m_alloc_traits::pointer>(cb), cb_size);
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
			
            [[nodiscard]] std::size_t use_count() const noexcept
            {
                return cb->m_counter;
            }
	};

    template <typename T, typename Alloc>
    class shared_ptr<T[], Alloc>
    {
        // shared_ptr typedef's
        private:
            typedef T* pointer;
            typedef T value_type;
            typedef T& reference;

        // alloc typedef's
        private:
            Alloc m_alloc;
            typedef std::allocator_traits<Alloc> m_alloc_traits;

    private:
        typedef std::function<void(pointer)> deleter_t;

        // control block typedef's
        private:
            struct control_block
            {
                std::size_t m_counter;
                pointer m_root_ptr;
                deleter_t m_deleter;

                explicit control_block(std::size_t counter, pointer root_ptr, deleter_t&& deleter) :
                    m_counter(counter),
                    m_root_ptr(root_ptr),
                    m_deleter(std::move(deleter))
                { }

                ~control_block() noexcept
                {
                    m_counter = -1;
                    m_root_ptr = nullptr;
                    m_deleter = nullptr;
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
                ::new (cb) control_block(1, nullptr, [](pointer ptr) -> void { delete[] ptr; });
            }

            explicit shared_ptr(pointer ptr, deleter_t&& deleter = [](pointer ptr) -> void { delete[] ptr; }) noexcept
            {
                cb = reinterpret_cast<cb_ptr>(m_alloc_traits::allocate(m_alloc, cb_size));
                ::new (cb) control_block(1, ptr, std::move(deleter));
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
                    cb->m_deleter(cb->m_root_ptr);

                    cb->~control_block();
                    m_alloc_traits::deallocate(m_alloc, reinterpret_cast<m_alloc_traits::pointer>(cb), cb_size);
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

            reference operator[](std::ptrdiff_t idx) const
            {
                return cb->m_root_ptr[idx];
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

            [[nodiscard]] std::size_t use_count() const noexcept
            {
                return cb->m_counter;
            }
    };

    template <typename T,
              typename Alloc = default_alloc_t,
              typename = std::enable_if_t<!std::is_array_v<T>>,
              typename... Args>
    shared_ptr<T, Alloc> make_shared(Args&&... args)
    {
        return shared_ptr<T, Alloc>(::new T(std::forward<Args>(args)...));
    }

    template <typename T, typename Alloc = default_alloc_t> requires std::is_array_v<T>
    shared_ptr<T, Alloc> make_shared(std::size_t N)
    {
        return shared_ptr<T, Alloc>(::new std::remove_all_extents_t<T>[N] { });
    }
}

#endif
