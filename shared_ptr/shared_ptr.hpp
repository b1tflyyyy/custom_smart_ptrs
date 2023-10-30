#pragma once

#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <memory>
#include <iostream>

#include "stack_allocator.hpp"

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
			       std::cout << "default ctor called\n";

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
					std::cout << "CB == NULLPTR\n";
					return;
				}

				--cb->m_counter;
				if(cb->m_counter == 0)
				{
					printf("deallocation of shared ptr: root ptr address = %p, counter = %zu, control_block address = %p\n", cb->m_root_ptr, cb->m_counter, cb);
					
					delete cb->m_root_ptr;
					m_alloc_traits::deallocate(m_alloc, cb, cb_size);
					return;
				}
				std::cout << "dtor skipped for object num: " << cb->m_counter << '\n';
			}

			explicit shared_ptr(shared_ptr&& other) noexcept
			{
				printf("move operator called, cb = %p, other.cb = %p\n", cb, other.cb);
				
				cb = other.cb;
				other.cb = nullptr;
				
				printf("move operator called, cb = %p, other.cb = %p\n", cb, other.cb);
			}

			explicit operator bool() const noexcept
			{
				return cb->m_root_ptr != nullptr;
			}

			shared_ptr<T, Alloc>& operator=(const shared_ptr<T, Alloc>& other) noexcept
			{
				std::cout << "operator=\n";
				
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
}

#endif
