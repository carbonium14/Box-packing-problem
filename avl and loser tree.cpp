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
	binaryTreeNode<T> *leftChild,   // 左子树
		*rightChild;  // 右子树
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
{//返回一个元素的指针，这个元素的关键字是不小于thekey的最小关键字
 // 如果这样的元素不存在，返回NULL
	binaryTreeNode<pair<const K, E> > *currentNode = root;
	pair<const K, E> *bestElement = NULL; // 目前找到的元素，其关键字是不小于thekey的最小关键字										  
	while (currentNode != NULL)
		if (currentNode->element.first >= theKey)// currentNode->element 是一个候选者吗
		{
			bestElement = &currentNode->element;// 是, currentNode->element 是比bestElement更好的候选者
			currentNode = currentNode->leftChild;// 左子树中唯一较小的关键字
		}
		else// 不是, currentNode->element.first 太小
			currentNode = currentNode->rightChild;// 检查右子树
	return bestElement;
}
template<class K, class E>
void dBinarySearchTreeWithGE<K, E>::insert( const pair< K, E>& thePair)
{// 把thePair插入到树中. 允许重复值.
 // 找到地方插入
	binaryTreeNode<pair<const K, E> > *p = root,
		*pp = NULL;
	while (p != NULL)
	{// 检查 p->element
		pp = p;
		if (thePair.first <= p->element.first)// 把p移到一个孩子
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	binaryTreeNode<pair<const K, E> > *newNode// 为thePair找到一个节点再连接到pp
		= new binaryTreeNode<pair<const K, E> >(thePair);
	if (root != NULL) // 树不是空的
		if (thePair.first <= pp->element.first)
			pp->leftChild = newNode;
		else
			pp->rightChild = newNode;
	else
		root = newNode; // 插入空树
	treeSize++;
}
template<class K, class E>
void dBinarySearchTreeWithGE<K, E>::erase(const K& theKey)
{// 删除值等于theKey的元素
 // 为theKey找到一个节点
	binaryTreeNode<pair<const K, E> > *p = root,
		*pp = NULL;
	while (p != NULL && p->element.first != theKey)
	{// 移到p的一个孩子
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)
		return; // 没有值等于theKey
	// 结构树			
	if (p->leftChild != NULL && p->rightChild != NULL)// 当p有两个孩子时
	{// 两个孩子
	 //转换为零或者一个孩子的情况
		binaryTreeNode<pair<const K, E> > *s = p->leftChild,*ps = p;  // 在p的左子树中找到最大的元素，ps是 s 的父节点
		while (s->rightChild != NULL)
		{// 移到一个更大的元素
			ps = s;
			s = s->rightChild;
		}// 从s到p，移动最大的		 
		binaryTreeNode<pair<const K, E> > *q =new binaryTreeNode<pair<const K, E> >(s->element, p->leftChild, p->rightChild);// 当值为常量时，p->element = s->element
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
	if (p->leftChild != NULL)// p至多有一个孩子
		c = p->leftChild;
	else
		c = p->rightChild;
	if (p == root)// 删除 p
		root = c;
	else
	{// 判断p是pp的左孩子还是右孩子
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
	int lowExt;           // 最低层次外部节点
	int offset;           // 2^log(n-1) - 1
	int *tree;            // 赢者树的数组
	int numberOfPlayers;
	T *player;            // 成员数组
	void play(int, int, int);
};
template<class T>
void completeWinnerTree<T>::initialize(T *thePlayer,
	int theNumberOfPlayers)
{
	int n = theNumberOfPlayers;
	if (n < 2)
		throw illegalParameterValue("必须至少有两个玩家");
	player = thePlayer;
	numberOfPlayers = n;
	delete[] tree;
	tree = new int[n];
	int i, s;
	for (s = 1; 2 * s <= n - 1; s += s);// 计算  s = 2^log (n-1)
	lowExt = 2 * (n - s);
	offset = 2 * s - 1;
	for (i = 2; i <= lowExt; i += 2)// 最低层次外部节点的比赛
		play((offset + i) / 2, i - 1, i);	
	if (n % 2 == 1)// 处理剩余外部节点
	{// 当n为奇数时，比赛外部节点和内部节点
		play(n / 2, tree[n - 1], lowExt + 1);
		i = lowExt + 3;
	}
	else i = lowExt + 2;
	for (; i <= n; i += 2)// i是剩余的最左边的外部节点
		play((i - lowExt + n - 1) / 2, i - 1, i);
}
template<class T>
void completeWinnerTree<T>::play(int p, int leftChild, int rightChild)
{
	tree[p] = (player[leftChild] <= player[rightChild]) ?leftChild : rightChild;// 在tree[p]开始比赛，leftChild 是p的左孩子，rightChild 是p的右孩子 
	while (p % 2 == 1 && p > 1)// 如果在右孩子，可能有更多的比赛
	{// 在一个右孩子
		tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ?
			tree[p - 1] : tree[p];
		p /= 2;
	}
}
template<class T>
void completeWinnerTree<T>::rePlay(int thePlayer)
{
	int n = numberOfPlayers;// 重组比赛.
	if (thePlayer <= 0 || thePlayer > n)
		throw illegalParameterValue("玩家的值不符合要求");
	int matchNode,       // 下一场比赛开始的节点
		leftChild,       // matchNode的左孩子
		rightChild;      // matchNode的右孩子	 
	if (thePlayer <= lowExt)// 找到第一场比赛节点和它的孩子
	{// 从最底层开始
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
	if (matchNode == n - 1 && n % 2 == 1)// 第二场比赛特殊情况
	{
		matchNode /= 2;   // 移向父节点
		tree[matchNode] = (player[tree[n - 1]] <=
			player[lowExt + 1]) ?
			tree[n - 1] : lowExt + 1;
	}
	// 进行剩余的比赛
	matchNode /= 2;  // 移向父节点
	for (; matchNode >= 1; matchNode /= 2)
		tree[matchNode] = (player[tree[2 * matchNode]] <=
			player[tree[2 * matchNode + 1]]) ?
		tree[2 * matchNode] : tree[2 * matchNode + 1];
}
template <class T>
class  AVLTreeNode
{	
public:
	int key;                // 关键字(键值)
	int height;         // 高度
	AVLTreeNode *left;    // 左孩子
	AVLTreeNode *right;    // 右孩子
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
	AVLTreeNode<T> *mRoot;    // 根结点
public:
	AVLTree();
	~AVLTree();	
	int height();// 获取树的高度
	int max(int a, int b);// 获取树的高度
	void preOrder();// 前序遍历"AVL树"
	void inOrder();// 中序遍历"AVL树"
	void postOrder();// 后序遍历"AVL树"
	AVLTreeNode<T>* search(T key);// (递归实现)查找"AVL树"中键值为key的节点
	AVLTreeNode<T>* iterativeSearch(T key);// (非递归实现)查找"AVL树"中键值为key的节点
	AVLTreeNode<T>* findGE(const T &k) const;
	T minimum();// 查找最小结点：返回最小结点的键值。
	T maximum();// 查找最大结点：返回最大结点的键值。
	void insert(T key,int n);// 将结点(key为节点键值)插入到AVL树中
	void remove(T key);// 删除结点(key为节点键值)
	void destroy();// 销毁AVL树
	void print();// 打印AVL树
private:
	int height(AVLTreeNode<T>* tree);// 获取树的高度
	void preOrder(AVLTreeNode<T>* tree) const;// 前序遍历"AVL树"
	void inOrder(AVLTreeNode<T>* tree) const;// 中序遍历"AVL树"
	void postOrder(AVLTreeNode<T>* tree) const;// 后序遍历"AVL树"
	AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;// (递归实现)查找"AVL树x"中键值为key的节点
	AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;// (非递归实现)查找"AVL树x"中键值为key的节点
	AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);// 查找最小结点：返回tree为根结点的AVL树的最小结点。
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);// 查找最大结点：返回tree为根结点的AVL树的最大结点。
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);// LL：左左对应的情况(左单旋转)。
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);// RR：右右对应的情况(右单旋转)。
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);// LR：左右对应的情况(左双旋转)。
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);// RL：右左对应的情况(右双旋转)。
	AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key,int n);// 将结点(z)插入到AVL树(tree)中
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);// 删除AVL树(tree)中的结点(z)，并返回被删除的结点
	void destroy(AVLTreeNode<T>* &tree);// 销毁AVL树
	void print(AVLTreeNode<T>* tree, T key, int direction);// 打印AVL树
};
template <class T>//构造函数
AVLTree<T>::AVLTree() :mRoot(NULL){}
template <class T>//析构函数
AVLTree<T>::~AVLTree()
{
	destroy(mRoot);
}
template <class T>//获取树的高度
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
template <class T>//比较两个值的大小
int AVLTree<T>::max(int a, int b)
{
	return a>b ? a : b;
}
template <class T>//前序遍历"AVL树"
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
template <class T>//中序遍历"AVL树"
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
template <class T>//后序遍历"AVL树"
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
template <class T>//(递归实现)查找"AVL树x"中键值为key的节点
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
template <class T>//(非递归实现)查找"AVL树x"中键值为key的节点
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
template <class T>//查找大于等于theKey的最小关键字
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
template <class T>//查找最小结点：返回tree为根结点的AVL树的最小结点。
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
template <class T>//查找最大结点：返回tree为根结点的AVL树的最大结点。
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
template <class T>//LL：左左对应的情况(左单旋转)。返回值：旋转后的根节点
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
template <class T>//RR：右右对应的情况(右单旋转)。返回值：旋转后的根节点
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
template <class T>//LR：左右对应的情况(左双旋转)。返回值：旋转后的根节点
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
	k3->left = rightRightRotation(k3->left);
	return leftLeftRotation(k3);
}
template <class T>//RL：右左对应的情况(右双旋转)。返回值：旋转后的根节点
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
	k1->right = leftLeftRotation(k1->right);

	return rightRightRotation(k1);
}
template <class T>//将结点插入到AVL树中，并返回根节点。参数说明：tree AVL树的根结点，key 插入的结点的键值。返回值：根节点 
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key,int n)
{
	if (tree == NULL)
	{
		tree = new AVLTreeNode<T>(key, NULL, NULL,n);// 新建节点
		if (tree == NULL)
		{
			cout << "错误：无法创建结点" << endl;
			return NULL;
		}
	}
	else if (key<=tree->key)//应该将key插入到"tree的左子树"的情况
	{
		tree->left = insert(tree->left, key,n);
		if (height(tree->left) - height(tree->right) == 2)// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		{
			if (key <= tree->left->key)
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else if (key > tree->key)//应该将key插入到"tree的右子树"的情况
	{
		tree->right = insert(tree->right, key,n);
		if (height(tree->right) - height(tree->left) == 2)// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		{
			if (key > tree->right->key)
				tree = rightRightRotation(tree);
			else
				tree = rightLeftRotation(tree);
		}
	}
    else if( key == tree->key)
	{
		cout << "添加失败：不允许添加相同的节点！" << endl;
	}
	tree->height = max(height(tree->left), height(tree->right)) + 1;
	return tree;
}
template <class T>
void AVLTree<T>::insert(T key,int n)
{
	insert(mRoot, key,n);
}
template <class T>//删除结点(z)，返回根节点。参数说明：tree AVL树的根结点，z 待删除的结点。返回值：根节点 
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
	if (tree == NULL || z == NULL)// 根为空 或者 没有要删除的节点，直接返回NULL。
		return NULL;
	if (z->key < tree->key)//待删除的节点在"tree的左子树"中
	{
		tree->left = remove(tree->left, z);
		if (height(tree->right) - height(tree->left) == 2)// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		{
			AVLTreeNode<T> *r = tree->right;
			if (height(r->left) > height(r->right))
				tree = rightLeftRotation(tree);
			else
				tree = rightRightRotation(tree);
		}
	}
	else if (z->key > tree->key)//待删除的节点在"tree的右子树"中
	{
		tree->right = remove(tree->right, z);
		if (height(tree->left) - height(tree->right) == 2)// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		{
			AVLTreeNode<T> *l = tree->left;
			if (height(l->right) > height(l->left))
				tree = leftRightRotation(tree);
			else
				tree = leftLeftRotation(tree);
		}
	}
	else//tree是对应要删除的节点。
	{
		if ((tree->left != NULL) && (tree->right != NULL))//tree的左右孩子都非空
		{
			if (height(tree->left) > height(tree->right))
			{
				// 如果tree的左子树比右子树高；
				// 则(01)找出tree的左子树中的最大节点
				//   (02)将该最大节点的值赋值给tree。
				//   (03)删除该最大节点。
				// 这类似于用"tree的左子树中最大节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
				AVLTreeNode<T>* max = maximum(tree->left);
				tree->key = max->key;
				tree->n = max->n;
				tree->left = remove(tree->left, max);
			}
			else
			{
				// 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
				// 则(01)找出tree的右子树中的最小节点
				//   (02)将该最小节点的值赋值给tree。
				//   (03)删除该最小节点。
				// 这类似于用"tree的右子树中最小节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
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
template <class T>//销毁AVL树
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
* 打印"二叉查找树"
* key        -- 节点的键值
* direction  --  0，表示该节点是根节点;
*               -1，表示该节点是它的父结点的左孩子;
*                1，表示该节点是它的父结点的右孩子。
*/
template <class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree是根节点
			cout << setw(2) << tree->key << "的根是" << tree->n<<"箱子" << endl;
		else                // tree是分支节点
			cout << setw(2) << tree->key << "是" << tree->n << "箱子" << setw(2) << key << "的" << setw(12) << (direction == 1 ? "右孩子" : "左孩子") << endl;
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
{//输出箱子容量为binCapacity的最先适配装载
	int n = numberOfObjects;//objectSize[1:numberOfObjects]是物品大小，初始化一个放箱子编号的数组
	int *number = new int[n + 1];
	binType *bin = new binType[n + 1];//箱子
	for (int i = 1; i <= n; i++)//初始化n个箱子和赢者树
		bin[i].unusedCapacity = binCapacity; //箱子的剩余容量
	completeWinnerTree<binType> winTree(bin, n);
	for (int i = 1; i <= n; i++)//将物品装到箱子里
	{//把物品i装入一个箱子
	 //找到第一个有足够容量的箱子
		int child = 2;//从根的左孩子开始搜索
		while (child < n)
		{
			int winner = winTree.winner(child);
			if (bin[winner].unusedCapacity < objectSize[i])
				child++;//第一个箱子在右子树
			child *= 2;//移动到左孩子
		}
		int binToUse;//设置为要使用的箱子
		child /= 2;//撤销向最后的左孩子的移动
		if (child < n)
		{//在一个树节点
			binToUse = winTree.winner(child);
			if (binToUse > 1 && bin[binToUse - 1].unusedCapacity >= objectSize[i])//若binToUse是右孩子，则要检查箱子binToUse-1，即使binToUse是左孩子，检查箱子binToUse-1也不会有问题 
				binToUse--;
		}
		else //当n是奇数
			binToUse = winTree.winner(child / 2);
		number[i] = binToUse;
	    cout << "物品" << i << "装到第" << binToUse<<"个箱子中" << endl;
		bin[binToUse].unusedCapacity -= objectSize[i];
		winTree.rePlay(binToUse);
	}
	select_sort(number, n);
	cout << "使用的箱子数：" << number[1] << endl;
}
void bestFitPack(int *objectSize, int numberOfObjects, int binCapacity)
{//输出容量为binCapacity的最优箱子匹配.
	int n = numberOfObjects;//objectSize[1:numberOfObjects]是物品大小
	int *number = new int[n + 1];
	int binsUsed = 0;
	AVLTree<int>*theTree = new AVLTree<int>();
	AVLTreeNode<int>*theBin=new AVLTreeNode<int>();	
	for (int i = 1; i <= n; i++)//将物品逐个装箱
	{//将物品i装箱
	 //寻找最匹配的箱子		
		AVLTreeNode<int> *bestBin = theTree->findGE(objectSize[i]);		
		if (bestBin == NULL)
		{//没有足够大的箱子，启用一个新箱子
			theBin->key = binCapacity;
			theBin->n = ++binsUsed;			
		}
		else
		{
			*theBin = *bestBin;//从树theTree中删除最匹配的箱子
       theTree->remove(bestBin->key);
		}
		number[i] = theBin->n;
	    cout << "物品" << i << "装到第" << theBin->n << "个箱子中"<< endl;
		//将箱子插到树中，除非箱子已满
		theBin->key = theBin->key - objectSize[i];
	    cout << "箱子" << theBin->n << "剩" << theBin->key << "空间" << endl;
		if (theBin->key > 0)
			theTree->insert(theBin->key,theBin->n);
		//theTree->print();
		//cout << endl;
		//cout << endl;
		//cout << endl;
	}
	select_sort(number, n);
	cout << "所用箱子数:" << number[1] << endl;
}
/*void best(int *objectSize, int numberOfObjects, int binCapacity)
{//输出容量为binCapacity的最优箱子匹配.
 //objectSize[1:numberOfObjects]是物品大小
	int n = numberOfObjects;
	int *number = new int[n + 1];
	int binsUsed = 0;
	dBinarySearchTreeWithGE<int, int> theTree;
	pair<int, int> theBin;

	//将物品逐个装箱
	for (int i = 1; i <= n; i++)
	{//将物品i装箱
	 //寻找最匹配的箱子
		auto *bestBin = theTree.findGE(objectSize[i]);
		if (bestBin == NULL)
		{//没有足够大的箱子，启用一个新箱子
			theBin.first = binCapacity;
			theBin.second = ++binsUsed;
		}
		else
		{//从树theTree中删除最匹配的箱子
			theBin = *bestBin;
			theTree.erase(bestBin->first);
		}
		number[i] = theBin.second;
		cout << "物品" << i << "装到第" << theBin.second << "个箱子中"<< endl;
		//将箱子插到树中，除非箱子已满
		theBin.first = theBin.first -objectSize[i];
		if (theBin.first > 0)
			theTree.insert(theBin);
		
	}

	select_sort(number, n);
	cout << "所用箱子数为" << number[1] << endl;
}

*/
int main()
{
		int n, binCapacity; //物品数量和箱子容量
		cout << "--------------------------    箱子装箱问题   ----------------------------"<< endl;
		cout << "分别输入物品数量和箱子容量："<< endl;
		cin >> n >> binCapacity;
		int *objectSize = new int[n + 1];
		for (int i = 1; i <= n; i++)
		{
			objectSize[i] = rand() % binCapacity + 1;
		}
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;
		cout << n << "个物品的大小分别为：" << endl;
		for (int i = 1; i <= n; i++)
		{
			cout << objectSize[i] << "  ";
		}
		cout << endl << endl;
		cout << "常用方法的性能比较"<< endl;
		cout << "***************"<< endl;
		cout << "最先匹配法(FF)：" << endl;
		clock_t s = clock();
		firstFitPack(objectSize, n, binCapacity);		
		clock_t e = clock();
		cout << "时间消耗:"<<(double)(e-s)/CLOCKS_PER_SEC<<"s"<< endl;
		cout << "****************"<< endl;
		cout << "最优匹配法(BF)：" << endl;
		clock_t h = clock();
	bestFitPack(objectSize, n, binCapacity);
	clock_t m = clock();
	cout << "时间消耗:" << (double)(m- h) / CLOCKS_PER_SEC<<"s"<< endl;
	//best(objectSize, n, binCapacity);	
	cout << "****************"<< endl;
	cout << "最先匹配递减法（FFD）：" << endl;
	select_sort(objectSize, n);
	clock_t u = clock();
	firstFitPack(objectSize, n, binCapacity);
	clock_t v = clock();
	cout << "时间消耗:" << (double)(v- u) / CLOCKS_PER_SEC << "s"<< endl;
	cout << "****************"<< endl;
	cout << "最优匹配递减法（BFD）：" << endl;
	select_sort(objectSize, n);	
	clock_t r = clock();
	bestFitPack(objectSize, n, binCapacity);
	clock_t d= clock();
	cout << "时间消耗:" << (double)(d- r) / CLOCKS_PER_SEC << "s"<< endl;
}
