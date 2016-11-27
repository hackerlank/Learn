#ifndef _INDEX_
#define _INDEX_

#define PGSIZE	512		/* 机器上一个磁盘页的大小 */
#define NUMDIMS	2		/* number of dimensions：维数，这里是二维的矩形 */
#define NDEBUG

typedef float RectReal;	/* 定义矩形的点的类型是float */


/*-----------------------------------------------------------------------------
| 全局定义
-----------------------------------------------------------------------------*/

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define NUMSIDES 2*NUMDIMS		/* 矩形边的数量=4，其实定义的是坐下和右上两个点的坐标 */

/**
 * 下面定义矩形
 */
struct Rect
{
	RectReal boundary[NUMSIDES]; /* 边界：xmin,ymin,...,xmax,ymax,... */
};

struct Node;

/**
 * 下面定义分支
 */
struct Branch
{
	struct Rect rect;			/* 所在的矩形 */
	struct Node *child;			/* 孩子指针 */
};

/**
 * 一个page中能保存的Branch的最大的个数
 */
#define MAXCARD (int)((PGSIZE-(2*sizeof(int))) / sizeof(struct Branch))

/**
 * 下面定义节点
 */
struct Node
{
	int count;						/* 包含的分支的个数 */
	int level;						/* 0 is leaf, others positive */
	struct Branch branch[MAXCARD];	/* 分支数组 */
};

/**
 * 节点链表：辅助作用，在删除的时候
 */
struct ListNode
{
	struct ListNode *next;			/* 下一个节点 */
	struct Node *node;				/* 当前节点 */
};


typedef int (*SearchHitCallback)(int id, void* arg);


extern int RTreeSearch(struct Node*, struct Rect*, SearchHitCallback, void*);
extern int RTreeInsertRect(struct Rect*, int, struct Node**, int depth);
extern int RTreeDeleteRect(struct Rect*, int, struct Node**);
extern struct Node * RTreeNewIndex();
extern struct Node * RTreeNewNode();
extern void RTreeInitNode(struct Node*);
extern void RTreeFreeNode(struct Node *);
extern void RTreePrintNode(struct Node *, int);
extern void RTreeTabIn(int);
extern struct Rect RTreeNodeCover(struct Node *);
extern void RTreeInitRect(struct Rect*);
extern struct Rect RTreeNullRect();
extern RectReal RTreeRectArea(struct Rect*);
extern RectReal RTreeRectSphericalVolume(struct Rect *R);
extern RectReal RTreeRectVolume(struct Rect *R);
extern struct Rect RTreeCombineRect(struct Rect*, struct Rect*);
extern int RTreeOverlap(struct Rect*, struct Rect*);
extern void RTreePrintRect(struct Rect*, int);
extern int RTreeAddBranch(struct Branch *, struct Node *, struct Node **);
extern int RTreePickBranch(struct Rect *, struct Node *);
extern void RTreeDisconnectBranch(struct Node *, int);
extern void RTreeSplitNode(struct Node*, struct Branch*, struct Node**);

extern int RTreeSetNodeMax(int);
extern int RTreeSetLeafMax(int);
extern int RTreeGetNodeMax();
extern int RTreeGetLeafMax();

#endif /* _INDEX_ */
