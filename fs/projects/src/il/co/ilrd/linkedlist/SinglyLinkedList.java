package il.co.ilrd.linkedlist;

/**
 * @author student Andrei plahota@gmail.com
 *
 */

public class SinglyLinkedList {
	private Node head;

	public SinglyLinkedList() {
		head = null;
	}

	public SinglyLinkedList(Object value) {
		head = new Node(value);
	}

	public void pushFront(Object value) {
		head = new Node(value, head);
	}

	public void popFront() {
		head = head.next;
	}

	Iterator begin() {
		return new ListIteratorImpl(head);
	}

	public Iterator find(Object target) {
		Node runner = head;

		while (null != runner) {
			if (target.equals(runner.value)) {
				return new ListIteratorImpl(runner);
			}
			
			runner = runner.next;
		}

		return null;
	}

	public int size() {
		int size = 0;
		Node runner = head;
		
		while (null != runner) {
			++size;
			runner = runner.next;
		}

		return size;
	}

	public boolean isEmpty() {
		return null == head;
	}

	private class Node {
		private final Object value;
		private Node next;

		private Node(Object value) {
			this (value, null);
		}

		private Node(Object value, Node next) {
			this.value = value;
			this.next = next;
		}
	}//class Node

	public class ListIteratorImpl implements Iterator {
		private Node current;

		private ListIteratorImpl() {
			this (head);
		}

		private ListIteratorImpl(Node current) {
			this.current = current;
		}
	
		@Override
		public boolean hasNext() {
			return null != current;
		}

		@Override
		public Object next() {
			Node holder = current;

			current = holder.next;

			return holder.value;
		}
	}//class ListIteratorImpl
}//class SinglyLinkedList
