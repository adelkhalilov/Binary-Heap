#pragma once

#include<stdexcept>

template <class Key>
class Vector
{
public:
	Vector();
	void increase();
	void decrease();
	void push_back(Key key);
	void pop_back();
	bool is_empty() const;
	int size() const;
	Key& operator [](int i);
	const Key& operator [](int i) const;
	Key* operator &(int i);

private:
	Key* T = nullptr;
	int max_sz;
	int curr_sz;
};


template<class Key>
Vector<Key>::Vector()
{
	max_sz = 2;
	Key* Q = new Key[2];
	T = Q;
	curr_sz = 0;
}

template <class Key>
void Vector<Key>::increase() // увеличиваем памяти в ~два раза и перезаписываем наш массив в новый
{
	max_sz = max_sz * 2 + 1;
	Key* Q = new Key[max_sz];
	for (int i = 0; i < curr_sz; i++)
	{
		Q[i] = T[i];
	}
	T = Q;
}

template<class Key>
void Vector<Key>::decrease()
{
	max_sz = max_sz / 2;
	Key* Q = new Key[max_sz];
	for (int i = 0; i < curr_sz; i++)
	{
		Q[i] = T[i];
	}
	T = Q;
}

template <class Key>
void Vector<Key>::push_back(Key key)
{
	if (curr_sz + 1 >= max_sz) // если размер вектора превысил нашу выделенную память, увеличиваем ее
	{
		increase();
	}
	T[curr_sz] = key;
	curr_sz++;
}

template<class Key>
void Vector<Key>::pop_back()
{
	curr_sz--; // считаем, что этого элемента не существует, уменьшая размер массива на 1
	if (curr_sz * 4 < max_sz && curr_sz > 10) // если слишком много лишней памяти, уменьшим ее в 2 раза
		decrease();
}

template <class Key>
int Vector<Key>::size() const
{
	return curr_sz;
}

template <class Key>
bool Vector<Key>::is_empty() const
{
	return curr_sz == 0;
}


template <class Key>
const Key& Vector<Key>::operator [](int i) const
{
	return T[i];
}

template <class Key>
Key& Vector<Key>::operator [](int i)
{
	return T[i];
}

template <class Key>
Key* Vector<Key>::operator &(int i)
{
	return &T[i];
}
