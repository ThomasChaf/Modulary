#ifndef __UTILS_H__
#define __UTILS_H__

#define true 1
#define false 0

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)
#define INT(x) (x == NULL ? 0 : atoi(x))
#define RAND(min, max) (rand() % (max - min) + min)

#endif /* __UTILS_H__ */
