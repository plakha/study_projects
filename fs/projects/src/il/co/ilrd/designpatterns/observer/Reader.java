package il.co.ilrd.designpatterns.observer;

public class Reader<T> {
	private Callback<T> callback = new Callback<>((T data) -> atNotify(data), () -> atStop());

	static private int i = 1; 
	private int number = i++;

	public Reader() {
		System.out.println("I am new reader no " + number);
	}

	private void atStop() {
		System.out.println("Reader no " + number + "atStop");
	}

	private void atNotify(T data) {
		System.out.println("Dear reader no " + number + ", you've got newspaper");
	}

	void subscribe(Newspaper<T> newspaper) {
		newspaper.subscribe(callback);
	}
	
	void unsubscribe() {
		callback.unsubscribe();
	}
	
	public Callback<T> getCallback(){
		return callback;
	}
}
