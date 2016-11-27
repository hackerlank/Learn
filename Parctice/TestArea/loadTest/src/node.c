
#include <stdio.h>
#include <malloc.h>
#include "assert.h"
#include "index.h"
#include "card.h"


/**
 * 初始化一个节点的所有的分支
 */
static void RTreeInitBranch(struct Branch *b)
{
	RTreeInitRect(&(b->rect));				/* 实际就是初始化这个矩形 */
	b->child = NULL;						/* 没有孩子 */
}


/**
 * 初始化这样一个节点
 */
void RTreeInitNode(struct Node *N)
{
	register struct Node *n = N;
	register int i;
	n->count = 0;							/* 分支数=0 */
	n->level = -1;							
	for (i = 0; i < MAXCARD; i++)			/* 下面初始化每一个分支 */
	{
		RTreeInitBranch(&(n->branch[i]));	/* 初始化 */
	}
}



/**
 * 创建一个新的节点，并初始化所有分支为空
 */
struct Node * RTreeNewNode()
{
	register struct Node *n;

	//n = new Node;
	n = (struct Node*)malloc(sizeof(struct Node));	/* 分配空间 */
	assert(n);										/* 检查 */
	RTreeInitNode(n);								/* 初始化R树的节点 */
	return n;
}

/**
 * 释放一个节点
 */
void RTreeFreeNode(struct Node *p)
{
	assert(p);
	//delete p;
	free(p);										/* just free */
}



static void RTreePrintBranch(struct Branch *b, int depth)
{
	RTreePrintRect(&(b->rect), depth);
	RTreePrintNode(b->child, depth);
}


extern void RTreeTabIn(int depth)
{
	int i;
	for(i=0; i<depth; i++)
		putchar('\t');
}


// Print out the data in a node.
//
void RTreePrintNode(struct Node *n, int depth)
{
	int i;
	assert(n);

	RTreeTabIn(depth);
	printf("node");
	if (n->level == 0)
		printf(" LEAF");
	else if (n->level > 0)
		printf(" NONLEAF");
	else
		printf(" TYPE=?");
	printf("  level=%d  count=%d  address=%o\n", n->level, n->count, n);

	for (i=0; i<n->count; i++)
	{
		if(n->level == 0) {
			// RTreeTabIn(depth);
			// printf("\t%d: data = %d\n", i, n->branch[i].child);
		}
		else {
			RTreeTabIn(depth);
			printf("branch %d\n", i);
			RTreePrintBranch(&n->branch[i], depth+1);
		}
	}
}

/**
 * 返回包含所有的矩形的大矩形
 */
struct Rect RTreeNodeCover(struct Node *N)
{
	register struct Node *n = N;
	register int i, first_time=1;
	struct Rect r;
	assert(n);

	RTreeInitRect(&r);					/* 初始化矩形r */

	/**
	 * 下面对所有的分支进行处理
	 */
	for (i = 0; i < MAXKIDS(n); i++)
		if (n->branch[i].child)			/* 如果分支上是有孩子的 */
		{
			if (first_time)				/* 第一次对r处理 */
			{
				r = n->branch[i].rect;	/* r等于第一个分支的rect */
				first_time = 0;
			}
			else
				r = RTreeCombineRect(&r, &(n->branch[i].rect));	/* 获得能够包含所有的矩形的大矩形 */
		}
	return r;
}



/**
 * 选择一个需要增加最少面积的分支来装入这个数据矩形( 尽量少的面积最好 )
 * 如果搜索到有两个一样的增加面子的分支，那么，选择之前更小的那个
 *
 * 注意参数：数据矩形 + 根
 */
int RTreePickBranch(struct Rect *R, struct Node *N)
{
	register struct Rect *r = R;	/* 数据矩形 */
	register struct Node *n = N;	/* 根 */
	register struct Rect *rr;
	register int i, first_time=1;
	RectReal increase, bestIncr = (RectReal)-1, area, bestArea;
	int best;
	struct Rect tmp_rect;
	assert(r && n);
	
	/**
	 * 对于n的每一个分支处理
	 * 要时刻注意我们的目的是什么：找到一个尽量小的合法的矩形
	 *
	 */
	for (i=0; i<MAXKIDS(n); i++)
	{
		if (n->branch[i].child)					/* 如果一个分支有孩子存在 */
		{	
			rr = &n->branch[i].rect;			/* 获得分支的矩形 */
			
			area = RTreeRectSphericalVolume(rr);/* 得到外接球体积 */

			tmp_rect = RTreeCombineRect(r, rr);	/* 创建一个新的矩形能够包住这个两个给定的矩形
			                                     * 注意参数：数据rect + 分支rect 
			                                     */

			increase = RTreeRectSphericalVolume(&tmp_rect) - area;	/* 两个矩形结合之后，形成一个
																	 * 大的矩形。那么在外接球体积上
																	 * 增大了多少呢？
																	 * 我们最终需要增大的最少的那种情况！
			                                                         */
			/**
			 * 下面就是筛选出增加面积最小的那个( first_time是一个特殊情况 )
			 */
			if (increase < bestIncr || first_time)
			{
				best = i;
				bestArea = area;
				bestIncr = increase;
				first_time = 0;
			}
			else if (increase == bestIncr && area < bestArea)	/* 如果相等，那么选择体积小的，为了保证最小的消耗^_^ */
			{
				best = i;
				bestArea = area;
				bestIncr = increase;
			}
		}
	}

	return best;
}



/**
 * 增加一个分支到节点上去( 如果需要的话就要分裂这个节点 )
 * 参数：
 *     新的分支B，这个分支的根节点N，新的节点New_node
 *
 * 返回0：没有分裂( 老的节点被更新 )
 * 返回1：分裂了  ( new_node被创建 ) 分成两个节点
 */
int RTreeAddBranch(struct Branch *B, struct Node *N, struct Node **New_node)
{
	register struct Branch *b = B;
	register struct Node *n = N;
	register struct Node **new_node = New_node;
	register int i;
	
	assert(b);
	assert(n);
	
	if (n->count < MAXKIDS(n))				/* 还没有必要分裂！ */
	{
		for (i = 0; i < MAXKIDS(n); i++)	/* 需要找到一个空的分支 */
		{
			if (n->branch[i].child == NULL)	/* 存在它的孩子为NULL:就是叶子节点 */
			{
				n->branch[i] = *b;			/* 分支赋值 */
				n->count++;					/* n的分支又多一个 */
				break;
			}
		}
		return 0;
	}
	else
	{
		assert(new_node);
		RTreeSplitNode(n, b, new_node);		/* 需要进行分裂！ 
											 * 参数：根，分支，新的节点
											 * 注意最终返回了一个新的node( 还有一个分支就是之前的n )
		                                     */
		return 1;
	}
}



// Disconnect a dependent node.
//
void RTreeDisconnectBranch(struct Node *n, int i)
{
	assert(n && i>=0 && i<MAXKIDS(n));
	assert(n->branch[i].child);

	RTreeInitBranch(&(n->branch[i]));
	n->count--;
}
