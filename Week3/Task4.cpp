ENQUEUE(value) 
	newNode.value = value;
	if(front == null) front = newNode;
	rear = front;
	else
	rear.next = newNode;
	rear = newNode;
->O(1)
DEQUEUE() 
	TMP = FRONT;
	TMP = TMP.NEXT;
	FRONT = TMP;
->O(1)
