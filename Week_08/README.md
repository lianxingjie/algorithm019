# 位运算

## 指定位置的位运算
1. 将x 最右边的n 位清零：x& (~0 << n)
2. 获取x 的第n 位值（0 或者1）：(x >> n) & 1
3. 获取x 的第n 位的幂值：x& (1 << n)
4. 仅将第n 位置为1：x | (1 << n)
5. 仅将第n 位置为0：x & (~ (1 << n))
6. 将x 最高位至第n 位（含）清零：x& ((1 << n) -1)

## N 皇后位运算代码模板
```C++
class Solution {
public:
    int totalNQueens(int n) {
        dfs(n, 0, 0, 0, 0);
        
        return this->res;
    }
    
    void dfs(int n, int row, int col, int ld, int rd) {
        if (row >= n) { res++; return; }
        
        // 将所有能放置 Q 的位置由 0 变成 1，以便进行后续的位遍历
        int bits = ~(col | ld | rd) & ((1 << n) - 1);
        while (bits > 0) {
            int pick = bits & -bits; // 注: x & -x
            dfs(n, row + 1, col | pick, (ld | pick) << 1, (rd | pick) >> 1);
            bits &= bits - 1; // 注: x & (x - 1)
        }
    }


private:
    int res = 0;
};
```
## 位1的个数
```C++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n != 0)
        {
            if(n & 1) count ++;
            n >>= 1;
        }
        return count;
    }
};
```

# 布隆过滤器代码模板
```C++
#include <iostream>
#include <bitset>
#include <cmath>
 
using namespace std;

typedef unsigned int uint; 
const int DEFAULT_SIZE = 1 << 20;
const int seed[] = { 5, 7, 11, 13, 31, 37, 61 };


class BloomFilter {
public:
	BloomFilter() : hash_func_count(3) {}
    BloomFilter(int bitsize, int str_count) { 
    	hash_func_count = ceil((bitsize / str_count) * log(2));
	}
    ~BloomFilter() {}
	
	uint RSHash(const char *str, int seed);
	void Add(const char *str);
	bool LookUp(const char *str);
 
private:
	int hash_func_count;
	bitset<DEFAULT_SIZE> bits;
};

uint BloomFilter::RSHash(const char *str, int seed) {  
    uint base = 63689;
    uint hash = 0;    
     
    while (*str) {    
        hash = hash * base + (*str++);    
        base *= seed;    
    }    
     
    return (hash & 0x7FFFFFFF);    
}    
 
void BloomFilter::Add(const char* str) {
	int index = 0;
	for(int i = 0; i < hash_func_count; ++i) {
		index = static_cast<int>(RSHash(str, seed[i])) % DEFAULT_SIZE;
		bits[index] = 1;
	}
	
	return ;
}
 
bool BloomFilter::LookUp(const char* str) {
	int index = 0;
	for(int i = 0; i < hash_func_count; ++i) {
		index = static_cast<int>(RSHash(str, seed[i])) % DEFAULT_SIZE;
		if (!bits[index]) return false; 
	}
 
	return true;
}
```

# LRU缓存机制代码
```C++
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};
```

# 排序算法

## 快速排序代码
```C++
int random_partition(vector<int>& nums, int l, intr) {
  int random_pivot_index = rand() % (r - l +1) + l;  //随机选择pivot
  int pivot = nums[random_pivot_index];
  swap(nums[random_pivot_index], nums[r]);
  int i = l - 1;
  for (int j=l; j<r; j++) {
    if (nums[j] < pivot) {
      i++;
      swap(nums[i], nums[j]);
    }
  }
  int pivot_index = i + 1;
  swap(nums[pivot_index], nums[r]);
  return pivot_index;
}
void random_quicksort(vector<int>& nums, int l, int r) {
  if (l < r) {
    int pivot_index = random_partition(nums, l, r);
    random_quicksort(nums, l, pivot_index-1);
    random_quicksort(nums, pivot_index+1, r);
  }
}
```

## 归并排序代码
```C++
void mergeSort(vector<int> &nums, int left, int right) {
	if (left >= right) return;
	
	int mid = left + (right - left) / 2;
	mergeSort(nums, left, mid);
	mergeSort(nums, mid+1, right);
	
	merge(nums, left, mid, right);
}


void merge(vector<int> &nums, int left, int mid, int right) {
	vector<int> tmp(right-left+1);
	int i = left, j = mid+1, k = 0;
	
	while (i <= mid && j <= right) {
		tmp[k++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
	}
	while (i <= mid) tmp[k++] = nums[i++];
	while (j <= right) tmp[k++] = nums[j++];
	
	for (i = left, k = 0; i <= right;) nums[i++] = tmp[k++];
}
```

## 堆排序代码
```C++
void heapify(vector<int> &array, int length, int i) {
    int left = 2 * i + 1, right = 2 * i + 2;
    int largest = i;

    if (left < length && array[left] > array[largest]) {
        largest = left;
    }
    if (right < length && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = array[i]; array[i] = array[largest]; array[largest] = temp;
        heapify(array, length, largest);
    }


    return ;
}

void heapSort(vector<int> &array) {
    if (array.size() == 0) return ;

    int length = array.size();
    for (int i = length / 2 - 1; i >= 0; i--) 
        heapify(array, length, i);

    for (int i = length - 1; i >= 0; i--) {
        int temp = array[0]; array[0] = array[i]; array[i] = temp;
        heapify(array, i, 0);
    }

    return ;
}
```