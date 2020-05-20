package il.co.ilrd.pair;

import java.util.Comparator;
import java.util.Map.Entry;

/**
 * Class Pair, that may accomodate a key and a value (in a Map) or any ordered
 * pair. This exercise is related to Worksheets on Java Generics and that on
 * Java Collections.
 * 
 * @author Andrei
 * @version 25/09/2019
 *
 * @param <K> - a Key type
 * @param <V> - a Value type
 */
public class Pair<K, V> implements Entry<K, V> {
	private K key;
	private V value;

	private Pair(K key, V value) {
		this.key = key;
		this.value = value;
	}

	/**
	 * @return the Key
	 */
	@Override
	public K getKey() {
		return key;
	}

	/**
	 * @return the Value
	 * 
	 */
	@Override
	public V getValue() {
		return value;
	}

	/**
	 * Sets new value to the Pair instance.
	 * 
	 * @param value - new value
	 * @return old value
	 */
	@Override
	public V setValue(V value) {
		V oldValue = this.value;

		this.value = value;

		return oldValue;
	}

	/**
	 * Sets new key to the Pair instance. An extra method, not inherited from
	 * Map.Entry.
	 * 
	 * @param value - new value
	 * @return old value
	 */
	public K setKey(K key) {
		K oldKey = this.key;

		this.key = key;

		return oldKey;
	}

	/**
	 * Checks that the respective Keys and the Values equal
	 * 
	 * @return whether the passed instance equals to this one
	 */
	@Override
	public boolean equals(Object other) {
		if (!(other instanceof Pair<?, ?>)) {
			return false;
		}

		Pair<?, ?> otherPair = (Pair<?, ?>) other;

		return (null == otherPair.getKey() ? null == key : otherPair.getKey().equals(key))
				&& (null == otherPair.getValue() ? null == value : otherPair.getValue().equals(value));
	}

	@Override
	public int hashCode() {
		return (null == key ? 0 : key.hashCode()) ^ (null == value ? 0 : value.hashCode());
	}

	@Override
	public String toString() {
		return "key = " + key + ", value = " + value;
	}

	/**
	 * Static factory method returning an instance of Pair that holds the passed key
	 * and the value
	 * 
	 * @param <K>   - the Key type
	 * @param <V>   - the Value type
	 * @param key   - the key
	 * @param value - the value
	 * @return an instance of Pair
	 */
	public static <K, V> Pair<K, V> of(K key, V value) {
		return new Pair<K, V>(key, value);
	}

	/**
	 * The method return an ordered Pair containing instances of type T, such that
	 * the first one is the minimum of the passed array, and the other one - the
	 * maximum.
	 * 
	 * @param <T>   - the Comparable type contained by the array
	 * @param array - array of instances of type T
	 * @return an ordered pair of minimum and maximum value respectively
	 */
	public static <T extends Comparable<? super T>> Pair<T, T> minMax(T[] array) {
		Comparator<T> comparator = new Comparator<T>() {
			@Override
			public int compare(T t1, T t2) {
				return t1.compareTo(t2);
			}
		};

		return minMax(array, comparator);
	}

	/**
	 * The method return an ordered Pair containing instances of type T, such that
	 * the first one is the minimum of the passed array, and the other one - the
	 * maximum.
	 * 
	 * @param <T>        - the type contained by the array
	 * @param array      - array of instances of type T
	 * @param comparator - instance of Comparator for the type T
	 * @return an ordered pair of minimum and maximum value respectively
	 */
	public static <T> Pair<T, T> minMax(T[] array, Comparator<T> comparator) {
		T min = array[0], max = array[0];
		final int arrLen = array.length;

		for (int i = 1; arrLen > i; i += 2) {
			T tempMax = array[i - 1];
			T tempMin = array[i];

			if (0 > comparator.compare(array[i - 1], array[i])) {
				tempMax = array[i];
				tempMin = array[i - 1];
			}
			if (0 < comparator.compare(tempMax, max)) {
				max = tempMax;
			}
			if (0 > comparator.compare(tempMin, min)) {
				min = tempMin;
			}
		}

		if (0 != arrLen % 2 && 0 > comparator.compare(array[arrLen - 1], min)) {
			min = array[arrLen - 1];
		} else {
			if (0 < comparator.compare(array[arrLen - 1], max))
				max = array[arrLen - 1];
		}

		return of(min, max);
	}
}