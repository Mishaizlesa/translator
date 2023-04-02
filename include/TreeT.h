#ifndef RBT_H
#define RBT_H

#include <utility>
#include <assert.h>

#define RED false
#define BLACK true

template<class TKey, class TValue>
class TreeT
{
private:
	struct Node
	{
		Node* parent;
		Node* l;
		Node* r;
		bool color;
		std::pair<TKey, TValue> p;

		static Node* P(Node* x) { return x->parent; }
		static Node* G(Node* x) { return x->parent->parent; }
		static Node* U(Node* x) { return S(x->parent); }
		static Node* S(Node* x);
		static Node* SL(Node* x) { return S(x)->l; }
		static Node* SR(Node* x) { return S(x)->r; }
		static bool isNIL(Node* x) { return !x->l && !x->r; }


		Node() { l = r = parent = nullptr; color = BLACK; p = { TKey(), TValue() }; }
		Node(Node* _parent, std::pair<TKey, TValue> _pair) { parent = _parent; p = _pair; l = r = nullptr; }
	};

	Node* root = nullptr;

public:
	class iterator
	{
	private:
		Node* node;
		iterator() = default;

	public:
		iterator(Node* _node) { node = _node; }
		bool operator ==(const iterator& it) { return node == it.node; }
		bool operator !=(const iterator& it) { return node != it.node; }
		std::pair<const TKey, TValue&> operator*() { return std::pair<const TKey, TValue&>(node->p.first, node->p.second); }
		iterator& operator ++();
	};

private:

	Node* find_min(Node* node);
	void delete_min(Node* node);
	Node* find_max(Node* node);
	void delete_max(Node* node);
	Node* find_node(const TKey& key);
	void erase_node(Node* node);
	void insert_node(Node* node, const std::pair<TKey, TValue>& el);

	void delete_node(Node* node);
	Node* copy_node(Node* node, Node* parent);
	void swap_node(Node* old_node, Node* new_node);
	void replace_child(Node* old_child, Node* new_child);
	void rotate_left(Node* node);
	void rotate_right(Node* node);
	void balance_insert(Node* x);
	void balance_delete(Node* x);



public:
	TreeT() { root = new Node(nullptr, std::make_pair(TKey(), TValue())); }
	TreeT(const TreeT& other) { root = copy_node(other.root, nullptr); }
	iterator begin() { return iterator(find_min(root)); } // min_el
	iterator end() { return iterator(nullptr); }
	iterator insert(const std::pair<TKey, TValue>& el);
	iterator erase(const TKey& key); // элемент, который встал на место удаленного 
	iterator find(const TKey& key) { return iterator(find_node(key)); }
	void clear() { delete_node(root); root = new Node(nullptr, std::make_pair(TKey(), TValue()));}
	~TreeT() { clear(); }
	TValue& operator[] (const TKey& key);

	int height(TKey k);

};


template<typename TKey, typename TValue>
inline typename TreeT<TKey, TValue>::iterator& TreeT<TKey, TValue>::iterator::operator++()
{
	if (!node) throw std::logic_error("out of range");

	Node* cur = node;

	if (!Node::isNIL(cur->r)) // cur->r.key > cur.key
	{
		cur = cur->r;
		while (cur->l && !Node::isNIL(cur->l))
			cur = cur->l;
	}
	else
	{
		Node* before;
		do
		{
			before = cur;
			cur = cur->parent;
		} while (cur && before == cur->r);
	}

	node = cur;

	return *this;
}

template<class TKey, class TValue>
inline typename TreeT<TKey, TValue>::Node* TreeT<TKey, TValue>::find_min(Node* node)
{
	if (!node) throw std::logic_error("nullptr");
	while (node->l && !Node::isNIL(node->l))
		node = node->l;
	return node;
}

