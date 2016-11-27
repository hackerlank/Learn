
#include <stdio.h>
#include <malloc.h>
#include "assert.h"
#include "index.h"
#include "card.h"


/**
 * 创建一个只有一个节点的新的索引
 */
struct Node * RTreeNewIndex()
{
	struct Node *x;			/* 一个节点 */
	x = RTreeNewNode();		/* 创建这个Node */
	x->level = 0;			/* 因为只有一个节点，那么就是叶子，那么level=0 */
	return x;				/* 返回这个新的索引节点 */
}

/**
 * 搜索目标矩形所在位置(或者说涉及到哪些数据矩形吧)
 *
 * 参数：根节点 + 目标矩形 + 回调函数 + 附加参数
 *
 * 返回找到的数据矩形的个数
 */
int RTreeSearch(struct Node *N, struct Rect *R, SearchHitCallback shcb, void* cbarg)
{
	register struct Node *n = N;
	register struct Rect *r = R;
	register int hitCount = 0;
	register int i;
	
	assert(n);
	assert(n->level >= 0);
	assert(r);

	/**
	 * 根n是一个真正的根
	 */
	if (n->level > 0)
	{
		/**
		 * 对所有的节点进行遍历
		 */
		for (i=0; i<NODECARD; i++)
			if (n->branch[i].child &&				/* 判断这个子矩形存在 && 重叠了 ==> 找到一个合理的"大矩形" */
			    RTreeOverlap(r,&n->branch[i].rect))	/* 判断两个矩形是否重叠
				                                     * 参数：搜索矩形 + 根的一个分支矩形 
													 */
			{
				/**
				 * 下面继续进行递归判断：直到找到的是数据矩形
				 */
				hitCount += RTreeSearch(n->branch[i].child, R, shcb, cbarg);
			}
	}
	/**
	 * 根n是一个叶子节点( 即是数据矩形了：是我们需要的最终的结果！ )
	 */
	else
	{
		for (i=0; i<LEAFCARD; i++)
			if (n->branch[i].child &&				/* 如果存在 && 重叠了 ==> 找到一个合理的"数据矩形" */
			    RTreeOverlap(r,&n->branch[i].rect))
			{
				hitCount++;							/* count++ */
			
				/**
				 * 下面我们是否自己创建了自己的回调函数
				 */
				if(shcb)
					if( ! shcb((int)n->branch[i].child, cbarg))	/* 先处理这个回调函数 */
						return hitCount;
			}
	}
	
	return hitCount;
}

/**
 * 实际执行：插入一个数据矩形到索引结构中
 * 是一个递归下降树
 * 返回1代表root分裂了，0代表没有分裂
 * 注意参数：数据矩形；数据矩形的id；树根；新的节点；层级
 */
static int RTreeInsertRect2(struct Rect *r,
		int tid, struct Node *n, struct Node **new_node, int level)
{
	register int i;
	struct Branch b;
	struct Node *n2;

	assert(r && n && new_node);
	assert(level >= 0 && level <= n->level);

	/**
	 * 注意参数传进来之后n就是树根
	 */
	
	/**
	 * 没有达到自己的层级，就处理( 是一个递归下降树 )
	 */
	if (n->level > level)
	{
		i = RTreePickBranch(r, n);	/* 找到一个能够容纳自己的且增加体积最少的那个rect。
		                             * 参数：数据矩形和根 
		                             */
		
		/**
		 * 下面进行递归处理子矩形
		 * 只有当那个所谓的根(n->branch[i].child)没有分支的时候，
		 * 那么说明是数据矩形，那么是最终的归宿
		 */
		if (!RTreeInsertRect2(r, tid, n->branch[i].child, &n2, level))
		{
			// 孩子没有分裂！
			//
			n->branch[i].rect =
				RTreeCombineRect(r,&(n->branch[i].rect));	/* 将两个矩形合并 */
			return 0;
		}
		else// 孩子分裂了！
		{
			n->branch[i].rect = RTreeNodeCover(n->branch[i].child);
			b.child = n2;
			b.rect = RTreeNodeCover(n2);
			return RTreeAddBranch(&b, n, new_node);
		}
	}
	else if (n->level == level)			/* 达到了可以插入的层级，就插入，注意必要的时候进行分裂！ */
	{
		b.rect = *r;					/* 创建一个新的分支：矩形就是新的数据矩形 */
		b.child = (struct Node *) tid;	/* 所谓的B的孩子，其实是自己的id */
		/* child field of leaves contains tid of data record */
		return RTreeAddBranch(&b, n, new_node);	/* 返回 */
	}
	else
	{
		assert (FALSE);	/* 这一步是不可能能通过的！ */
		return 0;
	}
}

