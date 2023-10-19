#pragma once

#ifndef CUSTOM_ALLOCATOR_HPP
#define CUSTOM_ALLOCATOR_HPP

#include <cstddef>

/* this allocator uses stack memory */
template <typename T, std::size_t SIZE>
class custom_allocator
{
	private:
		typedef T* pointer;
		typedef T value_type;

		typedef std::size_t size_type;

	private: 
		value_type m_memory[SIZE];
		pointer m_memory_ptr;

	public:
		explicit custom_allocator() :
			m_memory_ptr(m_memory)
		{ }

		~custom_allocator() = default;

		template <typename U>
		struct rebind
		{
			typedef custom_allocator<U, SIZE> other;
		};

		template <typename U>
		constexpr custom_allocator(const custom_allocator<U, SIZE>&) noexcept { }
		
		pointer allocate(std::size_t n)
		{
			return m_memory_ptr++;
		}

		void deallocate(pointer ptr, std::size_t n)
		{ }
};

#endif

template <typename T, typename U, std::size_t SIZE>
bool operator==(const custom_allocator<T, SIZE>&, const custom_allocator<U, SIZE>&) 
{
	return true;
}

template <typename T, typename U, std::size_t SIZE>
bool operator!=(const custom_allocator<T, SIZE>&, const custom_allocator<U, SIZE>&)
{
	return false;
}
