package m9.d19.q2;

public class List<T> {

    // Unused c-tor
    private List() {
    }

    public static <U> boolean hasLoop(Node<U> head) {
	return null != aLoopNode(head);
    }

    public static <S> void openLoop(Node<S> head) {
	if (!hasLoop(head)) {
	    return;
	}

	Node<S> aLoopNode = aLoopNode(head);
	int aLoopNodeListSize = sizeToANode(aLoopNode, aLoopNode);
	int listSize = sizeToANode(head, aLoopNode);
	Node<S> theLongerList = aLoopNodeListSize > listSize ? aLoopNode : head;
	Node<S> theShorterList = theLongerList == aLoopNode ? head : aLoopNode;

	theLongerList = promoteBy(theLongerList, Math.abs(aLoopNodeListSize - listSize));

	while (theLongerList != theShorterList) {
	    theLongerList = theLongerList.next();
	    theShorterList = theShorterList.next();
	}
	Node<S> theLoopIntersectionNode = theLongerList;

	while (aLoopNode.next() != theLoopIntersectionNode) {
	    aLoopNode = aLoopNode.next();
	}

	aLoopNode.setNext(null);
    }

    private static <T> Node<T> promoteBy(Node<T> head, int by) {
	for (int i = 0; by > i && null != head; ++i) {
	    head = head.next();
	}

	return head;
    }

    /**
     * 
     * @param <T>
     * @param head      - head of the list
     * @param aLoopNode - a node up to which to compute the size
     * @return size of the list from the head to the the given node exclusively
     */
    private static <T> int sizeToANode(Node<T> head, Node<T> aNode) {
	int size = 0;
	
	while (head != aNode) {
	    ++size;
	    head = head.next();
	}

	return size;
    }

    private static <S> Node<S> fastNext(Node<S> node) {
	return null == (node = node.next()) ? null : node.next();
    }

    private static <V> Node<V> aLoopNode(Node<V> head) {
	Node<V> slow = head;
	Node<V> fast = head.next();

	while (null != fast) {
	    if (fast == slow) {
		break;
	    }

	    fast = fastNext(fast);
	    slow = slow.next();
	}

	return fast;
    }

    public static <T> boolean hasIntersection(Node<T> list1, Node<T> list2) {
	if (hasLoop(list1) || hasLoop(list2)) {
	    throw new IllegalArgumentException("Check passed lists for loops!");
	}
	
	return false;
    }

    @SuppressWarnings("unused")
	private static <T> Node<T> anIntersection(Node<T> list1, Node<T> list2) {
	int size1 = sizeToANode(list1, null);
	int size2 = sizeToANode(list2, null);
	
	return null;
    }
}// class List
