package il.co.ilrd.factory;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

/**
 * 
 * @author Andrei
 *
 * @param <K> - type of key to the Function object
 * @param <D> - argument type of the function called in Function.apply()
 * @param <T> - return type of the Function.apply() method
 * 
 */
public class Factory<K, D, T> {
	private Map<K, Function<D, ? extends T>> mapOfFunctions = new HashMap<>();

	public T create(K key) {
		return create(key, null);
	}

	public T create(K key, D args) {
		if (!mapOfFunctions.containsKey(key)) {
			throw new IllegalArgumentException();
		}
		
		
		return mapOfFunctions.get(key).apply(args);
	}

	public void add(K key, Function<D, ? extends T> function) {
		if (null == function) {
			throw new IllegalArgumentException();
		}
		mapOfFunctions.put(key, function);
	}
}

//TESTS:
//1. Lambda
//2. Anonymous class for Function interface
//3. Static method of specific type
//4. instance method of existing object
//5. instance method of particular type
//6. rewrite CompositeTree using factory

/*
 * package il.co.ilrd.factory; ​ import java.util.HashMap; import java.util.Map;
 * import java.util.function.Function; ​ public class Factory<K, D, T> { private
 * Map<K, Function<D, ? extends T>> mapOfFunctions = new HashMap<>();
 * 
 * public T create(K key) { return null; }
 * 
 * public T create(K key, D args) { return null; }
 * 
 * public void add(K key, Function<D, ? extends T> function) {
 * 
 * } } ​
 */
