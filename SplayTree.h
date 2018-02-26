#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <iomanip>
using namespace std;

typedef struct SplayNode *TreeNode; // �ڵ����������������

/* ��չ���ڵ�
 * ��������:
 * Element:����Ԫ��
 * Left:�������ڵ�
 * Right:�������ڵ�
 */
struct SplayNode {
	int Element;
	TreeNode Left;
	TreeNode Right;
};

/* SplayTree��
 * �ӿ�:
 * MakeEmpty:�ÿպ����������ṹ�ÿ�
 * Splay:��չ��������Ŀ��ڵ�չ��
 * Find:���Һ���������Ŀ��Ԫ��
 * Insert:���뺯��������Ŀ��Ԫ��
 * Remove:ɾ��������ɾ��Ŀ��Ԫ��
 * Display:չʾ������չʾ���е���Ϣ
 */
class SplayTree
{
public:
	// ���캯��
	SplayTree();
	// ��������
	~SplayTree();

	// �ӿں���
	void MakeEmpty();
	void  Splay(const int);
	int Find(const int);
	void Insert(const int);
	void Remove(const int);
	void Display();

private:
	// �������ܺ���
	void Splay(const int, TreeNode &);
	void MakeEmpty(TreeNode);
	void Display(const TreeNode&,const int, const int);
	void SingleRotateWithRight(TreeNode &);
	void SingleRotateWithLeft(TreeNode &);

	TreeNode Root; // ������ڵ�
	TreeNode NullNode; // ����ձ�־�ڵ�
};

#endif // !SPLAYTREE_H



