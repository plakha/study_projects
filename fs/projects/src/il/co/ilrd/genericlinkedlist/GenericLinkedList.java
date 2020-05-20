package il.co.ilrd.genericlinkedlist;

import java.util.Iterator;
import java.util.List;
import java.util.ArrayList;
import java.util.ConcurrentModificationException;

/**
 * @author Andrei
 * @version 23/9/2019 Fail Fast Generic Linked List. Stack-like.
 */
public class GenericLinkedList<T> implements Iterable<T> {
	private Node<T> front;
	private ModCount modCount = new ModCount();

	public void pushFront(T data) {
		modCount.modify();
		front = new Node<>(data, front);
	}

	/**
	 * Return the data in the front and pop it from the list
	 * 
	 * @return the data in the front
	 */
	public T popFront() {
		modCount.modify();
		T data = front.getData();
		front = front.getNext();

		return data;
	}

	public int size() {
		Iterator<T> iter = iterator();
		int counter = 0;

		while (iter.hasNext()) {
			++counter;
			iter.next();
		}

		return counter;
	}

	public boolean isEmpty() {
		return (null == front);
	}

	/**
	 * @param the data searched in the linked list
	 * @return the iterator holding the value, or empty iterator if not found Empty
	 *         iterator means hasNext returns false
	 */
	public Iterator<T> find(T data) {
		Iterator<T> runner = iterator();
		Iterator<T> holder = iterator();

		while (holder.hasNext() && !data.equals(runner.next())) {
			holder.next();
		}

		return holder;
	}

	/**
	 * @param <S>
	 * @param Linked List to reverse
	 * @return a new, reversed linked list
	 */
	public static <S> GenericLinkedList<S> newReverse(GenericLinkedList<S> list) {
		GenericLinkedList<S> reversed = new GenericLinkedList<>();

		for (S s : list) {
			reversed.pushFront(s);
		}

		return reversed;
	}

	/**
	 * @param <U>
	 * @param list1
	 * @param list2
	 * @return new, concatenated linked list
	 */
	public static <U> GenericLinkedList<U> newMerge(GenericLinkedList<U> list1, GenericLinkedList<U> list2) {
		GenericLinkedList<U> merged = new GenericLinkedList<>();
		List<GenericLinkedList<U>> reversed = new ArrayList<>();

		reversed.add(newReverse(list2));
		reversed.add(newReverse(list1));

		for (GenericLinkedList<U> list : reversed) {
			for (U u : list) {
				merged.pushFront(u);
			}
		}

		return merged;
	}

	/**
	 * Constructs fail-fast iterator of the Linked List
	 */
	@Override
	public Iterator<T> iterator() {
		return new GenericLinkedListIterator<T>(front, modCount);
	}

	private static class ModCount {
		private int counter;

		public ModCount() {
		}

		private ModCount(int counter) {
			this.counter = counter;
		}

		public static ModCount copy(ModCount other) {
			return new ModCount(other.getCounter());
		}

		private int getCounter() {
			return counter;
		}

		public boolean modified(ModCount initial) {
			return !this.equals(initial);
		}

		@Override
		public boolean equals(Object other) {
			if (!(other instanceof ModCount)) {
				return false;
			}

			return counter == ((ModCount) other).getCounter();
		}

		@Override
		public int hashCode() {
			return ((Integer) counter).hashCode();
		}

		public void modify() {
			++counter;
		}
	}// class ModCount

	private static class GenericLinkedListIterator<W> implements Iterator<W> {
		private Node<W> current;
		private final ModCount initialModCountCopy;
		private final ModCount currentModCount;

		public GenericLinkedListIterator(Node<W> current, ModCount initialModCount) {
			this.current = current;
			currentModCount = initialModCount;
			initialModCountCopy = ModCount.copy(initialModCount);
		}

		@Override
		public boolean hasNext() {
			disproveConcurrentModification();

			return (null != current);
		}

		@Override
		public W next() {
			disproveConcurrentModification();

			W data = current.getData();
			current = current.getNext();

			return data;
		}

		private void disproveConcurrentModification() throws ConcurrentModificationException {
			if (currentModCount.modified(initialModCountCopy)) {
				throw new ConcurrentModificationException();
			}
		}
	}// class GenericLinkedListIterator

	private static class Node<V> {
		private V data;
		private Node<V> next;

		public Node(V data, Node<V> next) {
			this.data = data;
			this.next = next;
		}

		public Node<V> getNext() {
			return next;
		}

		public V getData() {
			return data;
		}
	}// class Node
}