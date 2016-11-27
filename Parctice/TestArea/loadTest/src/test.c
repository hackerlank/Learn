
#include "index.h"
#include <stdio.h>

/**
 * 下面是4个独立的矩形
 */
struct Rect rects[] = {
	{0, 0, 2, 2},		// xmin, ymin, xmax, ymax (for 2 dimensional RTree)
	{5, 5, 7, 7},
	{8, 5, 9, 6},
	{7, 1, 9, 2},
};

/**
 * 获取矩形的个数
 */
int nrects = sizeof(rects) / sizeof(rects[0]);	

/**
 * 下面是搜索矩形：需要搜索包含在这个矩形中的所有的子集
 */
struct Rect search_rect = {
	{6, 6, 10, 6},
};

/**
 * 自己定义的回调函数
 */
int MySearchCallback(int id, void* arg) 
{
	printf("找到一个合理的矩形，id: %d\n", id-1);
	return 1;
}

/**
 * MAIN 函数
 */
int main()
{
	struct Node* root = RTreeNewIndex();	/* 创建根节点 */
	int i, nhits;
	
	printf("数据矩形的个数 = %d\n", nrects);
	
	for(i=0; i<nrects; i++)
	{
		/**
		 * 分别将所有的子矩形都插入，最终形成R树
		 *
		 * 参数：数据矩形 + 每个矩形分配一个id + root + level初始化都是0 
		 */
		RTreeInsertRect(&rects[i], i+1, &root, 0);
	}

	/**
	 * 下面开始search一个矩形( 当然一个点也行，例如:(1,1,1,1)是一个特殊的矩形 )
	 *
	 * 注意参数：root：注意这是最终的root，上面的建立R树之后的宗的root！
	 *           search_rect：搜索矩形
	 *           MySearchCallback：回调函数
	 *           附加参数 = 0
	 */
	nhits = RTreeSearch(root, &search_rect, MySearchCallback, 0);
	
	printf("找到 %d 个合理的数据矩形！\n", nhits);

	return 0;
}