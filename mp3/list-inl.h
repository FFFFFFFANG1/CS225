/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  if (head_ == tail_){
    delete head_;
    return;
  }
  ListNode* trav = head_;
  while (trav->next != NULL){
    trav = trav->next;
    delete trav->prev;
  }
  delete tail_;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  ListNode* newnode = new ListNode (ndata);
  if (head_ == NULL) {
    head_ = newnode;
    tail_ = newnode;
    length_ ++;
    // cout << newnode->data << endl;
    return;
  }
  newnode->prev = NULL;
  newnode->next = head_;
  head_->prev = newnode;
  head_ = newnode;
  length_ ++;
  // cout << newnode->data << endl;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  ListNode* newnode  = new ListNode (ndata);
  if (head_ == NULL) {
    head_ = newnode;
    tail_ = newnode;
    length_ ++;
    // cout << newnode->data << endl;
    return;
  }
  newnode->prev = tail_;
  newnode->next = NULL;
  tail_->next = newnode;
  tail_ = newnode;
  length_ ++;
  // cout << newnode->data << endl;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    if (startPoint == NULL || endPoint == NULL || startPoint == endPoint) return;
    ListNode* begin = startPoint->prev;
    startPoint->prev = NULL;
    ListNode* end = endPoint->next;
    endPoint->next = NULL;
    ListNode* trav = startPoint;

    while (trav != NULL){
      ListNode* temp = trav->prev;
      trav->prev = trav->next;
      trav->next = temp;
      trav = trav->prev;
    }
    startPoint->next = end;
    endPoint->prev = begin;
    
    ListNode* temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;

    if (begin != NULL) begin->next = startPoint;
    if (end != NULL) end->prev = endPoint;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  if (n <= 1 || head_ == tail_) return;
  if (n >= size()) n = size() - 1;
  ListNode* startNode = head_;
  ListNode* endNode = head_;
  int first = 1;
  double last = 0;
  int len = size();
  while (len > 0) {last ++; len -= n;}

  while (endNode->next != NULL){
    for (int count = n; count > 1; count --){
      endNode = endNode->next;
      if (endNode->next == NULL) break;
    }
    reverse(startNode, endNode);
    first --;
    last --;
    if (first == 0) head_ = startNode;
    if (last <= 0) tail_ = endNode;
    startNode = endNode->next;
    endNode = endNode->next;
    if (endNode == NULL) break;
  }
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  if(head_==NULL ||head_->next==NULL)
  {
    return;
  }
  ListNode * curr = head_;
  ListNode * temp = curr->next;
  while(curr->next->next!=NULL && curr->next!=NULL)
  {
    curr = curr->next;
    curr->prev->next=curr->next;
    curr->next->prev =curr->prev;
    //insert
    temp = curr->next;
		tail_->next = curr;
		curr->prev = tail_;
		curr->next = NULL;
    tail_ = curr;
		curr = temp;
    // insertBack(curr->data);
    // delete curr;
		curr = temp;
  }
}
/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    if (start == NULL || start == tail_ || splitPoint == size() || splitPoint == 0) return NULL;
    ListNode* trav = start;
    if (splitPoint == 0) return head_;
    for (int count = 0; count < splitPoint; count ++){
      if (trav->next == NULL) break;
      trav = trav->next;
    }
    ListNode* breakpoint = trav;
    breakpoint->prev->next = NULL;
    breakpoint->prev = NULL;
    return breakpoint;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  if (first == NULL) return second;
  if (second == NULL) return first;
 
  ListNode* merg_head;
	if (first->data < second->data) {
		merg_head = first;
		first = first->next;
	}else {
		merg_head = second;
		second = second->next;
	}
	ListNode* curr = merg_head;
	while (first != NULL && second != NULL) {
		if (first->data < second->data) {
      curr->next = first;
			first->prev = curr;
			first = first->next;
		}else {
			curr->next = second;
			second->prev = curr;
			second = second->next;
		}
		curr = curr->next;
	}
  
  //end of one list
	if (first == NULL && second != NULL) {
		curr->next = second;
		second->prev = curr;
	}
	if (first != NULL && second == NULL) {
		curr->next = first;
		first->prev = curr;
	}
	return merg_head;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    if (chainLength == 1 || chainLength == 0) return start;
    ListNode* breakPoint = split(start, chainLength / 2);

    ListNode* left = mergesort(start, chainLength / 2); 
    ListNode* right = mergesort(breakPoint, chainLength - chainLength / 2);
    return merge(left, right);
}
