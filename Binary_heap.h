#pragma once
#include <stdexcept>


using std::logic_error;
using std::out_of_range;

template <class Key>
struct Node
{
	Key value; //значение в вершине
	int* ptr; //указатель на вершину, нужен для erase и change
};

template <class Key>
class binary_heap
{
public:
	binary_heap(); 
	bool is_empty() const;
	Key extract_min();
	Key get_min() const;
	int* insert(Key key); // добавляем элемент со значеним key и возвращаем указатель на него
	void erase(int *ptr);
	void change(int *ptr, Key key);
	template <typename iterator>
	binary_heap(iterator begin, iterator end); //создаем кучу, пробегаясь от итератора на начало до итератора на конец
	void optimize(int insertCount, int extractCount);

private:
	int K = 2;
	void siftUp(int i);
	void siftDown(int i);
	Vector <Node<Key>> T;
	void swap(int x, int y);
};

template <class Key>
binary_heap<Key>::binary_heap()
{

}

template <class Key>
void binary_heap<Key>::swap(int x, int y)
{
	Key tmp;
	tmp = T[x].value;
	T[x].value = T[y].value;
	T[y].value = tmp;
	int* ptmp = T[x].ptr;
	T[x].ptr = T[y].ptr;
	T[y].ptr = ptmp;
	if (T[x].ptr != nullptr) *(T[x].ptr) = x;
	if (T[y].ptr != nullptr) *(T[y].ptr) = y;
}

template <class Key>
void binary_heap<Key>::siftUp(int i)
{
	while (T[i].value < T[(i - 1) / K].value)
	{
		swap(i, (i - 1) / K);
		i = (i - 1) / K;
	}
}

template <class Key>
void binary_heap<Key>::siftDown(int i)
{
	while (K * i + 1 < T.size())
	{
		int j = K * i + 1;
		for (int l = K * i + 2; l <= (K * (i + 1)); l++)
		{
			if (l < T.size() && T[l].value < T[j].value) j = l;
		}
		if (T[i].value <= T[j].value) break;
		swap(i, j);
		i = j;
	}
}

template <class Key>
template <typename iterator>
binary_heap<Key>::binary_heap(iterator begin, iterator end)
{
	for (; begin != end; ++begin)
	{
		Node<Key> x;
		x.value = *begin;
		x.ptr = nullptr;
		T.push_back(x);
	}
	for (int i = T.size() / K ; i >= 0; i--)
	{
		siftDown(i);
	}
}

template <class Key>
int* binary_heap<Key>::insert(Key key)
{
	Node<Key> x;
	x.value = key;
	int *new_ptr = new int;
	*new_ptr = T.size();
	x.ptr = new_ptr;
	T.push_back(x);
	siftUp(T.size() - 1);
	return new_ptr;
}


template <class Key>
Key binary_heap<Key>::get_min() const
{
	if (is_empty())
		throw logic_error("Heap is empty!");
	return (T[0].value);
}

template <class Key>
Key binary_heap<Key>::extract_min()
{
	T[0].ptr = nullptr;
	if (is_empty())
		throw logic_error("Heap is empty!");
	Key Min = T[0].value;
	swap(0, T.size() - 1);
	T.pop_back();
	siftDown(0);
	return Min;
}

template <class Key>
void binary_heap<Key>::change(int *ptr, Key new_value)
{
	if (ptr == nullptr)
		throw logic_error("Element doesn;t exist!");
	T[*ptr].value = new_value;
	siftUp(*ptr);
	siftDown(*ptr);
}

template <class Key>
void binary_heap<Key>::erase(int *ptr)
{
	if (ptr == nullptr)
		throw logic_error("Element doesn't exist!");
	change(ptr, T[0].value - 1);
	extract_min();
}

template <class Key>
void binary_heap<Key>::optimize(int insertCount, int extractCount)
{
	if (!is_empty())
		throw logic_error("Heap is not empty!");
	if (extractCount == 0)
	{
		extractCount = 1;
	}
	if (insertCount / extractCount > 2)
	{
		K = insertCount / extractCount;
	}
	else K = 2;
}


template <class Key>
bool binary_heap<Key>::is_empty() const
{
	return (T.size() == 0);
}
