5.	Your task is to write operations of stack data structure in pseudo-codes using an array, then evaluate the complexities of the operations.
Void PUSH(value) {
	Arr[n] = value;
	->O(1);
}
Void POP() {
	Arr[n-1] = arr[n] 
}
->O(1)

6.	Your task is to write operations of stack data structure in pseudo-codes using a linked list, then evaluate the complexities of the operations.
Void PUSH(value)  {
	newNode.value = value;
	newNode.next = head;
	head = newNode
	}
->O(1)
Void POP() {
	Head = head - > next;
}
->O(1)
