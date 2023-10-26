#pragma once

#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <memory>
#include <iostream>

#include "stack_allocator.hpp"

// TODO: create make_shared func

namespace custom
{
	// default value for allocator - 30 bytes
	template <typename T, typename Alloc = stack_allocator<void, 30>>
	class shared_ptr
	{
		private:
			typedef T* pointer;
			typedef T value_type;

		private:
			Alloc m_alloc;
			typedef std::allocator_traits<Alloc> m_alloc_traits;
			
		private:
			struct control_block
			{
				std::size_t m_counter = -1;
				pointer m_root_ptr = nullptr;
			};

			control_block* cb;
		
		private:
			explicit shared_ptr(control_block* cb);

		public:
			explicit shared_ptr(pointer ptr) 
			{
				cb = static_cast<control_block*>(m_alloc_traits::allocate(m_alloc, sizeof(control_block)));

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
				std::cout << "dtor skipped for object num: " << cb->m_counter << '\n';
	
				if (cb == nullptr)
				{
					return;
				}

				--cb->m_counter;

				if(cb->m_counter == 0)
				{
					printf("deallocation of shared ptr: root ptr address = %p, counter = %zu, control_block address = %p\n", cb->m_root_ptr, cb->m_counter, cb);
					
					delete cb->m_root_ptr;
					m_alloc_traits::deallocate(m_alloc, cb, sizeof(control_block));
				}
			}

			explicit shared_ptr(shared_ptr&& other) noexcept
			{
				// TODO:
			}

			explicit operator bool() const noexcept
			{
				return cb->m_root_ptr != nullptr;
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
}

#endif
