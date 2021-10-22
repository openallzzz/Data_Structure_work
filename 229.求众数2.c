/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* majorityElement(int* nums, int numsSize, int* returnSize) {
    int* retArr = (int*)malloc(sizeof(int) * 2);
    *returnSize = 0;

    if (numsSize == 1) {
        retArr[0] = nums[0];
        *returnSize = 1;
        return retArr;
    }

    int num1 = nums[0], cnt_1 = 0;
    int num2 = nums[1], cnt_2 = 0;

    for (int i = 0; i < numsSize; i++) {
        if (num1 == nums[i]) {
            cnt_1++;
        }
        else if (num2 == nums[i]) {
            cnt_2++;
        }
        else if (cnt_1 == 0) {
            num1 = nums[i];
            cnt_1++;
        }
        else if (cnt_2 == 0) {
            num2 = nums[i];
            cnt_2++;
        }
        else {
            cnt_1--;
            cnt_2--;
        }
    }

    cnt_1 = 0;
    cnt_2 = 0;
    if (num1 == num2) {
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] == num1) {
                cnt_1++;
            }
        }
        if (cnt_1 > numsSize / 3) {
            retArr[0] = num1;
            *returnSize = 1;
            return retArr;
        }
        else {
            return retArr;
        }
    }
    else {
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] == num1) {
                cnt_1++;
            }
            else if (nums[i] == num2) {
                cnt_2++;
            }
        }

        if (cnt_1 > numsSize / 3 && cnt_2 > numsSize / 3) {
            retArr[0] = num1;
            retArr[1] = num2;
            *returnSize = 2;
            return retArr;
        }
        if (cnt_1 <= numsSize / 3 && cnt_2 > numsSize / 3) {
            retArr[0] = num2;
            *returnSize = 1;
            return retArr;
        }
        if (cnt_1 <= numsSize / 3 && cnt_2 <= numsSize / 3) {
            return retArr;
        }
        if (cnt_1 > numsSize / 3 && cnt_2 <= numsSize / 3) {
            retArr[0] = num1;
            *returnSize = 1;
            return retArr;
        }
    }

    return NULL;
}