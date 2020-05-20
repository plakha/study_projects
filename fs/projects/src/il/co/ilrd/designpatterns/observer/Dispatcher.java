package il.co.ilrd.designpatterns.observer;

import java.util.HashSet;
import java.util.Set;

public class Dispatcher<T> {
	private Set<Callback<? super T>> callbacks = new HashSet<>();

	public void subscribe(Callback<? super T> callback) {
		if (null == callback) {
			throw new IllegalArgumentException("Please pass non-null callback argument");
		}
		callbacks.add(callback);
		callback.setDispatcher(this);
	}

	public void unsubscribe(Callback<? super T> callback) {
		callbacks.remove(callback);
	}

	public void notify(T data) {
		for (Callback<? super T> callback : callbacks) {
			assert null != callback;// null entries weren't allowed
			callback.update(data);
		}
	}

	public void stop() {
		for (Callback<? super T> callback : callbacks) {
			assert null != callback;// null entries weren't allowed
			callback.stop();
		}
		callbacks.clear();
	}
}