#include <iostream>
#include <time.h>
#include <Windows.h>
#include <iomanip>
#include <utility>
#include <string>
using namespace std;
template <class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T> *leftChild,   // ������
		*rightChild;  // ������
	binaryTreeNode() { leftChild = rightChild = NULL; }
	binaryTreeNode(const T& theElement) :element(theElement)
	{		
		leftChild = rightChild = nullptr;
	}
	binaryTreeNode(const T& theElement,
		binaryTreeNode *theLeftChild,
		binaryTreeNode *theRightChild)
		:element(theElement)
	{
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};
template<class K, class E>
class dBinarySearchTreeWithGE
{
public:
	void insert(const pair< K, E>& );
	pair<const K, E>* findGE(const K& theKey) const;
	void erase(const K& theKey);
private:
	binaryTreeNode<pair<const K, E> > *root=NULL;
	int treeSize = 0;
};
template<class K, class E>
pair<const K, E>* dBinarySearchTreeWithGE<K, E>::findGE(const K& theKey) const
{//����һ��Ԫ�ص�ָ�룬���Ԫ�صĹؼ����ǲ�С��thekey����С�ؼ���
 // ���������Ԫ�ز����ڣ�����NULL
	binaryTreeNode<pair<const K, E> > *currentNode = root;
	pair<const K, E> *bestElement = NULL; // Ŀǰ�ҵ���Ԫ�أ���ؼ����ǲ�С��thekey����С�ؼ���										  
	while (currentNode != NULL)
		if (currentNode->element.first >= theKey)// currentNode->element ��һ����ѡ����
		{
			bestElement = &currentNode->element;// ��, currentNode->element �Ǳ�bestElement���õĺ�ѡ��
			currentNode = currentNode->leftChild;// ��������Ψһ��С�Ĺؼ���
		}
		else// ����, currentNode->element.first ̫С
			currentNode = currentNode->rightChild;// ���������
	return bestElement;
}
template<class K, class E>
void dBinarySearchTreeWithGE<K, E>::insert( const pair< K, E>& thePair)
{// ��thePair���뵽����. �����ظ�ֵ.
 // �ҵ��ط�����
	binaryTreeNode<pair<const K, E> > *p = root,
		*pp = NULL;
	while (p != NULL)
	{// ��� p->element
		pp = p;
		if (thePair.first <= p->element.first)// ��p�Ƶ�һ������
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	binaryTreeNode<pair<const K, E> > *newNode// ΪthePair�ҵ�һ���ڵ������ӵ�pp
		= new binaryTreeNode<pair<const K, E> >(thePair);
	if (root != NULL) // �����ǿյ�
		if (thePair.first <= pp->element.first)
			pp->leftChild = newNode;
		else
			pp->rightChild = newNode;
	else
		root = newNode; // �������
	treeSize++;
}
template<class K, class E>
void dBinarySearchTreeWithGE<K, E>::erase(const K& theKey)
{// ɾ��ֵ����theKey��Ԫ��
 // ΪtheKey�ҵ�һ���ڵ�
	binaryTreeNode<pair<const K, E> > *p = root,
		*pp = NULL;
	while (p != NULL && p->element.first != theKey)
	{// �Ƶ�p��һ������
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)
		return; // û��ֵ����theKey
	// �ṹ��			
	if (p->leftChild != NULL && p->rightChild != NULL)// ��p����������ʱ
	{// ��������
	 //ת��Ϊ�����һ�����ӵ����
		binaryTreeNode<pair<const K, E> > *s = p->leftChild,*ps = p;  // ��p�����������ҵ�����Ԫ�أ�ps�� s �ĸ��ڵ�
		while (s->rightChild != NULL)
		{// �Ƶ�һ�������Ԫ��
			ps = s;
			s = s->rightChild;
		}// ��s��p���ƶ�����		 
		binaryTreeNode<pair<const K, E> > *q =new binaryTreeNode<pair<const K, E> >(s->element, p->leftChild, p->rightChild);// ��ֵΪ����ʱ��p->element = s->element
		if (pp == NULL)
			root = q;
		else if (p == pp->leftChild)
			pp->leftChild = q;
		else
			pp->rightChild = q;
		if (ps == p) pp = q;
		else pp = ps;
		delete p;
		p = s;
	}
	
	binaryTreeNode<pair<const K, E> > *c;
	if (p->leftChild != NULL)// p������һ������
		c = p->leftChild;
	else
		c = p->rightChild;
	if (p == root)// ɾ�� p
		root = c;
	else
	{// �ж�p��pp�����ӻ����Һ���
		if (p == pp->leftChild)
			pp->leftChild = c;
		else pp->rightChild = c;
	}
	treeSize--;
	delete p;
}
template <class K, class E>
ostream& operator<<(ostream& out, const pair<K, E>& x)
{
	out << x.first << ' ' << x.second; 
	return out;
}
class illegalParameterValue// illegal parameter value
{
public:
	illegalParameterValue(string theMessage = "Illegal parameter value")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class illegalInputData// illegal input data
{
public:
	illegalInputData(string theMessage = "Illegal data input")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class illegalIndex// illegal index
{
public:
	illegalIndex(string theMessage = "Illegal index")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class matrixIndexOutOfBounds// matrix index out of bounds
{
public:
	matrixIndexOutOfBounds(string theMessage = "Matrix index out of bounds")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class matrixSizeMismatch// matrix size mismatch
{
public:
	matrixSizeMismatch(string theMessage ="The size of the two matrics doesn't match")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class stackEmpty// stack is empty
{
public:
	stackEmpty(string theMessage ="Invalid operation on empty stack")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class queueEmpty// queue is empty
{
public:
	queueEmpty(string theMessage ="Invalid operation on empty queue")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class hashTableFull// hash table is full
{
public:
	hashTableFull(string theMessage ="The hash table is full")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class undefinedEdgeWeight// edge weight undefined
{
public:
	undefinedEdgeWeight(string theMessage ="No edge weights defined")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
class undefinedMethod// method undefined
{
public:
	undefinedMethod(string theMessage ="This method is undefined")
	{
		message = theMessage;
	}
	void outputMessage() { cout << message << endl; }
private:
	string message;
};
template<class T>
class completeWinnerTree
{
public:
	completeWinnerTree(T *thePlayer, int theNumberOfPlayers)
	{
		tree = NULL;
		initialize(thePlayer, theNumberOfPlayers);
	}
	~completeWinnerTree() { delete[] tree; }
	void initialize(T*, int);
	int winner() const
	{
		return tree[1];
	}
	int winner(int i) const
	{
		return (i < numberOfPlayers) ? tree[i] : 0;
	}
	void rePlay(int);
private:
	int lowExt;           // ��Ͳ���ⲿ�ڵ�
	int offset;           // 2^log(n-1) - 1
	int *tree;            // Ӯ����������
	int numberOfPlayers;
	T *player;            // ��Ա����
	void play(int, int, int);
};
template<class T>
void completeWinnerTree<T>::initialize(T *thePlayer,
	int theNumberOfPlayers)
{
	int n = theNumberOfPlayers;
	if (n < 2)
		throw illegalParameterValue("�����������������");
	player = thePlayer;
	numberOfPlayers = n;
	delete[] tree;
	tree = new int[n];
	int i, s;
	for (s = 1; 2 * s <= n - 1; s += s);// ����  s = 2^log (n-1)
	lowExt = 2 * (n - s);
	offset = 2 * s - 1;
	for (i = 2; i <= lowExt; i += 2)// ��Ͳ���ⲿ�ڵ�ı���
		play((offset + i) / 2, i - 1, i);	
	if (n % 2 == 1)// ����ʣ���ⲿ�ڵ�
	{// ��nΪ����ʱ�������ⲿ�ڵ���ڲ��ڵ�
		play(n / 2, tree[n - 1], lowExt + 1);
		i = lowExt + 3;
	}
	else i = lowExt + 2;
	for (; i <= n; i += 2)// i��ʣ�������ߵ��ⲿ�ڵ�
		play((i - lowExt + n - 1) / 2, i - 1, i);
}
template<class T>
void completeWinnerTree<T>::play(int p, int leftChild, int rightChild)
{
	tree[p] = (player[leftChild] <= player[rightChild]) ?leftChild : rightChild;// ��tree[p]��ʼ������leftChild ��p�����ӣ�rightChild ��p���Һ��� 
	while (p % 2 == 1 && p > 1)// ������Һ��ӣ������и���ı���
	{// ��һ���Һ���
		tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ?
			tree[p - 1] : tree[p];
		p /= 2;
	}
}
template<class T>
void completeWinnerTree<T>::rePlay(int thePlayer)
{
	int n = numberOfPlayers;// �������.
	if (thePlayer <= 0 || thePlayer > n)
		throw illegalParameterValue("��ҵ�ֵ������Ҫ��");
	int matchNode,       // ��һ��������ʼ�Ľڵ�
		leftChild,       // matchNode������
		rightChild;      // matchNode���Һ���	 
	if (thePlayer <= lowExt)// �ҵ���һ�������ڵ�����ĺ���
	{// ����ײ㿪ʼ
		matchNode = (offset + thePlayer) / 2;
		leftChild = 2 * matchNode - offset;
		rightChild = leftChild + 1;
	}
	else
	{
		matchNode = (thePlayer - lowExt + n - 1) / 2;
		if (2 * matchNode == n - 1)
		{
			leftChild = tree[2 * matchNode];
			rightChild = thePlayer;
		}
		else
		{
			leftChild = 2 * matchNode - n + 1 + lowExt;
			rightChild = leftChild + 1;
		}
	}
	tree[matchNode] = (player[leftChild] <= player[rightChild])
		? leftChild : rightChild;
	if (matchNode == n - 1 && n % 2 == 1)// �ڶ��������������
	{
		matchNode /= 2;   // ���򸸽ڵ�
		tree[matchNode] = (player[tree[n - 1]] <=
			player[lowExt + 1]) ?
			tree[n - 1] : lowExt + 1;
	}
	// ����ʣ��ı���
	matchNode /= 2;  // ���򸸽ڵ�
	for (; matchNode >= 1; matchNode /= 2)
		tree[matchNode] = (player[tree[2 * matchNode]] <=
			player[tree[2 * matchNode + 1]]) ?
		tree[2 * matchNode] : tree[2 * matchNode + 1];
}
template <class T>
class  AVLTreeNode
{	
public:
	int key;                // �ؼ���(��ֵ)
	int height;         // �߶�
	AVLTreeNode *left;    // ����
	AVLTreeNode *right;    // �Һ���
	int n;	
	AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r,int nn) :
	    key(value), height(0), left(l), right(r),n(nn) {}
	AVLTreeNode() :
		key(0), height(0), left(NULL), right(NULL),n(0) {}
};
template <class T>
class AVLTree 
{
private:
	AVLTreeNode<T> *mRoot;    // �����
public:
	AVLTree();
	~AVLTree();	
	int height();// ��ȡ���ĸ߶�
	int max(int a, int b);// ��ȡ���ĸ߶�
	void preOrder();// ǰ�����"AVL��"
	void inOrder();// �������"AVL��"
	void postOrder();// �������"AVL��"
	AVLTreeNode<T>* search(T key);// (�ݹ�ʵ��)����"AVL��"�м�ֵΪkey�Ľڵ�
	AVLTreeNode<T>* iterativeSearch(T key);// (�ǵݹ�ʵ��)����"AVL��"�м�ֵΪkey�Ľڵ�
	AVLTreeNode<T>* findGE(const T &k) const;
	T minimum();// ������С��㣺������С���ļ�ֵ��
	T maximum();// ��������㣺���������ļ�ֵ��
	void insert(T key,int n);// �����(keyΪ�ڵ��ֵ)���뵽AVL����
	void remove(T key);// ɾ�����(keyΪ�ڵ��ֵ)
	void destroy();// ����AVL��
	void print();// ��ӡAVL��
private:
	int height(AVLTreeNode<T>* tree);// ��ȡ���ĸ߶�
	void preOrder(AVLTreeNode<T>* tree) const;// ǰ�����"AVL��"
	void inOrder(AVLTreeNode<T>* tree) const;// �������"AVL��"
	void postOrder(AVLTreeNode<T>* tree) const;// �������"AVL��"
	AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;// (�ݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
	AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;// (�ǵݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
	AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);// ������С��㣺����treeΪ������AVL������С��㡣
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);// ��������㣺����treeΪ������AVL��������㡣
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);// LL�������Ӧ�����(����ת)��
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);// RR�����Ҷ�Ӧ�����(�ҵ���ת)��
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);// LR�����Ҷ�Ӧ�����(��˫��ת)��
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);// RL�������Ӧ�����(��˫��ת)��
	AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key,int n);// �����(z)���뵽AVL��(tree)��
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);// ɾ��AVL��(tree)�еĽ��(z)�������ر�ɾ���Ľ��
	void destroy(AVLTreeNode<T>* &tree);// ����AVL��
	void print(AVLTreeNode<T>* tree, T key, int direction);// ��ӡAVL��
};
template <class T>//���캯��
AVLTree<T>::AVLTree() :mRoot(NULL){}
template <class T>//��������
AVLTree<T>::~AVLTree()
{
	destroy(mRoot);
}
template <class T>//��ȡ���ĸ߶�
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
	if (tree != NULL)
		return tree->height;
	return 0;
}

