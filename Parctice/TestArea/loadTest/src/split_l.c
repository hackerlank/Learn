
#include <stdio.h>
#include "assert.h"
#include "index.h"
#include "card.h"
#include "split_l.h"

/**
 * 得到
 * 参数：根 + 分支
 */
static void RTreeGetBranches(struct Node *N, struct Branch *B)
{
	register struct Node *n = N;
	register struct Branch *b = B;
	register int i;

	assert(n);
	assert(b);

	for (i=0; i<MAXKIDS(n); i++)
	{
		assert(n->branch[i].child);		/* 每一个分支必须是有数据的才是合理的！ */
		BranchBuf[i] = n->branch[i];	/* 分支缓冲区 */
	}

	BranchBuf[MAXKIDS(n)] = *b;			/* 最后一个空间给需要新的branch */
	BranchCount = MAXKIDS(n) + 1;		/* 分支数量 = MAXKIDS(n) + 1 */

	/**
	 * 下面其实是计算能够将所有这些矩形包含起来的大的矩形
	 */
	CoverSplit = BranchBuf[0].rect;		/* 初始化一个rect到覆盖矩形中去~ */
	
	for (i=1; i<MAXKIDS(n)+1; i++)		/* 对每一个子矩形进行处理 */
	{
		CoverSplit = RTreeCombineRect(&CoverSplit, &BranchBuf[i].rect);	/* 得到大矩形 */
	}

	RTreeInitNode(n);					/* 将根n重置 */
}

/**
 * 初始化分区的结构体
 *
 * 参数：分区 + rect的个数 + 一个非叶子节点可以拥有的最少的节点数
 */
static void RTreeInitPVars(struct PartitionVars *P, int maxrects, int minfill)
{
	register struct PartitionVars *p = P;
	register int i;
	assert(p);

	p->count[0] = p->count[1] = 0;	/* 出事后两个分区的count都是0 */
	p->total = maxrects;			/* 总的rect的数量 */
	p->minfill = minfill;			/* 每个非叶子节点的可以拥有的最少的节点数 */

	for (i=0; i<maxrects; i++)		/* 对于每个rect来说 */
	{
		p->taken[i] = FALSE;		/* 初始化都没有被分配到哪一个分区 */
		p->partition[i] = -1;		/* 自然属于自己的分区也是没有哦！id就是-1 */
	}
}

/**
 * 将一个rect加入到group这个id的分区中去
 *
 * 参数：rect在BranchBuf中的位置 + 分区id(0或者1) + 分区结构
 */
static void RTreeClassify(int i, int group, struct PartitionVars *p)
{
	assert(p);
	assert(!p->taken[i]);

	p->partition[i] = group;				/* 加入的组id */
	p->taken[i] = TRUE;						/* 说明被分配了 */

	if (p->count[group] == 0)				/* 如果是第一个矩形：那么不需要大矩形包含处理 */
		p->cover[group] = BranchBuf[i].rect;/* 加入 */
	else									/* 1号分区 */
		p->cover[group] = RTreeCombineRect(&BranchBuf[i].rect,
					&p->cover[group]);		/* 大矩形包含处理 */

	p->area[group] = RTreeRectSphericalVolume(&p->cover[group]);	/* 计算当前矩形的外接球体积 */
	p->count[group]++;						/* count++ */
}

/**
 * 从整个几何中分别找到两个rect作为两个分区的第一个矩形
 *
 * 基本原则：这两个矩形是重叠最少||距离最远的
 * 
 * 其实算法很easy：就是找到左下角最大的rect 和 右上角最小的rect，那么这两个矩形之间的矩形是最大的!
 * 自己画图看看！
 */
