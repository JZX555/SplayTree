#前言：
我现在是一个大二的学生，因为下个学期就要开始学习数据结构这门课程，出于兴趣我提前将数据结构自学了一遍，在学习的过程中发现了许多有趣的结构，最近终于有了一点时间，决定开始写点博客，记录一下自己的想法；这是我第一次写博客，如果有不好的地方欢迎大家指出，我们可以一同讨论共同进步。


#原理：
伸展树(SplayTree)是一种平衡树的结构，是二叉搜索树的一种，他保证从空树开始的任意连续M次对树的操作最多花费O(M logN)时间。虽然与AVL树以及红黑树相比它的时间复杂度似乎要高一些，但是其空间要求以及编程复杂度要更低。接下来，我就来介绍一下伸展树的特性。

有一种原则叫做叫做"二八原则"，也就是说百分之八十的搜索都发生在百分之二十的数据上，伸展树也就是满足这种需求出现的。为了满足这些需求，伸展树在每一次操作后都会把操作的元素，通过一系列的旋转放置到树的根部(插入，删除，查找)，在图一中，我们可以看到被查找元素被移动到树根。这样，根据二八原则，访问次数更多的元素，总是在离树根更近的地方，也就减少了检索的时间消耗，增加了效率。在我看来，这是一种非常有想法的一种数据结构，也让人印象深刻。 
![](http://img.blog.csdn.net/20180224143214773?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzQxNDI3NDAw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


#C++实现：
##1.旋转操作：
如果学习过了AVL树，那么你对旋转操作一定不会陌生，在AVL树中旋转被分为了双旋转和单旋转两种情况(当然，双旋转也就是两个单旋转)。而在我们的伸展树中，也将使用到旋转操作，不过与AVL树有点不同。
旋转操作可以说是平衡树结构中最最最基础的东西了，它是移动节点的一种有效方式，以图二右旋转为例，我们将当前节点(**N节点**)变为父节点(__F节点__)，父节点变为当前节点的右儿子，同时将原来的右儿子(**S节点**)链接到F节点的左儿子，完成旋转操作。左旋转操作与右旋转操作相同，只是方向相反，这里就不再讲解了。(*其实是不想画图了*)
![](http://img.blog.csdn.net/20180224144415190?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzQxNDI3NDAw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
		
下面是我们的实现代码:

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
*PS：有些朋友可能会觉得奇怪，因为这里的旋转代码并没有将父节点与祖父节点链接，难道不会出错吗？不用担心，这是因为伸展树的特殊性，同时也与我们使用的伸展方法有关系，会在后面具体解释。*

##2.伸展操作：
接下来的就是伸展操作，可以说伸展操作是整个伸展树的核心功能，因为所有的功能，都是根据伸展操作进行的(查找，插入，删除)。而伸展操作有两种实现方式。
###自底向上伸展：
这是一种很容易想到的伸展方式，我们通过从树根处开始检索，当我们检索到目标元素时，我们就开始向上伸展，通过旋转的方式将目标元素旋转到树根上。但是，我们可以想到，我们从顶部向下检索的过程中，以及从底部向上伸展的过程中，都需要保存许多的父指针来完成，或将路径储存到某个栈中进行保存，这样讲会带来大量的开销！**因此我们更加常用的是另外一个方法——自顶向下伸展。**
(*有兴趣的朋友可以自己尝试用自底向上方法实现，我在这里就不再多讲了~~*)
###自顶向下伸展：
在这里，我们先使用一种叫做标志节点的东西来代替空节点，它的代码如下：

		    typedef struct SplayNode *TreeNode;  
		    TreeNode NullNode; // 储存空标志节点  
		    NullNode = new SplayNode(); // 初始化空标志节点  
		    if (NullNode == NULL)  
			    cout << "标志节点申请失败!" << endl;  
		    NullNode->Element = 0;  
		    NullNode->Left = NullNode->Right = NullNode;   

而我们之所以使用这种空标志节点，有两个原因：**1.此处使用空标志节点而不是NULL，可以极大地简化程序；2.同时避免空指针NULL->Element的使用**；

首先，我们得了解，自顶向下的情况中，我们将在向下检索目标元素的同时就将其余元素分离，__将小的元素放置到左树(LeftTree)，将大的元素放置到右树(RightTree)中__，其中以左树为例，它的链接口叫**LeftTreeMax**，可以直接理解为左树中最大的元素，因为根据二叉树的性质，移动到左树上的元素肯定是已经移动到左树的元素中最大的元素，如果有朋友还不明白，可以自己画一个二叉树，选择一个元素从上到下，将小的链接到左边，大的放在右边，看看是不是这样，这些都是由二叉树的性质所决定的。同理，右树接口为__RightTreeMin__,是大于该元素的最小元素。再将没分离的元素的根作为新的树根，同时更新左右树接口LeftTreeMax以及RightTreeMin的位置，保证其始终指向正确的位置，之后再次进行伸展操作，直到检索到目标元素，或者是空标志节点，最后再将目标元素作为树根，将其与左右树进行连接，就完成了伸展操作了。看着似乎很简单，但却有许多我们需要注意的地方。

完成了这些，我们就可以开始按照情况分析了，当树根元素大于目标元素时有三种情况：  
1.当其左儿子为空标志节点时，结束我们的算法；  
2.当其为Zig-Zag(之字情况)情况或者单旋转情况时，将树根及其右儿子移动到RightTreeMin上，将其左儿子当做新的树根；(图三所示)  
![](http://img.blog.csdn.net/20180224154759280?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzQxNDI3NDAw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
3.当为Zig-Zig(一字情况)情况时，将其旋转成第二中情况再进行操作；(图四所示)
![](http://img.blog.csdn.net/20180224163106642?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzQxNDI3NDAw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

最后，完成分离之后，我们需要进行最后一步——将树根与左右树结合，具体为将左树链接到根的左子树，根原左子树变为左树的LeftTreeMax(因为LeftTreeMax的性质，这样将不会出错)；同理我们可以完成另外一边的操作。图五将为我们展示其具体情况：
![](http://img.blog.csdn.net/20180224162944536?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzQxNDI3NDAw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
*PS：在这里我们可以看出来，所有的旋转操作都是在根部进行的，所有我们不需要再对旋转后的节点与其父节点进行链接，因为它不存在父节点。*

这样所有的情况差不多都分析完成了，剩下的当根节点元素小于目标元素时，只要将左右对调即可，接下来来具体实现代码：  

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

*PS：应当注意的是，我们使用了一个局部变量来储存左树以及右树，这样可以减少开销，但我们必须清楚的时，这样左右树在Header上的位置会相反，Header.Right为左树，Header.Left为右树。*

##3. 查找操作：
只要我们熟练掌握了伸展操作以及其原理，那么查找对我们而言就是很简单的事情了，因为我们是需要对目标元素进行伸展，然后返回树根部的值即可。(可参考图一)
具体实现代码：

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

##4.插入操作： 
插入操作与前面的类似，我们对以插入元素为目标对伸展树进行伸展，再通过比较根节点元素大小，决定插入位置，完成插入操作；不过应当注意特殊情况，即开始时根节点为空标志节点，所以应当单独判断。
具体实现代码：
			
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

##5.删除操作：
删除操作是我们的最后一个操作了，与之前的两个操作相同，我们先进行一次伸展操作，使目标元素移动到根节点，并将根节点删除，重新选取新的根节点；
当然，这时也有两种情况：  
1.当其左子树为空标志节点时，直接将右子树作为新的树根；
2.否则将左子树按照目标元素伸展后将其变为右子树的右儿子，再将右子树作为新的树根；(如图六所示)
![](http://img.blog.csdn.net/20180224165557333?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvd2VpeGluXzQxNDI3NDAw/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
*PS:因为伸展树的特性的关系，若其左子树不为空，我们需要对其左子树进行一次伸展操作，以此便于之后的操作；同时因为伸展操作的特性，我们可以保证伸展后的左子树的右子树为空，这样就不会发生链接错误。*

接下来就是我们的具体代码：

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

#总结
那么我们伸展树的讲解就结束了，如果各位有什么不明白或者我有错误的地方，欢迎大家留言，我也会及时的回复大家的。

最后是CSDN地址:[JZX555的CSDN](http://blog.csdn.net/weixin_41427400/article/details/79360917)

参考文献：《算法导论》，《数据结构与算法分析——C语言描述》