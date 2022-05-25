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
	template<class UnPred> bool Delete( Data deletion, UnPred pred);

	void Destroy();
};