template <class T>
int AVLTree<T>::height()
{
	return height(mRoot);
}
template <class T>//�Ƚ�����ֵ�Ĵ�С
int AVLTree<T>::max(int a, int b)
{
	return a>b ? a : b;
}
template <class T>//ǰ�����"AVL��"
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
	if (tree != NULL)
	{
		cout << tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}
template <class T>
void AVLTree<T>::preOrder()
{
	preOrder(mRoot);
}
template <class T>//�������"AVL��"
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const
{
	if (tree != NULL)
	{
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
	}
}
template <class T>
void AVLTree<T>::inOrder()
{
	inOrder(mRoot);
}
template <class T>//�������"AVL��"
void AVLTree<T>::postOrder(AVLTreeNode<T>* tree) const
{
	if (tree != NULL)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}
template <class T>
void AVLTree<T>::postOrder()
{
	postOrder(mRoot);
}
template <class T>//(�ݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* x, T key) const
{
	if (x == NULL || x->key == key)
		return x;
	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}
template <class T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
	return search(mRoot, key);
}
template <class T>//(�ǵݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const
{
	while ((x != NULL) && (x->key != key))
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}
template <class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
	return iterativeSearch(mRoot, key);
}
template <class T>//���Ҵ��ڵ���theKey����С�ؼ���
AVLTreeNode<T>* AVLTree<T>::findGE(const T &k) const
{
	AVLTreeNode<int>*x = mRoot;
	AVLTreeNode<int>*bestElement = NULL;
	while (x!=NULL)
	{
		if (k<= x->key) {
			bestElement = x;

			x = x->left;
		}
		else x = x->right;
	}
	return bestElement;
}
template <class T>//������С��㣺����treeΪ������AVL������С��㡣
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}
template <class T>
T AVLTree<T>::minimum()
{
	AVLTreeNode<T> *p = minimum(mRoot);
	if (p != NULL)
		return p->key;
	return (T)NULL;
}
template <class T>//��������㣺����treeΪ������AVL��������㡣
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}
template <class T>
T AVLTree<T>::maximum()
{
	AVLTreeNode<T> *p = maximum(mRoot);
	if (p != NULL)
		return p->key;

	return (T)NULL;
}
template <class T>//LL�������Ӧ�����(����ת)������ֵ����ת��ĸ��ڵ�
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
	AVLTreeNode<T>* k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	return k1;
}
template <class T>//RR�����Ҷ�Ӧ�����(�ҵ���ת)������ֵ����ת��ĸ��ڵ�
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
	AVLTreeNode<T>* k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	return k2;
}
template <class T>//LR�����Ҷ�Ӧ�����(��˫��ת)������ֵ����ת��ĸ��ڵ�
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
	k3->left = rightRightRotation(k3->left);
	return leftLeftRotation(k3);
}
template <class T>//RL�������Ӧ�����(��˫��ת)������ֵ����ת��ĸ��ڵ�
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
	k1->right = leftLeftRotation(k1->right);

	return rightRightRotation(k1);
}
template <class T>//�������뵽AVL���У������ظ��ڵ㡣����˵����tree AVL���ĸ���㣬key ����Ľ��ļ�ֵ������ֵ�����ڵ� 
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key,int n)
{
	if (tree == NULL)
	{
		tree = new AVLTreeNode<T>(key, NULL, NULL,n);// �½��ڵ�
		if (tree == NULL)
		{
			cout << "�����޷��������" << endl;
			return NULL;
		}
	}
	else if (key<=tree->key)//Ӧ�ý�key���뵽"tree��������"�����
	{
		tree->left = insert(tree->left, key,n);
		if (height(tree->left) - height(tree->right) == 2)// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		{
			if (key <= tree->left->key)
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else if (key > tree->key)//Ӧ�ý�key���뵽"tree��������"�����
	{
		tree->right = insert(tree->right, key,n);
		if (height(tree->right) - height(tree->left) == 2)// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		{
			if (key > tree->right->key)
				tree = rightRightRotation(tree);
			else
				tree = rightLeftRotation(tree);
		}
	}
    else if( key == tree->key)
	{
		cout << "���ʧ�ܣ������������ͬ�Ľڵ㣡" << endl;
	}
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}
template <class T>
void AVLTree<T>::insert(T key,int n)
{
	insert(mRoot, key,n);
}
template <class T>//ɾ�����(z)�����ظ��ڵ㡣����˵����tree AVL���ĸ���㣬z ��ɾ���Ľ�㡣����ֵ�����ڵ� 
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
	if (tree == NULL || z == NULL)// ��Ϊ�� ���� û��Ҫɾ���Ľڵ㣬ֱ�ӷ���NULL��
		return NULL;
	if (z->key < tree->key)//��ɾ���Ľڵ���"tree��������"��
	{
		tree->left = remove(tree->left, z);
		if (height(tree->right) - height(tree->left) == 2)// ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		{
			AVLTreeNode<T> *r = tree->right;
			if (height(r->left) > height(r->right))
				tree = rightLeftRotation(tree);
			else
				tree = rightRightRotation(tree);
		}
	}
	else if (z->key > tree->key)//��ɾ���Ľڵ���"tree��������"��
	{
		tree->right = remove(tree->right, z);
		if (height(tree->left) - height(tree->right) == 2)// ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		{
			AVLTreeNode<T> *l = tree->left;
			if (height(l->right) > height(l->left))
				tree = leftRightRotation(tree);
			else
				tree = leftLeftRotation(tree);
		}
	}
	else//tree�Ƕ�ӦҪɾ���Ľڵ㡣
	{
		if ((tree->left != NULL) && (tree->right != NULL))//tree�����Һ��Ӷ��ǿ�
		{
			if (height(tree->left) > height(tree->right))
			{
				// ���tree�����������������ߣ�
				// ��(01)�ҳ�tree���������е����ڵ�
				//   (02)�������ڵ��ֵ��ֵ��tree��
				//   (03)ɾ�������ڵ㡣
				// ����������"tree�������������ڵ�"��"tree"������
				// �������ַ�ʽ�ĺô��ǣ�ɾ��"tree�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				AVLTreeNode<T>* max = maximum(tree->left);
				tree->key = max->key;
				tree->n = max->n;
				tree->left = remove(tree->left, max);
			}
			else
			{
				// ���tree��������������������(��������ȣ�������������������1)
				// ��(01)�ҳ�tree���������е���С�ڵ�
				//   (02)������С�ڵ��ֵ��ֵ��tree��
				//   (03)ɾ������С�ڵ㡣
				// ����������"tree������������С�ڵ�"��"tree"������
				// �������ַ�ʽ�ĺô��ǣ�ɾ��"tree������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
				AVLTreeNode<T>* min = maximum(tree->right);
				tree->key = min->key;
				tree->n = min->n;
				tree->right = remove(tree->right, min);
			}
		}
		else
		{
			AVLTreeNode<T>* tmp = tree;
			tree = (tree->left != NULL) ? tree->left : tree->right;
			delete tmp;
		}
	}
	return tree;
}
template <class T>
void AVLTree<T>::remove(T key)
{
	AVLTreeNode<T>* z;
	if ((z = search(mRoot, key)) != NULL)
		mRoot = remove(mRoot, z);
}
template <class T>//����AVL��
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		destroy(tree->left);
	if (tree->right != NULL)
		destroy(tree->right);
	delete tree;
}
template <class T>
void AVLTree<T>::destroy()
{
	destroy(mRoot);
}
/*
* ��ӡ"���������"
* key        -- �ڵ�ļ�ֵ
* direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
*               -1����ʾ�ýڵ������ĸ���������;
*                1����ʾ�ýڵ������ĸ������Һ��ӡ�
*/
template <class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree�Ǹ��ڵ�
			cout << setw(2) << tree->key << "�ĸ���" << tree->n<<"����" << endl;
		else                // tree�Ƿ�֧�ڵ�
			cout << setw(2) << tree->key << "��" << tree->n << "����" << setw(2) << key << "��" << setw(12) << (direction == 1 ? "�Һ���" : "����") << endl;
		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}
