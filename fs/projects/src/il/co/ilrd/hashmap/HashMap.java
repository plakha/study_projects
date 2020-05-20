package il.co.ilrd.hashmap;

import il.co.ilrd.pair.*;

import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.Collection;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Set;

/**
 * An object that maps keys to values. A map cannot contain duplicate keys; each
 * key can map to at most one value. Null value is allowed. Null key can work if
 * keys hashCode method accommodates null.
 * 
 * @author Andrei
 * @version 1.10.2019
 *
 * @param <K> - key type
 * @param <V> - value type
 */
public class HashMap<K, V> implements Map<K, V> {
	private static final int DEFAULT_CAPACITY = 16;
	private List<Entry<K, V>>[] buckets;
	private volatile int modCountEntries;
	private volatile Set<Entry<K, V>> entrySet;
	private volatile Set<K> keySet;
	private volatile Collection<V> values;

	public HashMap() {
		this(DEFAULT_CAPACITY);
	}

	public HashMap(int initialCapacity) {
		if (0 >= initialCapacity) {
			throw new IllegalArgumentException("Only positive initialCapacity argument allowed");
		}

		@SuppressWarnings("unchecked")
		List<Entry<K, V>>[] buckets = new List[initialCapacity];
		this.buckets = buckets;

		initializeBuckets();
	}

	/**
	 * Removes all of the mappings from this map . The map will be empty after this
	 * call returns.
	 */
	@Override
	public void clear() {
		synchronized (buckets) {
			++modCountEntries;
		}

		initializeBuckets();
	}

	/**
	 * Returns true if this map contains a mapping for the specified key. More
	 * formally, returns true if and only if this map contains a mapping for a key k
	 * such that (key==null ? k==null : key.equals(k)). (There can be at most one
	 * such mapping.)
	 * 
	 * @param key - key whose presence in this map is to be tested
	 * @return true if this map contains a mapping for the specified key
	 */
	@Override
	public boolean containsKey(Object key) {
		return null != getEntry(key);
	}

	/**
	 * Returns true if this map maps one or more keys to the specified value. More
	 * formally, returns true if and only if this map contains at least one mapping
	 * to a value v such that (value==null ? v==null : value.equals(v)). This
	 * operation will probably require time linear in the map size for most
	 * implementations of the Map interface.
	 * 
	 * @param value - value whose presence in this map is to be tested
	 * @return true if this map maps one or more keys to the specified value
	 * 
	 */
	@Override
	public boolean containsValue(Object value) {
		for (V v : values()) {
			if (null == v && null == value || v.equals(value)) {
				return true;
			}
		}

		return false;
	}

	/**
	 * Returns a Set view of the mappings contained in this map. The set is backed
	 * by the map, so changes to the map are reflected in the set, and vice-versa.
	 * If the map is modified while an iteration over the set is in progress (except
	 * through the iterator's own remove operation, or through the setValue
	 * operation on a map entry returned by the iterator) the results of the
	 * iteration are undefined. The set supports element removal, which removes the
	 * corresponding mapping from the map, via the Iterator.remove, Set.remove,
	 * removeAll, retainAll and clear operations. It does not support the add or
	 * addAll operations.
	 * 
	 * @return a set view of the mappings contained in this map
	 */
	@Override
	public Set<Entry<K, V>> entrySet() {
		if (null == entrySet) {
			synchronized (EntrySet.class) {
				if (null == entrySet) {
					entrySet = new EntrySet();
				}
			}
		}
		return entrySet;
	}

	/**
	 * Returns the value to which the specified key is mapped, or null if this map
	 * contains no mapping for the key.
	 * 
	 * More formally, if this map contains a mapping from a key k to a value v such
	 * that (key==null ? k==null : key.equals(k)), then this method returns v;
	 * otherwise it returns null. (There can be at most one such mapping.)
	 * 
	 * @param key - the key whose associated value is to be returned
	 * @return the value to which the specified key is mapped, or null if this map
	 *         contains no mapping for the key
	 *
	 */
	@Override
	public V get(Object key) {
		Entry<K, V> entry = getEntry(key);

		return null == entry ? null : entry.getValue();
	}

