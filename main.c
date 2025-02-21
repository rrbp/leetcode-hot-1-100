#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


/*
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *ans = (int *) malloc(2 * sizeof(int));
    int A[numsSize];
    for (int i=0; i<numsSize ; i++)
    {
        A[i] = target-nums[i];
    }
    int p1=0, p2=numsSize-1;
    while(p1<numsSize && p2>=0) {
        if (A[p2] < nums[p1]) {
            p2--;
        } else if (A[p2] > nums[p1]) {
            p1++;
        } else {
            *returnSize = 2;
            ans[0] = p1;
            ans[1] = p2;
            return ans;
        }
    }
    return ans;
}
*/

//上述方法有负数情况就会出错
/*
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *ans = (int *) malloc(2 * sizeof(int));
    int *hash = (int *)malloc(20000* sizeof(int));

    for (int i=0; i<20000 ; i++){
        hash[i] = -1;
    }

    for (int i=0;i<numsSize;i++){
        if(hash[(abs(nums[i]+10000))%107]!=-1 ){
            ans[0]=hash[(abs(nums[i]+10000))%107];
            ans[1]=i;
            *returnSize = 2;
            return ans;
        }
        else{
            hash[(abs(target-nums[i]+10000))%107]=i;
        }
    }
    return ans;
}
*/
//上述方法有一个测例不能过

#define HashSize 107 // 哈希表大小

typedef struct Node { // 哈希结点
    int value; // 值
    int index; // 下标
    struct Node* next; // 下指针
}Node;

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int n = numsSize; // 数组长度
    Node* hash[HashSize]; // 哈希表
    for (int i = 0; i < HashSize; i++) { // 初始化哈希表
        hash[i] = (Node*)malloc(sizeof(Node));
        hash[i]->value = hash[i]->index = -1;
        hash[i]->next = NULL;
    }
    for (int i = 0; i < n; i++) { // 遍历一遍原数组
        int pos = abs(target - nums[i]) % HashSize; // 找到 target - nums[i] 在哈希表中对应的位置
        Node* head = hash[pos];
        while (head->next && head->next->value != target - nums[i]) head = head->next; // 找该位置是否有 target - nums[i] 这个值
        if (head->next) { // 找到符合题意的值
            *returnSize = 2;
            int* ans = (int*)malloc(sizeof(int) * 2);
            ans[0] = i; ans[1] = head->next->index; // 写入答案
            for (int i = 0; i < HashSize; i++) free(hash[i]);
            return ans;
        }
        pos = abs(nums[i]) % HashSize; // 找到 nums[i] 在哈希表中对应的位置
        head = hash[pos];
        while (head->next) head = head->next; // 写在这个位置的末尾
        head->next = (Node*)malloc(sizeof(Node));
        head->next->value = nums[i]; // 写入该值
        head->next->index = i; // 写入该值对应的下标
        head->next->next = NULL;
    }
    for (int i = 0; i < HashSize; i++) free(hash[i]);
    *returnSize = 0;
    return NULL;
}
//C语言构建哈希表的方法

//贴一个C++代码，真的简单
/*
 class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> a;//建立hash表存放数组元素
        vector<int> b(2,-1);//存放结果
        for(int i=0;i<nums.size();i++)
            a.insert(map<int,int>::value_type(nums[i],i));
        for(int i=0;i<nums.size();i++)
        {
            if(a.count(target-nums[i])>0&&(a[target-nums[i]]!=i))
            //判断是否找到目标元素且目标元素不能是本身
            {
                b[0]=i;
                b[1]=a[target-nums[i]];
                break;
            }
        }
        return b;
    };
};

 */

int main()
{
    int nums[] = {-1,-2,-3,-4,-5};
    int target = -8;
    int returnSize;
    int *a = twoSum(nums, 5, target, &returnSize);
    printf("%d %d", a[0], a[1]);
    return 0;
}