static void RTreePickSeeds(struct PartitionVars *P)
{
	register struct PartitionVars *p = P;			/* 分区 */
	register int i, dim, high;
	register struct Rect *r, *rlow, *rhigh;
	register float w, separation, bestSep;
	RectReal width[NUMDIMS];
	int leastUpper[NUMDIMS], greatestLower[NUMDIMS];
	int seed0, seed1;
	assert(p);
	
	/**
	 * greatestLower : 保存左下角那个点最大的x或者y的值的rect在BranchBuf中的位置idx
	 * leastUpper	 : 保存右上角那个点最小的x或者y的值的rect在BranchBuf中的位置idx
	 *
	 * 因为要处理两次，那么x和y都被处理到
	 */
	
	for (dim=0; dim<NUMDIMS; dim++)
	{
		high = dim + NUMDIMS;

		/* find the rectangles farthest out in each direction
		 * along this dimens */
		
		greatestLower[dim] = leastUpper[dim] = 0;
		
		/**
		 * 下面对于所有的rect进行处理
		 * 
		 * 先对x进行处理！再对y进行处理！
		 */
		for (i=1; i<NODECARD+1; i++)
		{
			r = &BranchBuf[i].rect;	/* 取一个矩形 */

			if (r->boundary[dim] >	/* 得到一个更大的值 */
			    BranchBuf[greatestLower[dim]].rect.boundary[dim])
			{
				greatestLower[dim] = i;
			}

			if (r->boundary[high] <	/* 得到一个最小的值 */
			    BranchBuf[leastUpper[dim]].rect.boundary[high])
			{
				leastUpper[dim] = i;
			}
		}

		/* find width of the whole collection along this dimension */
		/**
		 * 获得那个大大矩形的x宽度和y宽度( 范围 )
		 */
		width[dim] = CoverSplit.boundary[high] -
			     CoverSplit.boundary[dim];
	}
	
	/**
	 * 下面需要找到最好的这样的两个初始化的矩形
	 */
	for (dim=0; dim<NUMDIMS; dim++)
	{
		high = dim + NUMDIMS;

		assert(width[dim] >= 0);
		
		/**
		 * 获得x // y的宽度
		 */
		if (width[dim] == 0)	
			w = (RectReal)1;
		else
			w = width[dim];
		
		rlow = &BranchBuf[leastUpper[dim]].rect;		/* 右上角x // y最小的rect */
		rhigh = &BranchBuf[greatestLower[dim]].rect;	/* 左下角x // y最大的rect */

		if (dim == 0)									/* 对于x */
		{
			seed0 = leastUpper[0];						/* 第一个矩形 */
			seed1 = greatestLower[0];					/* 第二个矩形 */
			
			separation = bestSep =						/* 获得分离距离 */
				(rhigh->boundary[0] -
				 rlow->boundary[NUMDIMS]) / w;
		}	
		else											/* 对于y */
		{
			separation =								/* 获得分离距离 */
				(rhigh->boundary[dim] -
				rlow->boundary[dim+NUMDIMS]) / w;

			if (separation > bestSep)					/* 分离距离更小大，那么更好！ */
			{
				seed0 = leastUpper[dim];
				seed1 = greatestLower[dim];
				bestSep = separation;
			}
		}
	}

	if (seed0 != seed1)					/* 两个矩形不是同一个rect才OK！ */
	{	
		RTreeClassify(seed0, 0, p);		/* 分区0：第一个矩形seed0 */
		RTreeClassify(seed1, 1, p);		/* 分区1：第一个矩形seed1 */
	}
}

/**
 * 将没有加入分区的rects加入分区，每次处理一个rect
 *
 * 规则：如果是平局，那么进入下一个测试！
 *
 * 1)：如果一个组已经达到maxnum(指的是至少另一个分组要放足minfill个！)了，那么将r放到另一个中
 * 2)：将r放到，使得扩张空间最小的那个组中
 * 3)：如果2)有平手，那么放到整体空间更小的组中^_^
 * 4)：将r放到元素少的组中
 * 5)：任意放~
 */
static void RTreePigeonhole(struct PartitionVars *P)
{
	register struct PartitionVars *p = P;
	struct Rect newCover[2];
	register int i, group;
	RectReal newArea[2], increase[2];
	
	/**
	 * 下面根据上面的规则进行处理每一个rect
	 */
	for (i=0; i<NODECARD+1; i++)
	{
		/**
		 * 如果还没有放到分组中去
		 */
		if (!p->taken[i])
		{
			/**
			 * 规则一：
			 * 如果一个分组放满了，那么放到另一个分组中去
			 */
			if (p->count[0] >= p->total - p->minfill)	/* 另一个分组至少放minfill个 */
			{
				RTreeClassify(i, 1, p);					/* 0号满了，放到1号中 */
				continue;
			}
			else if (p->count[1] >= p->total - p->minfill)
			{
				RTreeClassify(i, 0, p);					/* 1号满了，放到0号中 */
				continue;
			}
				
			/**
			 * 规则二：
			 *  获得扩展更小的那个分区
			 */

			/* 先预将rect放到两个分区中，获得分别增加的空间的大小！ */
			for (group=0; group<2; group++)
			{
				if (p->count[group]>0)								/* 不是第一个rect */
					newCover[group] = RTreeCombineRect(
						&BranchBuf[i].rect,
						&p->cover[group]);	
				else												/* 是第一个rect */
					newCover[group] = BranchBuf[i].rect;

				newArea[group] = RTreeRectSphericalVolume(			/* 获得新的矩形的外接球体积 */
							&newCover[group]);

				increase[group] = newArea[group]-p->area[group];	/* 增量 */
			}

			/* 下面进行比较：获得更小的扩展的一个 */
			if (increase[0] < increase[1])
				RTreeClassify(i, 0, p);
			else if (increase[1] < increase[0])
				RTreeClassify(i, 1, p);
			
			/**
			 * 规则三：
			 * 如果上面的增量相等，那么将元素放到面积小的矩形中
			 */
			else if (p->area[0] < p->area[1])
				RTreeClassify(i, 0, p);
			else if (p->area[1] < p->area[0])
				RTreeClassify(i, 1, p);

			/**
			 * 规则四：
			 * 上面的也相等，那么放到元素比较少的分区中
			 */
			else if (p->count[0] < p->count[1])
				RTreeClassify(i, 0, p);
			else
				RTreeClassify(i, 1, p);
		}
	}

	assert(p->count[0] + p->count[1] == NODECARD + 1);
}

