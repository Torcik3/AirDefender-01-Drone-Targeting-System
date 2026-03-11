#pragma once
#include "Allocator.h"
template<typename T>
class Vector {
public:
    Vector()
    {
        ReAllec(2);
    }

    Vector(const Vector& other) {
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        m_Data = Allocator<T>::Allocate(m_Capacity);
        for (unsigned long long i = 0; i < m_Size; i++) {
            Allocator<T>::Constructor(&m_Data[i], other.m_Data[i]);
        }
    }

    Vector(Vector&& other) noexcept {
        m_Data = other.m_Data;
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;

        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_Capacity = 0;
    }
    ~Vector() {
        for (unsigned long long i = 0; i < m_Size; i++) {
            Allocator<T>::Destroy(&m_Data[i]);
        }

        if (m_Data != nullptr) {
            Allocator<T>::Deallocate(m_Data, m_Capacity);
        }
    }
    void PushBack(const T& value)
    {
        if (m_Size>=m_Capacity)
            ReAllec(m_Capacity + m_Capacity/2);

        m_Data[m_Size] = value;
        m_Size++;
    }

    void PushBack(T&& value)
    {
        if (m_Size>=m_Capacity)
            ReAllec(m_Capacity + m_Capacity/2);

        Allocator<T>::Constructor(&m_Data[m_Size], std::move(value));
        m_Size++;
    }

    template<typename... Args>
    T& EmplaceBack(Args&&... args) {
        if (m_Size>=m_Capacity)
            ReAllec(m_Capacity + m_Capacity/2);

           Allocator<T>::Constructor(&m_Data[m_Size], std::forward<Args>(args)...);

        return m_Data[m_Size++];
    }

   void PopBack() {
        if (m_Size > 0) {
            m_Size--;
            Allocator<T>::Destroy(&m_Data[m_Size]);
        }

    }

const T& operator[](unsigned long long index) const
    {
    if (index >= m_Size)
        {
        //  assert
        }
    return m_Data[index];
    }

    T& operator[](unsigned long long index)
    {
        return m_Data[index];
    }

   unsigned long long Size() const { return m_Size; }
private:
    void ReAllec(unsigned long long newCapacity)
    {
        T* newBlock = Allocator<T>::Allocate(newCapacity);

        if (newCapacity<m_Size)
            m_Size = newCapacity;

        for(unsigned long long i = 0; i < m_Size; i++)
        {
            Allocator<T>::Constructor(&newBlock[i], std::move(m_Data[i]));
            Allocator<T>::Destroy(&m_Data[i]);
        }

        Allocator<T>::Deallocate(m_Data,m_Capacity);

        m_Data=newBlock;
        m_Capacity=newCapacity;
    }
private:
    T* m_Data = nullptr;
    unsigned long long m_Size = 0;
    unsigned long long m_Capacity = 0;
};