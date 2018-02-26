#include "stdafx.h"
#include "SplayTree.h"

/* 构造函数:初始化对象
 * 返回值:无
 * 参数:无
 */
SplayTree::SplayTree()
{
	NullNode = new SplayNode(); // 初始化空标志节点
	if (NullNode == NULL)
		cout << "标志节点申请失败!" << endl;
	NullNode->Element = 0;
	NullNode->Left = NullNode->Right = NullNode; 

	Root = NullNode; // 初始化根节点
}

/* 析构函数:对象消亡时回收内存空间
 * 返回值:无
 * 参数:无
 */
SplayTree::~SplayTree()
{
	MakeEmpty(); // 树置空
	delete Root; // 删除根节点
	Root = NULL;
	delete NullNode; // 删除标志2节点
	NullNode = NULL;
}

/* 置空函数:将树置空
 * 返回值:无
 * 参数:无
 */
void SplayTree::MakeEmpty() {
	MakeEmpty(Root); // 将根节点置空
	Root = NullNode; // 置空后再次初始化
}

/* 置空函数:将目标节点置空
 * 返回值:无
 * 参数:无
 */
void SplayTree::MakeEmpty(TreeNode Tree) {
	if (Tree != NullNode) { // 判断目标是否需要置空
		// 递归置空其子树
		MakeEmpty(Tree->Left);
		MakeEmpty(Tree->Right);
		delete Tree; // 删除当前节点
		Tree = NULL;
	}
}

/* 伸展函数:将根节点根据目标元素进行伸展
 * 返回值:无
 * 参数:key:目标元素
 */
void SplayTree::Splay(const int key) {
	Splay(key, Root);
}

/* 伸展函数:将目标节点根据目标元素进行伸展
 * 返回值:无
 * 参数:key:目标元素；root:伸展的目标节点
 */
void SplayTree::Splay(const int key, TreeNode &root) {
	static struct SplayNode Header; // 储存静态头结点，减少系统开销
	TreeNode LeftTreeMax, RightTreeMin; // 储存左树与右树

	Header.Left = Header.Right = NullNode; // 初始化头结点
	LeftTreeMax = RightTreeMin = &Header; // 将左树与右树与头结点连接
	NullNode->Element = key; // 防止重复操作

	while (key != root->Element) { // 判断是否已将目标元素伸展至最上层
		// 将根节点向右侧伸展
		if (key < root->Element) {
			if (root->Left == NullNode) // 此处使用空标志节点而不是NULL，可以极大地简化程序，同时避免NULL->Element的使用
				break;
			if (key < root->Left->Element) // zig-zig特殊情形处理
				SingleRotateWithLeft(root);

			// 特别说明:
			//     因为可以将zig-zag情形简化操作，其步骤与单旋转操作相同，同时因为zig-zig
			// 情形比其他两种情况多一步，所以将zig-zig情形单独判断，而其他两种情况没有做独
			// 的判断，而是何在一起使用。

			// 将根以及其右树接到右树上
			RightTreeMin->Left = root;
			RightTreeMin = root; // 更新右树插入位置
			root = root->Left; // 更新树根
		}

		// 将根节点向左侧伸展
		else {
			if (root->Right == NullNode)
				break;
			if (key > root->Right->Element) // zig-zig特殊情形处理
				SingleRotateWithRight(root);

			// 将根及其左树接到其左树上
			LeftTreeMax->Right = root;
			LeftTreeMax = root; // 更新左树插入位置
			root = root->Right; // 更新树根
		}
	}
	// 完成整理操作
	LeftTreeMax->Right = root->Left;
	RightTreeMin->Left = root->Right;

	// 完成左右树与根合并
	root->Left = Header.Right;
	root->Right = Header.Left;
}

/* 右旋转函数:将目标节点向右旋转
 * 返回值:无
 * 参数:Tree:想要进行右旋转的目标节点
 */
void SplayTree::SingleRotateWithLeft(TreeNode &Tree) {
	TreeNode LeftChild; // 储存左子树
	// 进行旋转操作
	LeftChild = Tree->Left;
	Tree->Left = LeftChild->Right;
	LeftChild->Right = Tree;

	Tree = LeftChild; // 更新目标节点
}