/**
 * 发现分区:分区就是将这个大的rect分裂成两个新的大的rect( 即：两个分区 )
 * 参数：分区p + 最少的拥有节点数
 */
static void RTreeMethodZero(struct PartitionVars *p, int minfill)
{
	RTreeInitPVars(p, BranchCount, minfill);	/* 初始化；两个分区结构 */
	RTreePickSeeds(p);							/* 分别找到两个分区的最初的一个rect，并加入 */
	RTreePigeonhole(p);							/* 将所有的rect都加入分区 */
}

/**
 * 将buf中的两个分区拷贝到两个分支上去
 *
 * 参数：N：第一个新的节点
 *       Q：第二个新的节点  ( 两个节点是由原始的N分裂得到 )
 *       P：分区信息
 */
static void RTreeLoadNodes(struct Node *N, struct Node *Q,
			struct PartitionVars *P)
{
	register struct Node *n = N, *q = Q;
	register struct PartitionVars *p = P;
	register int i;
	assert(n);
	assert(q);
	assert(p);

	/**
	 * 扫描所有的点，然后加入自己的branch
	 */
	for (i=0; i<NODECARD+1; i++)
	{	
		if (p->partition[i] == 0)					/* 第一个新的节点(分区) */
			RTreeAddBranch(&BranchBuf[i], n, NULL);
		else if (p->partition[i] == 1)				/* 第二个新的节点(分区) */
			RTreeAddBranch(&BranchBuf[i], q, NULL);
		else
			assert(FALSE);
	}
}

/**
 * 分裂一个节点！
 * 
 * 一个节点变成两个节点！
 * 
 * 参数：根 + 分支 + 新的节点
 */
void RTreeSplitNode(struct Node *n, struct Branch *b, struct Node **nn)
{
	register struct PartitionVars *p;
	register int level;
	RectReal area;

	assert(n);
	assert(b);

	/**
	 * 将n的所有的分支节点和新的分支都放到BranchBuf中，
	 * 并且将n重置！
	 */
	level = n->level;
	RTreeGetBranches(n, b);		/* 参数：根 + 分支 */
	
	/* 找到分区 */
	p = &Partitions[0];

	/**
	 * 下面将所有的矩形都加入两个分区
	 * 
	 * 注意参数：分区 + 能够拥有的节点的数量
	 */
	RTreeMethodZero(p, level>0 ? MinNodeFill : MinLeafFill);
	
	/**
	 * 获得两个分区的面积之和
	 */
	area = p->area[0] + p->area[1];
	
	/* put branches from buffer in 2 nodes according to chosen partition */

	/**
	 * 下面创建一个新的节点
	 */
	*nn = RTreeNewNode();				/* 新的节点 */
	(*nn)->level = n->level = level;
	RTreeLoadNodes(n, *nn, p);			/* 参数：原始的根节点 + 新的节点( 这个两个节点是原来的n分裂得到的哦 ) */
										/*       p：分区信息 */	
	assert(n->count + (*nn)->count == NODECARD+1);
}



/*-----------------------------------------------------------------------------
| Print out data for a partition from PartitionVars struct.
-----------------------------------------------------------------------------*/
static void RTreePrintPVars(struct PartitionVars *p)
{
	int i;
	assert(p);

	printf("\npartition:\n");
	for (i=0; i<NODECARD+1; i++)
	{
		printf("%3d\t", i);
	}
	printf("\n");
	for (i=0; i<NODECARD+1; i++)
	{
		if (p->taken[i])
			printf("  t\t");
		else
			printf("\t");
	}
	printf("\n");
	for (i=0; i<NODECARD+1; i++)
	{
		printf("%3d\t", p->partition[i]);
	}
	printf("\n");

	printf("count[0] = %d  area = %f\n", p->count[0], p->area[0]);
	printf("count[1] = %d  area = %f\n", p->count[1], p->area[1]);
	printf("total area = %f  effectiveness = %3.2f\n",
		p->area[0] + p->area[1],
		RTreeRectSphericalVolume(&CoverSplit)/(p->area[0]+p->area[1]));

	printf("cover[0]:\n");
	RTreePrintRect(&p->cover[0], 0);

	printf("cover[1]:\n");
	RTreePrintRect(&p->cover[1], 0);
}
