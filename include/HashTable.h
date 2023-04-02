#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include "list.hpp"


template<class TValue, class TKey = std::string>
class HashTable
{
private:

	static const int P = 1e9 + 7;
	static const char ALPH_SZ = 251;
	int A, B;

	using list = TDynamicList < std::pair < TKey, TValue > >;
	std::vector<list> v;
	size_t sz = 0;

	size_t hash_str(const std::string& str);
	size_t get_index(size_t hash) { return (((hash * A) % P + B) % P) % (v.size()); }


	void repacking(size_t new_size);
		
public:

	class iterator
	{
		using list_iterator = typename TDynamicList<std::pair<TKey, TValue>>::iterator;
	private:
		size_t index_in_vector;
		list_iterator iter;
		HashTable* ht = nullptr;

	public:
		iterator(list_iterator _iter, size_t _i, HashTable* _ht) { iter = _iter; index_in_vector = _i; ht = _ht; }
		bool operator ==(const iterator& it) { return iter == it.iter && index_in_vector == it.index_in_vector; }
		bool operator !=(const iterator& it) { return !(operator==(it)); }
		std::pair<const TKey, TValue&> operator*() { auto& tmp = *iter;  return std::pair<const TKey, TValue&>(tmp.first, tmp.second); }
		iterator& operator ++();
	};

	HashTable(int seed = ALPH_SZ, bool used_random_hash = true);
	HashTable(const HashTable& other) = default;
	iterator begin();
	iterator end() { return iterator(v[v.size() - 1].end(), v.size() - 1, this); }
	iterator insert(const std::pair<TKey, TValue>& el);
	iterator erase(const TKey& key); // элемент, который встал на место удаленного 
	iterator find(const TKey& key);
	void clear() { v.clear(); }
	~HashTable() = default;
	TValue& operator[] (const TKey& key) { return (*insert(std::make_pair(key, TValue()))).second; }

	size_t size() { return sz; }
};

template<class TValue, class TKey>
inline typename HashTable<TValue, TKey>::iterator& HashTable<TValue, TKey>::iterator::operator++()
{
	if (iter != ht->v[index_in_vector].end())
		++iter;

	if(iter == ht->v[index_in_vector].end())
	{
		++index_in_vector;
		while (index_in_vector + 1 < ht->v.size() && ht->v[index_in_vector].size() == 0)
			++index_in_vector;

		iter = ht->v[index_in_vector].begin();
	}

	return *this;
}

template<class TValue, class TKey>
inline typename HashTable<TValue, TKey>::iterator HashTable<TValue, TKey>::begin()
{
	int ind = 0;

	while (ind + 1 < v.size() && v[ind].size() == 0)
		++ind;

	return iterator(v[ind].begin(), ind, this);
}


template<class TValue, class TKey>
inline size_t HashTable<TValue, TKey>::hash_str(const std::string& str)
{
	size_t res = 0ll;
	size_t pow = 1;
	for (char c : str)
	{
		res = (res + (c * pow) % P) % P;
		pow = (pow * ALPH_SZ) % P;
	}
	return res;
}

template<class TValue, class TKey>
inline void HashTable<TValue, TKey>::repacking(size_t new_size)
{
	auto cop = v;
	v.clear();
	v.resize(new_size);
	for (auto& _list : cop) for(auto& x: _list)
		insert(x);
}


template<class TValue, class TKey>
inline HashTable<TValue, TKey>::HashTable(int seed, bool used_random_hash)
{
	v = std::vector<TDynamicList<std::pair<TKey, TValue>>>();
	if (!used_random_hash)
		srand(seed);

	A = (rand() % (P - 1)) + 1; // 0 < A < P
	B = rand();
}

template<class TValue, class TKey>
inline typename HashTable<TValue, TKey>::iterator HashTable<TValue, TKey>::insert(const std::pair<TKey, TValue>& el)
{
	++sz;
	if (v.size() * 2 < sz)
		repacking(v.size() * 2 + 1);

	size_t hash = hash_str(el.first);
	size_t index = get_index(hash);


	for (auto it = v[index].begin(); it != v[index].end(); ++it)
		if ((*it).first == el.first)
			return iterator(it, index, this);

	v[index].push_front(el);
	return iterator(v[index].begin(), index, this);
}

template<class TValue, class TKey>
inline typename HashTable<TValue, TKey>::iterator HashTable<TValue, TKey>::erase(const TKey& key)
{
	--sz;

	size_t hash = hash_str(key);
	size_t index = get_index(hash);
	auto prev_iter = v[index].end();
	auto it = v[index].begin();
	for (; it != v[index].end() && (*it).first != key; ++it)
	{
		prev_iter = it;
	}

	auto res = iterator(it, index, this);
	if (prev_iter != v[index].end())
	{
		v[index].erase_after(prev_iter);
	}
	else if ((*v[index].begin()).first == key)
	{
		v[index].pop_front();
	}

	++res;
	return res;
}


#endif
