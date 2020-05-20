package il.co.ilrd.crud;

import java.io.Serializable;

public interface CRUD<E extends Serializable, K extends Serializable> extends AutoCloseable {

	public K create(E entry);

	public E read(K key);
	
	public void update(K key, E data);

	public void delete(K key);
}