/* 左旋转函数:将目标节点向左旋转
 * 返回值:无
 * 参数:Tree:想要进行左旋转的目标节点
 */
void SplayTree::SingleRotateWithRight(TreeNode &Tree) {
	TreeNode RightChild; // 储存右子树
	// 进行旋转操作
	RightChild = Tree->Right;
	Tree->Right = RightChild->Left;
	RightChild->Left = Tree;

	Tree = RightChild; // 更新目标节点
}

/* 查找函数:查找目标元素，并返回值
 * 返回值:int:目标元素的值
 * 参数:key:想要查找的目标元素
 */
int SplayTree::Find(int key) {
	Splay(key, Root); // 将根部展开
	if (Root->Element != key) { // 判断元素是否存在
		cout << "不存在元素:" << key << endl;
		return NULL;
	}
	else
		return key;
}

/* 插入函数:插入目标元素
 * 返回值:无
 * 参数:key:想要插入的目标元素
 */
void SplayTree::Insert(const int key) {
	static TreeNode NewNode = NULL; // 储存静态新节点，减少系统开销
	if (NewNode == NULL) { // 判断新节点是否置空
		NewNode = new SplayNode(); // 初始化新节点
		if (NewNode == NULL)
			cout << "新节点内存分配失败!" << endl;
	}
	NewNode->Element = key;

	if (Root == NullNode) { // 判断树根是否为空标志
		// 直接赋值新节点
		NewNode->Left = NewNode->Right = NullNode;
		Root = NewNode;
	}

	else {
		Splay(key, Root); // 将根节点伸展

		// 向左侧插入
		if (key < Root->Element) {
			//        NewNode
			//        /     \
			//  Root->Left  Root  
			NewNode->Left = Root->Left;
			NewNode->Right = Root;
			Root->Left = NullNode;
			Root = NewNode;
		}

		// 向右侧插入
		else if (key > Root->Element) {
			//        NewNode
			//        /     \
			//     Root  Root->Right
			NewNode->Right = Root->Right;
			NewNode->Left = Root;
			Root->Right = NullNode;
			Root = NewNode;
		}

		else // 已经在树中不需要插入
			return;
	}

	NewNode = NULL;
}

/* 删除函数:删除树中的目标元素
 * 返回值:无
 * 参数:key:想要删除的目标元素
 */
void SplayTree::Remove(const int key) {
	TreeNode NewNode; // 储存新节点

	if (Root == NullNode) // 判断树是否可以执行删除操作
		cout << "空树不能执行删除操作!" << endl;
	else {
		Splay(key, Root); // 沿着根部展开
		// 判断是否存在目标元素
		if (key == Root->Element) {
			// 如果其左子树为空标志，直接把右子树当做新的树根（也可以反过来写）
			if (Root->Left == NullNode)
				NewNode = Root->Right;
			else {
				NewNode = Root->Left;
				Splay(key, NewNode); // 将其左子树展开
				NewNode->Right = Root->Right; // 移接旧的右子树
			}
			delete Root; // 删除旧树根
			Root = NewNode; // 更新树根
		}
	}
}

/* 展示函数:展示树中的信息
 * 返回值:无
 * 参数:无
 */
void SplayTree::Display() {
	Display(Root, 1, 0); // 展示树根信息
}

/* 展示函数:展示目标节点信息
 * 返回值:无
 * 参数:Tree:想要展示的目标节点；index:节点所在层数
 */
void SplayTree::Display(const TreeNode &Tree, const int index, const int x) {
	// 判断是否可以执行展示功能
	if (Tree != NullNode) {
		// 中序展示信息
		if (x == 1)
			cout << "左";
		if (x == 2)
			cout << "右";
		cout << "第" << index << "层: " << Tree->Element << endl;
		Display(Tree->Left, index + 1, 1); // 递归展示左子树

		Display(Tree->Right, index + 1, 2); // 递归展示右子树
	}
	else
		return;
}