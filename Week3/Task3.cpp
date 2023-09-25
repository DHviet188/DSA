QUEUE {
	Queue(int size) {
        capacity = size;
       	 arr = new int[size];
       	 front = rear = -1;
 }
//KIEM TRA QUEUE RONG
	bool isEmpty() {
		Return front == -1;
	} -> O(1)
//KIEM TRA QUEUE ÐAY
	bool isFull() {
		Return (rear + 1) % capacity  == front;
	}
->O(1)
//THÊM MOT PHAN TU VÀO QUEUE
	Void enqueue(int value) {
	If(isFull()) return;
	If(isEmpty) {
	Front = rear = 0;
	} else {
	Rear = (rear + 1) % capacity;
	}
	Arr[rear] = value;
	Size++;
	}
->O(1)
	// LOAI BO PHAN TU ÐAU TIÊN KHOI QUEUE
		int dequeue() {
			If(isEmpty) return -1;
			If(front = rear) front = rear = -1;
			Else front = (front + 1) % capacity;
			Size--;
		}
->O(1)

}