/**
 * 插入一个矩形到索引结构中
 *
 * 注意插入中主要就是为了判断是否需要分裂节点
 *
 * 注意返回值：1代表根分裂了，0代表没有分裂
 *
 * level：0代表叶子，其他代表非叶子节点
 *
 * 具体的在RTreeInsertRect2中递归处理
 */
int RTreeInsertRect(struct Rect *R, int Tid, struct Node **Root, int Level)
{
	register struct Rect *r = R;				/* 插入矩形r */
	register int tid = Tid;						/* 代表这个数据矩形的id */
	register struct Node **root = Root;			/* 树根 */
	register int level = Level;					/* 数据矩形所在的level，一般数据矩形都是0：叶子 */

	register int i;
	register struct Node *newroot;				/* 可能的新的root：分裂导致 */
	struct Node *newnode;						/* 新的节点 */
	struct Branch b;							/* 分支 */
	int result;									/* 返回结果：1代表根分裂了，0代表没有分裂 */

	/**
	 * 检查合法性
	 */
	assert(r && root);
	assert(level >= 0 && level <= (*root)->level);
	for (i=0; i<NUMDIMS; i++)
	{
		assert(r->boundary[i] <= r->boundary[NUMDIMS+i]);	/* 坐标不合理 */
	}

	/**
	 * 下面使用RTreeInsertRect2进行插入这个矩形，并判断是否分裂
	 *
	 * 如果分裂了，那么
	 *
	 * 注意参数：数据矩形；数据矩形的id；树根；新的节点；层级
	 */
	if (RTreeInsertRect2(r, tid, *root, &newnode, level))  /* 
		                                                    * 如果根分裂了，注意同时一个新的分支
															* newnode返回，还有一个分支就是之前的
															* root，所以不需要返回，只是数据变化了而已
															*/
	{
		newroot = RTreeNewNode();			/* 这两个新的节点root和newnode需要被一个新的newroot管理 */
		newroot->level = (*root)->level + 1;/* 层次高一级咯！ */
		
		/**
		 * 处理分支一
		 */
		b.rect = RTreeNodeCover(*root);		/* b.rect是包含root中所有小矩形的大矩形 */	
		b.child = *root;					/* b的孩子就是root */
		RTreeAddBranch(&b, newroot, NULL);	/* 然后在newroot上面增加一个新的分支b(也就是之前的root) */
		
		b.rect = RTreeNodeCover(newnode);	/* 然后b的rect赋值为第二个分裂的新的节点 
											 * b.rect是包含newnode中所有小矩形的大矩形
		                                     */
		/**
		 * 处理分支二
		 */
		b.child = newnode;					/* b的孩子就是node */
		RTreeAddBranch(&b, newroot, NULL);	/* 然后在newroot上面增加一个新的分支newnode */

		/**
		 * 注意root指针需要替换了哦~~~ ^_^
		 */
		*root = newroot;
		result = 1;							/* 返回1代表节点分裂了 */
	}
	else
	{
		result = 0;
	}

	return result;
}




// Allocate space for a node in the list used in DeletRect to
// store Nodes that are too empty.
//
static struct ListNode * RTreeNewListNode()
{
	return (struct ListNode *) malloc(sizeof(struct ListNode));
	//return new ListNode;
}


