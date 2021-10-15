#ifndef _LIST_H
#define _LIST_H

template <class T>
struct ListNode {
	ListNode* prev;
	T data;
	ListNode* next;

	ListNode() {
		prev = nullptr;
		next = nullptr;
	}

	ListNode(T _data) {
		prev = nullptr;
		data = _data;
		next = nullptr;
	}

	ListNode(ListNode* _prev, T _data, ListNode* _next) {
		prev = _prev;
		if (prev != nullptr) prev->next = this;
		data = _data;
		next = _next;
		if (next != nullptr) next->prev = this;
	}
};

template <class T>
struct List {
	ListNode<T>* first;

	List() {
		first = nullptr;
	}

	List(T _data) {
		add(_data);
	}

	unsigned int size() {
		unsigned int count = 0;
		ListNode<T>* current = first;
		while(true) {
			if (current == nullptr) return count;
			current = current->next;
			count++;
		}
	}

	void append(T _data) {
		if (first == nullptr) {
			first = new ListNode<T>(_data);
		} else {
			new ListNode<T>(get(size() - 1), _data, nullptr);
		}
	}

	void add(T _data) {
		first = new ListNode<T>(nullptr, _data, first);
	}

	void insert(T data, unsigned int _pos) {
		if (_pos == 0) add(data);
		unsigned int lsize = size();
		if (_pos >= lsize) {
			append(data);
		} else {
			ListNode<T>* cn = get(_pos-1);
			new ListNode<T>(cn, data, cn->next);
		}
	}

	T* get(const unsigned int index) {
		ListNode<T>* current = first;
		for (unsigned int i = 0; i < index; i++) {
			if (current == nullptr) return nullptr;
			current = current->next;
		}
		return &(current->data);
	}
};

#endif