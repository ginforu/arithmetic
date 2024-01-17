//
//  main.c
//  Ch1
//
//  Created by Gin on 2022/4/5.
//

#include <stdio.h>
#include <stdbool.h>


// 寻找第K大的数，二分排除查找，通过排除查找K大的数
// 思路：1、先看k/2 位置AB两个数组元素的大小，可以排除k/2个，此处有2种情况 AB都在范围，AB其一不在范围
int min(int k1, int k2)
{
    if (k1 < k2) {
        return k1;
    }
    return k2;
}
// 寻找第K大的元素，
double GetKValue(int* nums1, int nums1Size, int* nums2, int nums2Size, int k)
{
    int index1 = 0;
    int index2 = 0;
    while (true){
        // 数组1全部遍历完成
        if (index1 == nums1Size) {
            return nums2[index2 + k - 1];
        }
        // 数组2全部遍历完成
        if (index2 == nums2Size) {
            return nums1[index1 + k - 1];
        }
        // 最终K减小到1,取两者之中的小的那个返回
        if (k == 1) {
            return min(nums2[index2 + k - 1], nums1[index1 + k - 1]);
        }

        // 正常逻辑判断
        int mind = k / 2;
        int newIndex1 = min(index1 + mind, nums1Size) - 1;
        int newIndex2 = min(index2 + mind, nums2Size) - 1;
        if (nums1[newIndex1] < nums2[newIndex2]) {
            k -=  (newIndex1 - index1 + 1);
            index1 = newIndex1 + 1;
        } else {
            k -= (newIndex2 - index2 + 1);
            index2 = newIndex2 + 1;
        }
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int num = nums1Size + nums2Size;
    int flag = num & 0x01;
    //判断奇偶性 如果true奇
    if (flag) {
        return GetKValue(nums1, nums1Size, nums2, nums2Size, num / 2 + 1);//奇数情况
    } else {
        return ((double)GetKValue(nums1, nums1Size, nums2, nums2Size, num / 2) +
                (double)GetKValue(nums1, nums1Size, nums2, nums2Size, num / 2 + 1)) / 2;
    }//偶数情况
}

int main() {
    int arr1[]={5,15,18};
    int arr2[]={3,14,21,23};
    double result;
    result=findMedianSortedArrays(arr1, 3, arr2, 3);
    printf("The　result　is　%ld.\n",result);
    return 0;
}

