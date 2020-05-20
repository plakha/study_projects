package il.co.ilrd.hashmap;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;

import org.junit.jupiter.api.Test;

class HashMapTest {

	@Test
	public void testSize() {
		HashMap<Integer, String> hashMap = new HashMap<>();
		assertTrue(hashMap.isEmpty());
		assertEquals(0, hashMap.size());
		assertFalse(hashMap.containsKey(0));
		assertFalse(hashMap.containsValue(null));
		// assertFalse(hashMap.containsKey(null));//doesnt work because the Integers
		// hashCode throws null pointer exception

		hashMap.put(0, "zeroth");
		assertFalse(hashMap.isEmpty());
		assertEquals(1, hashMap.size());
		assertTrue(hashMap.containsKey(0));
		assertTrue(hashMap.containsValue("zeroth"));

		hashMap.put(0, "zeroeth");
		assertFalse(hashMap.isEmpty());
		assertEquals(1, hashMap.size());
		assertTrue(hashMap.containsKey(0));
		assertTrue(hashMap.containsValue("zeroeth"));

		hashMap.put(1, "first");
		assertFalse(hashMap.isEmpty());
		assertEquals(2, hashMap.size());
		assertEquals("first", hashMap.get(1));

		Set<Entry<Integer, String>> entrySet = hashMap.entrySet();

		Iterator<Entry<Integer, String>> entryIterator = entrySet.iterator();

		assertEquals(hashMap.size(), entrySet.size());

		assertTrue(entryIterator.hasNext());

		HashMap<Integer, String> hashMap2 = new HashMap<>();
		hashMap2.putAll(hashMap);
		assertTrue(hashMap2.containsKey(0));
		assertTrue(hashMap2.containsValue("zeroeth"));

		hashMap.clear();
		assertTrue(hashMap.isEmpty());
		assertEquals(0, hashMap.size());

		hashMap.put(0, "zeroth");
		assertFalse(hashMap.isEmpty());
		assertEquals(1, hashMap.size());
		assertTrue(hashMap.containsKey(0));
		assertTrue(hashMap.containsValue("zeroth"));
	}

	@Test
	public void testIterator() {
		HashMap<Integer, String> hashMap = new HashMap<>();
		Iterator<String> valueIterator = hashMap.values().iterator();

		hashMap.put(0, "zeroeth");
		hashMap.put(1, "first");

		hashMap.put(2, "second");
		assertThrows(ConcurrentModificationException.class, () -> valueIterator.hasNext());
	}

	@Test
	public void testPutAll() {
		HashMap<Integer, String> hashMap = new HashMap<>();
		HashMap<Integer, String> hashMap2 = new HashMap<>();
		hashMap.put(0, "zeroeth");
		assertEquals(1, hashMap.size());
		Iterator<String> valueIterator = hashMap.values().iterator();

		hashMap2.put(1, "first");

		hashMap.putAll(hashMap2);
		assertEquals(2, hashMap.size());

		assertThrows(ConcurrentModificationException.class, () -> valueIterator.hasNext());
		
		assertEquals(null, hashMap.get(3));
		assertEquals("first", hashMap.get(1));

	}
	
	@Test
	public void testSet() {
		HashMap<Integer, String> hashMap = new HashMap<>();
		
		Set<Entry<Integer, String>> entrySet1 = hashMap.entrySet();
		Set<Entry<Integer, String>> entrySet2 = hashMap.entrySet();
		assertTrue(entrySet1 == entrySet2);
		
		Set<Integer> keySet1 = hashMap.keySet();
		Set<Integer> keySet2 = hashMap.keySet();
		assertTrue(keySet1 == keySet2);
	}
	
	@Test
	public void testNull() {
		HashMap<Integer, String> hashMap = new HashMap<>();
		hashMap.put(null, null);
		assertTrue(hashMap.get(null) == null);
		

	}
}
