
#ifndef __CARD__
#define __CARD__

/**
 * 最大的节点数：即一个分支中能包含的节点的最大个数，相当于M，超过就需要分裂
 */
extern int NODECARD;
extern int LEAFCARD;

/**
 * 平衡节点分割的标准
 */
#define MinNodeFill (NODECARD / 2)	/* 最少借节点数，相当于m，这里设为 M/2 */
#define MinLeafFill (LEAFCARD / 2)  /* 最少借节点数，相当于m，这里设为 M/2 */

/**
 * 下面就是根据level判断是叶子还是非叶子节点，然后返回允许de最大的节点数
 */
#define MAXKIDS(n) ((n)->level > 0 ? NODECARD : LEAFCARD)
#define MINFILL(n) ((n)->level > 0 ? MinNodeFill : MinLeafFill)

#endif
