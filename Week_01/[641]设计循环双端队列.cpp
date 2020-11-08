class MyCircularDeque {
private:
    int front, rear;
    int tag;
    int size;
    int *data;
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        data = new int[k];
        for (int i = 0; i < k; ++i) {
            data[i] = -1;
        }
        size = k;
        front = 0;
        rear =  0;
        tag = 0;
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if (isFull()) {
            return false;
        } else {
            front = (front - 1 + size) % size;
            data[front] = value;
            tag = 1;
            return true;
        }
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if (isFull()) {
            return false;
        } else {
            data[rear] = value;
            rear = (rear + 1) % size;
            tag = 1;
            return true;
        }
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if (isEmpty()) {
            return false;
        } else {
            data[front] = -1;
            front = (front + 1) % size;
            tag = 0;
            return true;
        }
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if (isEmpty()) {
            return false;
        } else {
            rear = (rear - 1 + size) % size;
            data[rear] = -1;
            tag = 0;
            return true;
        }
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        return data[front];
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        return data[(rear - 1 + size) % size];
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return front == rear && tag == 0;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return front == rear && tag == 1;
    }
};