	/**
	 * Returns true if this map contains no key-value mappings.
	 * 
	 * @return true if this map contains no key-value mappings
	 */
	@Override
	public boolean isEmpty() {
		return entrySet().isEmpty();
	}

	/**
	 * Returns a Set view of the keys contained in this map. The set is backed by
	 * the map, so changes to the map are reflected in the set, and vice-versa. If
	 * the map is modified while an iteration over the set is in progress (except
	 * through the iterator's own remove operation), the results of the iteration
	 * are undefined. The set supports element removal, which removes the
	 * corresponding mapping from the map, via the Iterator.remove, Set.remove,
	 * removeAll, retainAll, and clear operations. It does not support the add or
	 * addAll operations.
	 * 
	 * @return a set view of the keys contained in this map
	 */
	@Override
	public Set<K> keySet() {
		if (null == keySet) {
			synchronized (KeySet.class) {
				if (null == keySet) {
					keySet = new KeySet();
				}
			}
		}

		return keySet;
	}

	/**
	 * Associates the specified value with the specified key in this map (optional
	 * operation). If the map previously contained a mapping for the key, the old
	 * value is replaced by the specified value. (A map m is said to contain a
	 * mapping for a key k if and only if m.containsKey(k) would return true.)
	 * 
	 * @param key   - key with which the specified value is to be associated
	 * @param value - value to be associated with the specified key
	 * @return the previous value associated with key, or null if there was no
	 *         mapping for key. (A null return can also indicate that the map
	 *         previously associated null with key, if the implementation supports
	 *         null values.)
	 */
	@Override
	public V put(K key, V value) {
		synchronized (buckets) {
			++modCountEntries;
		}

		Entry<K, V> oldEntry = getEntry(key);

		if (null != oldEntry) {
			return oldEntry.setValue(value);
		}

		buckets[bucketIndex(key)].add(Pair.of(key, value));

		return null;
	}

	/**
	 * Copies all of the mappings from the specified map to this map (optional
	 * operation). The effect of this call is equivalent to that of calling put(k,
	 * v) on this map once for each mapping from key k to value v in the specified
	 * map. The behavior of this operation is undefined if the specified map is
	 * modified while the operation is in progress.
	 * 
	 * @param sourceMap - mappings to be stored in this map
	 */
	@Override
	public void putAll(Map<? extends K, ? extends V> sourceMap) {
		// Set<Map.Entry<? extends K, ? extends V>> sourceEntries =
		// sourceMap.entrySet();//Doesn't work because of capture

		for (Entry<? extends K, ? extends V> entry : sourceMap.entrySet()) {
			put(entry.getKey(), entry.getValue());
		}
	}

	/**
	 * Removes the mapping for a key from this map if it is present (optional
	 * operation). More formally, if this map contains a mapping from key k to value
	 * v such that (key==null ? k==null : key.equals(k)), that mapping is removed.
	 * (The map can contain at most one such mapping.)
	 * 
	 * Returns the value to which this map previously associated the key, or null if
	 * the map contained no mapping for the key.
	 * 
	 * @param key - key whose mapping is to be removed from the map
	 * @return the previous value associated with key, or null if there was no
	 *         mapping for key.
	 */
	@Override
	public V remove(Object key) {
		final List<Entry<K, V>> bucket = buckets[bucketIndex(key)];
		final int bucketSize = bucket.size();

		for (int i = 0; bucketSize > i; ++i) {
			if ((bucket.get(i).getKey().equals(key))) {
				synchronized (bucket) {
					++modCountEntries;
				}

				return bucket.remove(i).getValue();

			}
		}

		return null;
	}

