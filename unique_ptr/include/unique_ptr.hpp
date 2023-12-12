#pragma once

#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <type_traits>
#include <iostream>
#include <functional>

namespace custom
{
	template <typename T>
	class unique_ptr
	{
	private:
		typedef T* pointer;
		typedef T value_type;

    private:
        typedef std::function<void(pointer)> deleter_t;

    private:
		pointer m_root_ptr;
        deleter_t m_deleter;

	public:
		explicit unique_ptr() noexcept :
			m_root_ptr(nullptr),
            m_deleter([](pointer ptr) -> void { delete ptr; })
		{ }
		
		explicit unique_ptr(pointer ptr,
                            deleter_t&& deleter = [](pointer ptr) -> void { delete ptr; }) noexcept :
            m_root_ptr(ptr),
            m_deleter(std::move(deleter))
		{ }
		
		explicit unique_ptr(const unique_ptr&) noexcept = delete;
		
		explicit unique_ptr(unique_ptr&& other) noexcept
		{
			m_root_ptr = other.m_root_ptr;
            m_deleter = std::move(other.m_deleter);

			other.m_root_ptr = nullptr;
		}

		~unique_ptr() noexcept
		{
            if (m_deleter != nullptr)
            {
                m_deleter(m_root_ptr);
            }
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
        typedef T& reference;
		typedef T value_type;

    private:
        typedef std::function<void(pointer)> deleter_t;

	private:
		pointer m_root_ptr;
        deleter_t m_deleter;

	public:
		explicit unique_ptr() noexcept :
			m_root_ptr(nullptr),
            m_deleter([](pointer ptr) -> void { delete[] ptr; })
		{ }

		explicit unique_ptr(pointer ptr,
                            deleter_t&& deleter = [](pointer ptr) -> void { delete[] ptr; }) noexcept :
			m_root_ptr(ptr),
            m_deleter(std::move(deleter))
		{ }

		explicit unique_ptr(const unique_ptr&) noexcept = delete;

		explicit unique_ptr(unique_ptr&& other) noexcept
		{
			m_root_ptr = other.m_root_ptr;
            m_deleter = std::move(other.m_deleter);

			other.m_root_ptr = nullptr;
		}

		~unique_ptr() noexcept
		{
            if (m_deleter != nullptr)
            {
                m_deleter(m_root_ptr);
            }
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

		reference operator[](std::ptrdiff_t idx)
		{
			return m_root_ptr[idx];
		}
	};
}

#endif
