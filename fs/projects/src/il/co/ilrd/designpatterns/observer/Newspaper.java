package il.co.ilrd.designpatterns.observer;

public class Newspaper<T> {
	private Dispatcher<T> dispatcher = new Dispatcher<>();
 
	void subscribe(Callback<T> callback) {
		dispatcher.subscribe(callback);
	}

	public Dispatcher<T> getDispatcher() {
		return dispatcher;
	}

	void unsubscribe(Callback<T> callback) {
		dispatcher.unsubscribe(callback);
	}

	void closeNewspaper() {
		dispatcher.stop();
	}
}
