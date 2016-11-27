

#define METHODS 1

struct Branch BranchBuf[MAXCARD+1];		/* 分支的缓冲区 */
int BranchCount;						/* 保存BranchBuf中的分支数量 */
struct Rect CoverSplit;					/* 将所有的子矩形都装进去的那个大大矩形 */

/**
 * 为了当一个节点进行分裂的时候处理使用的tmp
 */
struct PartitionVars
{
	int partition[MAXCARD+1];	/* 表示第i个节点(rect)所在的那个分区的id */
	int total, minfill;			/* 总的rect数量 + 每个非叶节点可以拥有的子节点的最少个数 */
	int taken[MAXCARD+1];		/* 表示第i个节点(rect)是否被已经被分配了 */
	int count[2];				/* 代表两个分区当前拥有的rect的数量 */
	struct Rect cover[2];		/* 当前已经加入的子矩形们的大的包含矩形，为了更大的包含！ */
	RectReal area[2];			/*  */
} Partitions[METHODS];