template<class TKey, class TValue>
inline typename TreeT<TKey, TValue>::Node* TreeT<TKey, TValue>::find_max(Node* node)
{
	if (!node) throw std::logic_error("nullptr");
	while (node->r && !Node::isNIL(node->r))
		node = node->r;
	return node;
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::delete_min(Node* y)
{
	Node* x = y->r;
	replace_child(y, x);
	if (x->color == RED) { x->color = BLACK; }
	else if (x->color == BLACK && y->color == BLACK) { balance_delete(x); }
	delete y->l; delete y;
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::delete_max(Node* y)
{
	Node* x = y->l;
	replace_child(y, x);
	if (x->color == RED) { x->color = BLACK; }
	else if (x->color == BLACK && y->color == BLACK) { balance_delete(x); }
	delete y->r; delete y;
}

template<class TKey, class TValue>
inline typename TreeT<TKey, TValue>::Node* TreeT<TKey, TValue>::find_node(const TKey& key)
{
	Node* cur = root;
	while (cur && !Node::isNIL(cur) && cur->p.first != key)
	{
		TKey cur_key = cur->p.first;
		if (cur_key > key)
			cur = cur->l;
		else
			cur = cur->r;
	}

	return cur;
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::erase_node(Node* z)
{


	if (Node::isNIL(z->l) && Node::isNIL(z->r))
	{
		delete_min(z);
		return;
	}
	else if(Node::isNIL(z->r))
	{
		Node* y = find_max(z->l);
		swap_node(z, y);
		delete_max(z);
		return;
	}
	else
	{
		Node* y = find_min(z->r);
		swap_node(z, y);
		delete_min(z);
		return;
	}
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::insert_node(Node* node, const std::pair<TKey, TValue>& el)
{
	if (Node::isNIL(node))
	{
		node->p = el;
		node->color = RED;
		node->l = new Node(node, std::make_pair(TKey(), TValue()));
		node->r = new Node(node, std::make_pair(TKey(), TValue()));

		balance_insert(node);
	}
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::delete_node(Node* node)
{
	if (!node) return;
	delete_node(node->l);
	delete_node(node->r);
	delete node;
}

template<class TKey, class TValue>
inline typename TreeT<TKey, TValue>::Node* TreeT<TKey, TValue>::copy_node(Node* node, Node* parent)
{
	if (!node) return node;
	Node* new_node = new Node(parent, node->p);
	new_node->l = copy_node(node->l, new_node);
	new_node->r = copy_node(node->r, new_node);
	return new_node;
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::swap_node(Node* old_node, Node* new_node)
{
	if (!old_node) throw std::logic_error("nullptr");

	Node* new_root = root;

	if (old_node != root)
	{
		if (old_node->parent->l == old_node)
			old_node->parent->l = new_node;
		else
			old_node->parent->r = new_node;
	}
	else
	{
		new_root = new_node;
	}

	if (new_node != root)
	{
		if (new_node->parent->l == new_node)
			new_node->parent->l = old_node;
		else
			new_node->parent->r = old_node;
	}
	else
	{
		new_root = old_node;
	}
	
	std::swap(old_node->parent, new_node->parent);
	root = new_root;


	std::swap(new_node->l, old_node->l);
	std::swap(new_node->r, old_node->r);
	std::swap(new_node->color, old_node->color);

	if (new_node->l) new_node->l->parent = new_node;
	if (new_node->r) new_node->r->parent = new_node;
	if (old_node->l) old_node->l->parent = old_node;
	if (old_node->r) old_node->r->parent = old_node;


}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::replace_child(Node* old_child, Node* new_child)
{
	if (new_child)
		new_child->parent = old_child->parent;

	if (old_child != root)
	{
		if (old_child->parent->l == old_child)
			old_child->parent->l = new_child;
		else
			old_child->parent->r = new_child;
	}
	else
	{
		root = new_child;
		root->parent = nullptr;
	}
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::rotate_left(Node* x)
{
	Node* y = x->r;

	x->r = y->l;
	if (y->l)
		y->l->parent = x;

	if (x != root)
		replace_child(x, y);
	else
	{
		root = y;
		root->parent = nullptr;
	}

	y->l = x;
	x->parent = y;
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::rotate_right(Node* x)
{
	Node* y = x->l;

	x->l = y->r;
	if (y->r)
		y->r->parent = x;

	if (x != root)
		replace_child(x, y);
	else
	{
		root = y;
		root->parent = nullptr;
	}

	y->r = x;
	x->parent = y;
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::balance_insert(Node* x)
{
	if (x == root)
	{
		x->color = BLACK;
		return;
	}
	if (Node::P(x)->color == BLACK) return;


	if (Node::U(x)->color == RED)
	{
		Node::P(x)->color = BLACK;
		Node::U(x)->color = BLACK;
		Node::G(x)->color = RED;
		balance_insert(Node::G(x));
		return;
	}

	Node* grand_x = Node::G(x);
	grand_x->color = !grand_x->color;
	Node::P(x)->color = RED;
	if (Node::P(x) == grand_x->l)
	{
		if (x == Node::P(x)->r)
			rotate_left(grand_x->l);
		rotate_right(grand_x);
	}
	else
	{
		if (x == Node::P(x)->l)
			rotate_right(grand_x->r);
		rotate_left(grand_x);
	}
}

template<class TKey, class TValue>
inline void TreeT<TKey, TValue>::balance_delete(Node* x)
{
	if (x == root) { return; }

	if (Node::S(x)->color == RED)
	{
		Node::P(x)->color = RED;
		Node::S(x)->color = BLACK;
		if (x == Node::P(x)->l)
			rotate_left(Node::P(x));
		else
			rotate_right(Node::P(x));
	}

	if (Node::S(x)->color == BLACK && Node::P(x)->color == BLACK &&
		Node::SL(x)->color == BLACK && Node::SR(x)->color == BLACK)
	{
		Node::S(x)->color = RED;
		balance_delete(Node::P(x));
		return;
	}

	if (Node::S(x)->color == BLACK && Node::P(x)->color == RED &&
		Node::SL(x)->color == BLACK && Node::SR(x)->color == BLACK)
	{
		Node::S(x)->color = RED;
		Node::P(x)->color = BLACK;
		return;
	}

	if (x == Node::P(x)->l) {
		if (Node::SL(x)->color == RED && Node::SR(x)->color == BLACK)
		{
			Node::S(x)->color = RED;
			Node::SL(x)->color == BLACK;
			rotate_right(Node::S(x));
		}
		Node::S(x)->color = Node::P(x)->color;
		Node::P(x)->color = BLACK;
		Node::SR(x)->color = BLACK;
		rotate_left(Node::P(x));
	}
	else if (x == Node::P(x)->r)
	{
		if (Node::SR(x)->color == RED && Node::SL(x)->color == BLACK)
		{
			Node::S(x)->color = RED;
			Node::SR(x)->color == BLACK;
			rotate_left(Node::S(x));
		}
		Node::S(x)->color = Node::P(x)->color;
		Node::P(x)->color = BLACK;
		Node::SL(x)->color = BLACK;
		rotate_right(Node::P(x));
	}


}

template<class TKey, class TValue>
inline int TreeT<TKey, TValue>::height(TKey key)
{
	int res = 0;
	Node* cur = root;
	while (cur && !Node::isNIL(cur) && cur->p.first != key)
	{
		res++;
		TKey cur_key = cur->p.first;
		if (cur_key > key)
			cur = cur->l;
		else
			cur = cur->r;
	}
	if (cur->p.first != key) res = -1;
	return res;
}

template<typename TKey, typename TValue>
inline typename TreeT<TKey, TValue>::iterator TreeT<TKey, TValue>::insert(const std::pair<TKey, TValue>& el)
{
	Node* cur = find_node(el.first);
	insert_node(cur, el);
	return iterator(cur);
}

template<typename TKey, typename TValue>
inline typename TreeT<TKey, TValue>::iterator TreeT<TKey, TValue>::erase(const TKey& key)
{
	Node* del_node = find_node(key);

	if (Node::isNIL(del_node))
		return end();

	auto it = iterator(del_node);
	++it;
	erase_node(del_node);
	return it;
}

template<class TKey, class TValue>
inline TValue& TreeT<TKey, TValue>::operator[](const TKey& key)
{
	Node* node = find_node(key);
	insert_node(node, std::make_pair(key, TValue()));
	return node->p.second;
}

template<class TKey, class TValue>
inline typename TreeT<TKey, TValue>::Node* TreeT<TKey, TValue>::Node::S(Node* x)
{
	if (x->parent->l == x)
		return x->parent->r;
	else
		return x->parent->l;
}

#endif
