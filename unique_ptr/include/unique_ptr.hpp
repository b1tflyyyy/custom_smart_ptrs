#pragma once

#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <type_traits>
#include <iostream>

// TODO: add google tests, add custom deleter

namespace custom
{
	template <typename T>
	class unique_ptr
	{
	private:
		typedef T* pointer;
		typedef T value_type;

    private:
		pointer m_root_ptr;

	public:
		explicit unique_ptr() noexcept :
			m_root_ptr(nullptr)
		{ }
		
		explicit unique_ptr(pointer ptr) noexcept :
			m_root_ptr(ptr)
		{ std::cout << "default ptr\n"; }
		
		explicit unique_ptr(const unique_ptr&) noexcept = delete;
		
		explicit unique_ptr(unique_ptr&& other) noexcept
		{
			this->m_root_ptr = other.m_root_ptr;
			other.m_root_ptr = nullptr;
		}

		~unique_ptr() noexcept
		{
			delete m_root_ptr;
		}

		unique_ptr& operator=(const unique_ptr&) = delete;
		
		explicit operator bool() const noexcept
		{
			return m_root_ptr != nullptr;
		}

		typename std::add_lvalue_reference_t<value_type> operator*() const noexcept(noexcept(*std::declval<pointer>()))
		{
			return *m_root_ptr;
		}	

		pointer operator->() const noexcept
		{
			return m_root_ptr;
		}

		pointer get() const noexcept
		{
			return m_root_ptr;
		}
	};

	template <typename T>
	class unique_ptr<T[]>
	{
	private:
		typedef T* pointer;
		typedef T value_type;

	private:
		pointer m_root_ptr;

	public:
		explicit unique_ptr() noexcept :
			m_root_ptr(nullptr)
		{ }

		explicit unique_ptr(pointer ptr) noexcept :
			m_root_ptr(ptr)
		{ std::cout << "smart ptr array\n"; }

		explicit unique_ptr(const unique_ptr&) noexcept = delete;

		explicit unique_ptr(unique_ptr&& other) noexcept
		{
			this->m_root_ptr = other.m_root_ptr;
			other.m_root_ptr = nullptr;
		}

		~unique_ptr() noexcept
		{
			delete[] m_root_ptr;
		}

		unique_ptr& operator=(const unique_ptr&) = delete;

		explicit operator bool() const noexcept
		{
			return m_root_ptr != nullptr;
		}

		typename std::add_lvalue_reference_t<value_type> operator*() const noexcept(noexcept(*std::declval<pointer>()))
		{
			return *m_root_ptr;
		}

		pointer operator->() const noexcept
		{
			return m_root_ptr;
		}

		pointer get() const noexcept
		{
			return m_root_ptr;
		}

		value_type& operator[](std::size_t index)
		{
			return m_root_ptr[index];
		}
	};
}

#endif