template <class T>
void AVLTree<T>::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->key, 0);
}
using namespace std;
struct binType
{
	int unusedCapacity;
	bool operator <= (binType& right) const
	{
		return (unusedCapacity >= right.unusedCapacity) ? true : false;
	}
};
void select_sort(int *array, int n)
{
	int i, j, t;
	for (i = 1; i< n; i++)
	{
		for (j = i + 1; j<n + 1; j++)
		{
			if (array[j] > array[i])
			{
				t = array[j];
				array[j] = array[i];
				array[i] = t;
			}
		}
	}
}
void firstFitPack(int *objectSize, int numberOfObjects, int binCapacity)
{//�����������ΪbinCapacity����������װ��
	int n = numberOfObjects;//objectSize[1:numberOfObjects]����Ʒ��С����ʼ��һ�������ӱ�ŵ�����
	int *number = new int[n + 1];
	binType *bin = new binType[n + 1];//����
	for (int i = 1; i <= n; i++)//��ʼ��n�����Ӻ�Ӯ����
		bin[i].unusedCapacity = binCapacity; //���ӵ�ʣ������
	completeWinnerTree<binType> winTree(bin, n);
	for (int i = 1; i <= n; i++)//����Ʒװ��������
	{//����Ʒiװ��һ������
	 //�ҵ���һ�����㹻����������
		int child = 2;//�Ӹ������ӿ�ʼ����
		while (child < n)
		{
			int winner = winTree.winner(child);
			if (bin[winner].unusedCapacity < objectSize[i])
				child++;//��һ��������������
			child *= 2;//�ƶ�������
		}
		int binToUse;//����ΪҪʹ�õ�����
		child /= 2;//�������������ӵ��ƶ�
		if (child < n)
		{//��һ�����ڵ�
			binToUse = winTree.winner(child);
			if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i])//��binToUse���Һ��ӣ���Ҫ�������binToUse-1����ʹbinToUse�����ӣ��������binToUse-1Ҳ���������� 
				binToUse--;
		}
		else //��n������
			binToUse = winTree.winner(child / 2);
		number[i] = binToUse;
	    cout << "��Ʒ" << i << "װ����" << binToUse<<"��������" << endl;
		bin[binToUse].unusedCapacity -= objectSize[i];
		winTree.rePlay(binToUse);
	}
	select_sort(number, n);
	cout << "ʹ�õ���������" << number[1] << endl;
}
void bestFitPack(int *objectSize, int numberOfObjects, int binCapacity)
{//�������ΪbinCapacity����������ƥ��.
	int n = numberOfObjects;//objectSize[1:numberOfObjects]����Ʒ��С
	int *number = new int[n + 1];
	int binsUsed = 0;
	AVLTree<int>*theTree = new AVLTree<int>();
	AVLTreeNode<int>*theBin=new AVLTreeNode<int>();	
	for (int i = 1; i <= n; i++)//����Ʒ���װ��
	{//����Ʒiװ��
	 //Ѱ����ƥ�������		
		AVLTreeNode<int> *bestBin = theTree->findGE(objectSize[i]);		
		if (bestBin == NULL)
		{//û���㹻������ӣ�����һ��������
			theBin->key = binCapacity;
			theBin->n = ++binsUsed;			
		}
		else
		{
			*theBin = *bestBin;//����theTree��ɾ����ƥ�������
       theTree->remove(bestBin->key);
		}
		number[i] = theBin->n;
	    cout << "��Ʒ" << i << "װ����" << theBin->n << "��������"<< endl;
		//�����Ӳ嵽���У�������������
		theBin->key = theBin->key - objectSize[i];
	    cout << "����" << theBin->n << "ʣ" << theBin->key << "�ռ�" << endl;
		if (theBin->key > 0)
			theTree->insert(theBin->key,theBin->n);
		//theTree->print();
		//cout << endl;
		//cout << endl;
		//cout << endl;
	}
	select_sort(number, n);
	cout << "����������:" << number[1] << endl;
}
/*void best(int *objectSize, int numberOfObjects, int binCapacity)
{//�������ΪbinCapacity����������ƥ��.
 //objectSize[1:numberOfObjects]����Ʒ��С
	int n = numberOfObjects;
	int *number = new int[n + 1];
	int binsUsed = 0;
	dBinarySearchTreeWithGE<int, int> theTree;
	pair<int, int> theBin;

	//����Ʒ���װ��
	for (int i = 1; i <= n; i++)
	{//����Ʒiװ��
	 //Ѱ����ƥ�������
		auto *bestBin = theTree.findGE(objectSize[i]);
		if (bestBin == NULL)
		{//û���㹻������ӣ�����һ��������
			theBin.first = binCapacity;
			theBin.second = ++binsUsed;
		}
		else
		{//����theTree��ɾ����ƥ�������
			theBin = *bestBin;
			theTree.erase(bestBin->first);
		}
		number[i] = theBin.second;
		cout << "��Ʒ" << i << "װ����" << theBin.second << "��������"<< endl;
		//�����Ӳ嵽���У�������������
		theBin.first = theBin.first -objectSize[i];
		if (theBin.first > 0)
			theTree.insert(theBin);
		
	}

	select_sort(number, n);
	cout << "����������Ϊ" << number[1] << endl;
}

*/
int main()
{
		int n, binCapacity; //��Ʒ��������������
		cout << "--------------------------    ����װ������   ----------------------------"<< endl;
		cout << "�ֱ�������Ʒ����������������"<< endl;
		cin >> n >> binCapacity;
		int *objectSize = new int[n + 1];
		for (int i = 1; i <= n; i++)
		{
			objectSize[i] = rand() % binCapacity + 1;
		}
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
		cout << n << "����Ʒ�Ĵ�С�ֱ�Ϊ��" << endl;
		for (int i = 1; i <= n; i++)
		{
			cout << objectSize[i] << "  ";
		}
		cout << endl << endl;
		cout << "���÷��������ܱȽ�"<< endl;
		cout << "***************"<< endl;
		cout << "����ƥ�䷨(FF)��" << endl;
		clock_t s = clock();
		firstFitPack(objectSize, n, binCapacity);		
		clock_t e = clock();
		cout << "ʱ������:"<<(double)(e-s)/CLOCKS_PER_SEC<<"s"<< endl;
		cout << "****************"<< endl;
		cout << "����ƥ�䷨(BF)��" << endl;
		clock_t h = clock();
	bestFitPack(objectSize, n, binCapacity);
	clock_t m = clock();
	cout << "ʱ������:" << (double)(m- h) / CLOCKS_PER_SEC<<"s"<< endl;
	//best(objectSize, n, binCapacity);	
	cout << "****************"<< endl;
	cout << "����ƥ��ݼ�����FFD����" << endl;
	select_sort(objectSize, n);
	clock_t u = clock();
	firstFitPack(objectSize, n, binCapacity);
	clock_t v = clock();
	cout << "ʱ������:" << (double)(v- u) / CLOCKS_PER_SEC << "s"<< endl;
	cout << "****************"<< endl;
	cout << "����ƥ��ݼ�����BFD����" << endl;
	select_sort(objectSize, n);	
	clock_t r = clock();
	bestFitPack(objectSize, n, binCapacity);
	clock_t d= clock();
	cout << "ʱ������:" << (double)(d- r) / CLOCKS_PER_SEC << "s"<< endl;
}
