#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <iomanip>
using namespace std;

typedef struct SplayNode *TreeNode; // 节点重命名，方便操作

/* 伸展树节点
 * 储存数据:
 * Element:储存元素
 * Left:左子树节点
 * Right:右子树节点
 */
struct SplayNode {
	int Element;
	TreeNode Left;
	TreeNode Right;
};

/* SplayTree类
 * 接口:
 * MakeEmpty:置空函数，将树结构置空
 * Splay:伸展函数，将目标节点展开
 * Find:查找函数，查找目标元素
 * Insert:插入函数，插入目标元素
 * Remove:删除函数，删除目标元素
 * Display:展示函数，展示树中的信息
 */
class SplayTree
{
public:
	// 构造函数
	SplayTree();
	// 析构函数
	~SplayTree();

	// 接口函数
	void MakeEmpty();
	void  Splay(const int);
	int Find(const int);
	void Insert(const int);
	void Remove(const int);
	void Display();

private:
	// 辅助功能函数
	void Splay(const int, TreeNode &);
	void MakeEmpty(TreeNode);
	void Display(const TreeNode&,const int, const int);
	void SingleRotateWithRight(TreeNode &);
	void SingleRotateWithLeft(TreeNode &);

	TreeNode Root; // 储存根节点
	TreeNode NullNode; // 储存空标志节点
};

#endif // !SPLAYTREE_H



