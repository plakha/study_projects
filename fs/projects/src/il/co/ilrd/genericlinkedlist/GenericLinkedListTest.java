package il.co.ilrd.genericlinkedlist;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

class GenericLinkedListTest {

	@Test
	void test1() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();

		assertTrue(list.isEmpty());
		assertEquals(0, list.size());

		list.pushFront(1);

		assertFalse(list.isEmpty());
		assertEquals(1, list.size());

		list.pushFront(2);

		assertFalse(list.isEmpty());
		assertEquals(2, list.size());

		list.pushFront(3);

		assertFalse(list.isEmpty());
		assertEquals(3, list.size());

		Iterator<Integer> iter = list.find(1);

		assertEquals(1, iter.next());

		assertFalse(iter.hasNext());

		assertEquals(3, list.popFront());

		assertFalse(list.isEmpty());
		assertEquals(2, list.size());

	}

	@Test
	void testFind() {
		
		GenericLinkedList<Integer> list = new GenericLinkedList<>();

		list.pushFront(1);
		list.pushFront(2);
		list.pushFront(3);
		
		assertEquals(3, list.find(3).next());
		assertTrue(list.find(2).hasNext());

		
		assertFalse(list.find(545454).hasNext());
		
	}
	
	@Test
	void testPushPop() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();

		list.pushFront(1);
		list.pushFront(2);
		list.pushFront(3);

		assertEquals(3, list.popFront());
		assertEquals(2, list.popFront());
		assertEquals(1, list.popFront());

		assertTrue(list.isEmpty());
	}

	@Test
	void testIteration() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		Integer[] input = { 1, 2, 3 };

		for (Integer i : input) {
			list.pushFront(i);
		}

		{
			Iterator<Integer> iter = list.iterator();

			int i = 2;
			while (iter.hasNext()) {
				assertEquals(input[i--], iter.next());
			}
		}
	}

	@Test
	void testReverse() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		Integer[] input = { 1, 2, 3 };

		for (Integer i : input) {
			list.pushFront(i);
		}

		GenericLinkedList<Integer> reverseList = GenericLinkedList.newReverse(list);

		{
			Iterator<Integer> iter = reverseList.iterator();

			int i = 0;
			while (iter.hasNext()) {
				assertEquals(input[i++], iter.next());
			}
		}

	}

	@Test
	void testMerge() {
		GenericLinkedList<Integer> list1 = new GenericLinkedList<>();
		Integer[] input1 = { 3, 2, 1 };

		for (Integer i : input1) {
			list1.pushFront(i);
		}

		GenericLinkedList<Integer> list2 = new GenericLinkedList<>();
		Integer[] input2 = { 6, 5, 4 };

		for (Integer i : input2) {
			list2.pushFront(i);
		}

		{
			GenericLinkedList<Integer> merged = GenericLinkedList.newMerge(list1, list2);
			Integer[] expectedOutput = { 1, 2, 3, 4, 5, 6 };
			int i = 0;

			for (Integer member : merged) {
				assertEquals(expectedOutput[i++], member);
			}
		}
	}

	@Test
	void testConcur() {
		GenericLinkedList<Integer> list = new GenericLinkedList<>();
		list.pushFront(1);
		Iterator<Integer> iter = list.iterator();
		list.pushFront(1);

		assertThrows(ConcurrentModificationException.class, ()-> iter.next());
	}
}
