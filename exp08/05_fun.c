#include <stdio.h>

#define M 3
#define N 4

struct abc {
    int a;
    int b;
    int c;
};

void fun1_1(int array[][4], int m, int n) { // 形参声明为二维数组
    printf("the address is %p\n", array);
    int max = array[0][0];
	for (int i = 0; i < m; i ++) {
		for (int j = 0; j < n; j ++) {
			if (max < array[i][j]) 
                max = array[i][j]; 
		}
	}
	printf("max in array is %d\n", max);
}
void fun1_2(int *array, int m, int n) {     // 形参声明为一级指针
    printf("the address is %p\n", array);
    int max = array[0];
	for (int i = 0; i < m * n; i++) {
		if(max < array[i]) 
            max = array[i];
	}
    printf("max in array is %d\n", max);
}
void fun1_3(int **array, int m, int n) {    // 形参声明为二级指针
    printf("the address is %p\n", array);
    int max = array[0][0];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if(max < array[i][j]) 
                max = array[i][j];
		}
	}
    printf("max in array is %d\n", max);
}

void fun2(struct abc myabc) {
    printf("the address is %p\n", &myabc);
}

void fun3(struct abc *myabc) {
    printf("the address is %p\n", myabc);
}

int main()
{
    int a[M][N] = {{1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}};
    struct abc myabc;

    int *p1 = a[0]; // 定义指针用于储存二维数组第一行的首地址，也就是把二维数组当作一维数组
    int *p2[M];     // 定义指针数组用于储存二维数组每行的首地址
    p2[0] = &a[0][0];
    p2[1] = &a[1][0];
    p2[2] = &a[2][0];
    
    fun1_1(a, M, N);
    fun1_2(p1, M, N);
    fun1_3(p2, M, N);
    fun2(myabc);
    fun3(&myabc);


    return 0;
}