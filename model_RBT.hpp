#include<iostream>
using namespace std;

enum Color { RED, BLACK };

template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& data = T(), Color color = RED)
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _color(color)
	{}


	RBTreeNode<T>* _pLeft;
	RBTreeNode<T>* _pRight;
	RBTreeNode<T>* _pParent;
	T _data;

	Color _color;
};

template<class T>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;

	RBTreeIterator(Node* pNode)
		:_pNode(pNode)
	{}

	T& operator*()
	{
		return _pNode->_data;
	}
	T* operator->()
	{
		return &(operator*());
	}
	Self& operator++()
	{
		Increament();
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Increament();
		return temp;
	}

	Self& operator--()
	{
		DeIncreament();
		return *this;
	}

	Self operator--(int)
	{
		Self temp(*this);
		DeIncreament();
		return temp;
	}

	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}

	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}

private:
	void Increament()
	{
		if (_pNode->_pRight)
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
				_pNode = _pNode->_pLeft;
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}

			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}

	// --
	void DeIncreament()
	{
		// Handle the position of the iterator at the end
		if (_pNode->_pParent->_pParent == _pNode && _pNode->_color == RED)
			_pNode = _pNode->_pRight;
		else if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
				_pNode = _pNode->_pRight;
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (pParent->_pLeft == _pNode)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}

			_pNode = pParent;
		}
	}
	Node* _pNode;
};

 // T: It may be a key-value pair <key, value>
 // may be a key
 // Regardless of the <key, value> || key stored in the node, the comparison is done according to the key
 // KeyOfValue: extract the key from data
template<class T, class KeyOfValue>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T> iterator;
	RBTree()
		:_size(0)
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	pair<iterator, bool> Insert(const T& data)
	{
		 // Insert new nodes according to the nature of the binary search tree
		Node*& pRoot = GetRoot();
		Node* pNewNode = nullptr;
		if (nullptr == pRoot)
		{
			pNewNode = pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
		}
		else
		{
			 // Find the position of the inserted node in the binary tree
			 // Save its parent node
			Node* cur = pRoot;
			Node* pParent = nullptr;
			while (cur)
			{
				pParent = cur;
				if (KeyOfValue()(data) < KeyOfValue()(cur->_data))
					cur = cur->_pLeft;
				else if (KeyOfValue()(data) > KeyOfValue()(cur->_data))
					cur = cur->_pRight;
				else
					return make_pair(iterator(cur), false);

			}

			 // Insert new node
			pNewNode = cur = new Node(data);
			if ((KeyOfValue()(data) < KeyOfValue()(pParent->_data)))
				pParent->_pLeft = cur;
			else
				pParent->_pRight = cur;

			cur->_pParent = pParent;


			while (pParent != _pHead && pParent->_color == RED)
			{
				Node* grandFather = pParent->_pParent;
				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;
					if (uncle&&uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						cur = grandFather;
						pParent = cur->_pParent;
					}
					else
					{
						if (cur == pParent->_pRight)
						{
							RotateL(pParent);
							swap(cur, pParent);
						}

						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateR(grandFather);
					}
				}
				else
				{
					Node* uncle = grandFather->_pLeft;
					if (uncle&&uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						cur = grandFather;
						pParent = cur->_pParent;
					}
					else
					{
						if (cur == pParent->_pLeft)
						{
							RotateR(pParent);
							swap(cur, pParent);
						}

						grandFather->_color = RED;
						pParent->_color = BLACK;
						RotateL(grandFather);
					}
				}
			}
		}
		++_size;
		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return make_pair(iterator(pNewNode), true);
	}

	iterator Begin()
	{
		return iterator(LeftMost());
	}
	iterator End()
	{
		return iterator(_pHead);
	}

	bool Empty()const
	{
		return _pHead->_pLeft == _pHead;
	}

	size_t Size()const
	{
		return _size;
	}

	void Clear()
	{
		_Destroy(GetRoot());
	}

	iterator Find(const T& data)
	{
		Node* pCur = GetRoot();
		while (pCur)
		{
			if ((KeyOfValue()(data) == KeyOfValue()(pCur->_data)))
				return iterator(pCur);
			else if ((KeyOfValue()(data) < KeyOfValue()(pCur->_data)))
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}

		return End();
	}

	Node*& GetRoot()
	{
		return _pHead->_pParent;
	}
	void InOrder()
	{
		_InOrder(GetRoot());
	}
	Node* LeftMost()
	{
		Node* root = GetRoot();
		if (nullptr == root)
			return _pHead;
		Node* cur = root;
		while (cur->_pLeft)
			cur = cur->_pLeft;
		return cur;
	}

	Node* RightMost()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;

		Node* cur = pRoot;
		while (cur->_pRight)
			cur = cur->_pRight;

		return cur;
	}

	bool IsValidRBTRee()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;

		if (pRoot->_color != BLACK)
		{
			 cout << "Violation of nature one: the root node is black" << endl;
			return false;
		}

		size_t blackCount = 0;
		Node* cur = pRoot;
		while (cur)
		{
			if (cur->_color == BLACK)
				blackCount++;

			cur = cur->_pLeft;
		}
		size_t pathBalck = 0;
		return _IsValidRBTRee(pRoot, blackCount, pathBalck);
	}
private:
	void _Destroy(Node*& pRoot)
	{
		if (pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}

	bool _IsValidRBTRee(Node* pRoot, size_t blackCount, size_t pathBlack)
	{
		if (nullptr == pRoot)
			return true;

		if (pRoot->_color == BLACK)
			pathBlack++;

		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead &&
			RED == pParent->_color && RED == pRoot->_color)
		{
			 cout << "violation of nature 3: there can be no red nodes connected together" << endl;
			return false;
		}

		 // leaf node
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (pathBlack != blackCount)
			{
				 cout << "violation of nature 4: the number of black nodes in each path are the same" << endl;
				return false;
			}
		}

		return _IsValidRBTRee(pRoot->_pLeft, blackCount, pathBlack) &&
			_IsValidRBTRee(pRoot->_pRight, blackCount, pathBlack);
	}
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	void RotateL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* ppParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = ppParent;

		if (ppParent == _pHead)
			_pHead->_pParent = pSubR;
		else
		{
			if (pParent == ppParent->_pLeft)
				ppParent->_pLeft = pSubR;
			else
				ppParent->_pRight = pSubR;
		}
	}

	void RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;

		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}
private:
	Node* _pHead;
	size_t _size;
};
