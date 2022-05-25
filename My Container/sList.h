#pragma once

#include <string>

template<class Data>
class sNode {
	using Node = sNode;
	using pNode = Node*;

	Data data;

public:
	pNode next;

public:
	sNode() : data{}, next{} {}
	sNode(Data d) : data{d}, next{} {}

public:
	const Data& getData() const { return data; }
};

template<class Data>
class sList {
	using Node = sNode<Data>;
	using pNode = Node*;

	pNode head;
	pNode tail;
	size_t size;

public:
	sList() : head{}, tail{}, size{} {}
	~sList() { Destroy(); }

	bool Load( std::string fileName, const char mode = 'r' );

	// Insertion
	void Insert( int index, Data newData );
	void push_back( Data newData );
	void push_front( Data newData );

	// Deletion
	bool Delete( Data deletion );
	template<class BiPred> bool Delete( Data deletion, BiPred pred );


	void Destroy();
};

// ============================================================================

template<class Data>
inline bool sList<Data>::Load( std::string fileName, const char mode )
{
	std::ifstream is{ fileName };

	if ( !is )
		return false;

	if ( 'r' == mode )
		Destroy();
	else if ( 'a' == mode );
	else
		return false;

	pNode cur{ head };
}

template<class Data>
inline void sList<Data>::Insert( int index, Data newData )
{
	if ( !index ) {
		push_front( newData );
		return;
	}
	else if ( index == size ) {
		push_back( newData );
		return;
	}
	else if ( index < 0 )
		abs( index );

	pNode cur{ head };

	for ( int i{ 1 }; i < index; ++i )
		cur = cur->next;

	pNode next = cur->next;
	cur->next = new Node{ newData };
	cur->next = next;

	++size;
}

template<class Data>
inline void sList<Data>::push_back( Data newData )
{
	if ( !head ) {
		head = new Node{ newData };
		tail = head;
	}
	else
		tail->next = new Node{ newData };

	++size;
}

template<class Data>
inline void sList<Data>::push_front( Data newData )
{
	if ( !head ) {
		head = new Node{ newData };
		tail = head;
	}
	else {
		pNode newNode = new Node{ newData };
		newNode->next = head;
		head = newNode;
	}

	++size;
}

template<class Data>
inline bool sList<Data>::Delete( Data deletion )
{
	pNode cur{ head };
	pNode prev{};

	while ( cur ) {
		if ( cur->data == deletion ) {
			if ( cur == head ) {
				head = head->next;
				delete cur;
			}
			else if ( cur == tail ) {
				tail = prev;
				delete cur;
			}
			else {
				prev = cur->next;
				delete cur;
			}
			--size;
			return true;
		}
		prev = cur;
		cur = cur->next;
	}
	return false;
}

template<class Data>
template<class BiPred>
inline bool sList<Data>::Delete( Data deletion, BiPred pred )
{
	pNode cur{ head };
	pNode prev{};

	while ( cur ) {
		if ( !pred( cur->data, deletion ) && !pred(deletion, cur->data) ) {
			if ( cur == head ) {
				head = head->next;
				delete cur;
			}
			else if ( cur == tail ) {
				tail = prev;
				delete cur;
			}
			else {
				prev = cur->next;
				delete cur;
			}
			--size;
			return true;
		}
		prev = cur;
		cur = cur->next;
	}
	return false;
}

template<class Data>
inline void sList<Data>::Destroy()
{
	pNode next{};
	while ( head ) {
		next = head->next;
		delete head;
		head = next;
	}

	head = tail = nullptr;
}