	/**
	 * Returns the number of key-value mappings in this map. If the map contains
	 * more than Integer.MAX_VALUE elements, returns Integer.MAX_VALUE.
	 * 
	 * @return the number of key-value mappings in this map
	 */
	@Override
	public int size() {
		return entrySet().size();
	}

	/**
	 * Returns a Collection view of the values contained in this map. The collection
	 * is backed by the map, so changes to the map are reflected in the collection,
	 * and vice-versa. If the map is modified while an iteration over the collection
	 * is in progress (except through the iterator's own remove operation), the
	 * results of the iteration are undefined. The collection supports element
	 * removal, which removes the corresponding mapping from the map, via the
	 * Iterator.remove, Collection.remove, removeAll, retainAll and clear
	 * operations. It does not support the add or addAll operations.
	 * 
	 * @return a collection view of the values contained in this map
	 */
	@Override
	public Collection<V> values() {
		if (null == values) {
			synchronized (Values.class) {
				if (null == values) {
					values = new Values();
				}
			}
		}
		return values;
	}

	private void initializeBuckets() {
		for (int i = 0; buckets.length > i; ++i) {
			buckets[i] = new LinkedList<>();
		}
	}

	private Entry<K, V> getEntry(Object key) {
		for (Entry<K, V> entry : buckets[bucketIndex(key)]) {
			if (null == entry.getKey() && null == key || entry.getKey().equals(key)) {
				return entry;
			}
		}

		return null;
	}

	private int bucketIndex(Object key) {
		return null == key ? 0 : Math.abs(key.hashCode()) % buckets.length;
	}

	private class EntrySet extends AbstractSet<Entry<K, V>> {
		@Override
		public Iterator<Entry<K, V>> iterator() {
			return new EntryIterator();
		}

		@Override
		public int size() {
			int size = 0;

			for (@SuppressWarnings("unused")
			Entry<K, V> entry : this) {
				++size;
			}

			return size;
		}

		private class EntryIterator implements Iterator<Entry<K, V>> {
			private int bucket;
			private Iterator<Entry<K, V>> currBucketIterator = buckets[bucket].iterator();
			private final int modCount = modCountEntries;

			@Override
			public boolean hasNext() {
				while (buckets.length > bucket) {
					if (modCount != modCountEntries) {
						throw new ConcurrentModificationException();
					}

					if (currBucketIterator.hasNext()) {
						return true;
					}
					++bucket;

					if (buckets.length > bucket) {
						currBucketIterator = buckets[bucket].iterator();
					}
				}

				return false;
			}

			@Override
			public Entry<K, V> next() {
				if (modCount != modCountEntries) {
					throw new ConcurrentModificationException();
				}

				if (hasNext()) {
					return currBucketIterator.next();
				}
				throw new NoSuchElementException();
			}
		}// class EntryIterator
	}// class EntrySet

	private class KeySet extends AbstractSet<K> {
		@Override
		public Iterator<K> iterator() {
			return new KeyIterator();
		}

		@Override
		public int size() {
			return entrySet().size();
		}

		private class KeyIterator implements Iterator<K> {
			private Iterator<Map.Entry<K, V>> entryIterator = entrySet().iterator();

			@Override
			public boolean hasNext() {
				return entryIterator.hasNext();
			}

			@Override
			public K next() {
				return entryIterator.next().getKey();
			}
		}// class KeyIterator
	}// class KeySet

	private class Values extends AbstractCollection<V> {
		@Override
		public Iterator<V> iterator() {
			return new ValueIterator();
		}

		@Override
		public int size() {
			return entrySet().size();
		}

		private class ValueIterator implements Iterator<V> {
			private Iterator<Map.Entry<K, V>> entryIterator = entrySet().iterator();

			@Override
			public boolean hasNext() {
				return entryIterator.hasNext();
			}

			@Override
			public V next() {
				return entryIterator.next().getValue();
			}
		}// class ValueIterator
	}// class Values

	@Override
	final protected void finalize() {
	}
}// class HashMap