static void RTreeFreeListNode(struct ListNode *p)
{
	free(p);
	//delete(p);
}



// Add a node to the reinsertion list.  All its branches will later
// be reinserted into the index structure.
//
static void RTreeReInsert(struct Node *n, struct ListNode **ee)
{
	register struct ListNode *l;

	l = RTreeNewListNode();
	l->node = n;
	l->next = *ee;
	*ee = l;
}


// Delete a rectangle from non-root part of an index structure.
// Called by RTreeDeleteRect.  Descends tree recursively,
// merges branches on the way back up.
// Returns 1 if record not found, 0 if success.
//
static int
RTreeDeleteRect2(struct Rect *R, int Tid, struct Node *N, struct ListNode **Ee)
{
	register struct Rect *r = R;
	register int tid = Tid;
	register struct Node *n = N;
	register struct ListNode **ee = Ee;
	register int i;

	assert(r && n && ee);
	assert(tid >= 0);
	assert(n->level >= 0);

	if (n->level > 0)  // not a leaf node
	{
	    for (i = 0; i < NODECARD; i++)
	    {
		if (n->branch[i].child && RTreeOverlap(r, &(n->branch[i].rect)))
		{
			if (!RTreeDeleteRect2(r, tid, n->branch[i].child, ee))
			{
				if (n->branch[i].child->count >= MinNodeFill)
					n->branch[i].rect = RTreeNodeCover(
						n->branch[i].child);
				else
				{
					// not enough entries in child,
					// eliminate child node
					//
					RTreeReInsert(n->branch[i].child, ee);
					RTreeDisconnectBranch(n, i);
				}
				return 0;
			}
		}
	    }
	    return 1;
	}
	else  // a leaf node
	{
		for (i = 0; i < LEAFCARD; i++)
		{
			if (n->branch[i].child &&
			    n->branch[i].child == (struct Node *) tid)
			{
				RTreeDisconnectBranch(n, i);
				return 0;
			}
		}
		return 1;
	}
}



// Delete a data rectangle from an index structure.
// Pass in a pointer to a Rect, the tid of the record, ptr to ptr to root node.
// Returns 1 if record not found, 0 if success.
// RTreeDeleteRect provides for eliminating the root.
//
int RTreeDeleteRect(struct Rect *R, int Tid, struct Node**Nn)
{
	register struct Rect *r = R;
	register int tid = Tid;
	register struct Node **nn = Nn;
	register int i;
	register struct Node *tmp_nptr;
	struct ListNode *reInsertList = NULL;
	register struct ListNode *e;

	assert(r && nn);
	assert(*nn);
	assert(tid >= 0);

	if (!RTreeDeleteRect2(r, tid, *nn, &reInsertList))
	{
		/* found and deleted a data item */

		/* reinsert any branches from eliminated nodes */
		while (reInsertList)
		{
			tmp_nptr = reInsertList->node;
			for (i = 0; i < MAXKIDS(tmp_nptr); i++)
			{
				if (tmp_nptr->branch[i].child)
				{
					RTreeInsertRect(
						&(tmp_nptr->branch[i].rect),
						(int)tmp_nptr->branch[i].child,
						nn,
						tmp_nptr->level);
				}
			}
			e = reInsertList;
			reInsertList = reInsertList->next;
			RTreeFreeNode(e->node);
			RTreeFreeListNode(e);
		}
		
		/* check for redundant root (not leaf, 1 child) and eliminate
		*/
		if ((*nn)->count == 1 && (*nn)->level > 0)
		{
			for (i = 0; i < NODECARD; i++)
			{
				tmp_nptr = (*nn)->branch[i].child;
				if(tmp_nptr)
					break;
			}
			assert(tmp_nptr);
			RTreeFreeNode(*nn);
			*nn = tmp_nptr;
		}
		return 0;
	}
	else
	{
		return 1;
	}
}
