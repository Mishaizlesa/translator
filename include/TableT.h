#pragma once
#include <vector>

template<typename TKey, typename TValue>
class TableT
{
private:
	std::vector<std::pair<TKey, TValue>> v;

public:
	void insert(const std::pair<TKey, TValue>& p);
	void erase(const TKey& key);
	typename std::vector<std::pair<TKey, TValue>>::iterator find(const TKey& key);
	size_t size() const { return v.size(); }
	TableT() = default;
	TValue& operator[](const TKey& key);
	TValue operator[] (const TKey& key) const;

};

template<typename TKey, typename TValue>
inline typename std::vector<std::pair<TKey, TValue>>::iterator TableT<TKey, TValue>::find (const TKey& key)
{
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		if (it->first == key)
			return it;
	}
	return v.end();
}

template<typename TKey, typename TValue>
inline TValue& TableT<TKey, TValue>::operator[](const TKey& key)
{
	auto it = find(key);
	if (it != v.end())
		return (it->second);

	v.push_back(std::make_pair(key, TValue()));
	return v.back().second;
}

template<typename TKey, typename TValue>
inline TValue TableT<TKey, TValue>::operator[](const TKey& key) const
{
	auto it = find(key);
	if (it != v.end())
		return (it->second);

	return TValue();
}

template<typename TKey, typename TValue>
inline void TableT<TKey, TValue>::insert(const std::pair<TKey, TValue>& p)
{
	auto it = find(p.first);
	if (it != v.end())
	{
		it->second = p.second;
		return;
	}
	v.push_back(p);
}

template<typename TKey, typename TValue>
inline void TableT<TKey, TValue>::erase(const TKey& key)
{
	if (v.size() == 0) return;
	auto it = find(key);

	if (it != v.end())
	{
		swap(it, --v.end());
		return;
	}

	v.pop_back();
}
