package il.co.ilrd.designpatterns.observer;

import java.util.function.Consumer;//acts via side effects (no return value) void accept T

public class Callback<T> {
	private Consumer<T> onUpdate;
	private Worker onStop;
	private Dispatcher<? extends T> dispatcher;

	public Callback(Consumer<T> onUpdate, Worker onStop) {
		if (null == onUpdate) {
			throw new IllegalArgumentException("Please pass valid Consumer instance onUpdate");
		}
		this.onUpdate = onUpdate;
		this.onStop = onStop;
	}

	public void setDispatcher(Dispatcher<? extends T> dispatcher) {
		if (null != this.dispatcher) {
			this.dispatcher = dispatcher;
		} else {
			// allowed only if stopped / not subscribed
		}
	}

	public void update(T data) {
		onUpdate.accept(data);
	}

	public void stop() {
		if (null != onStop) {
			onStop.doWork();
		}
		dispatcher = null;
	}

	public void unsubscribe() {
		if (null == dispatcher) {
			throw new UnsupportedOperationException("Cannot unsubscribe before has subscribed");
		}
		dispatcher.unsubscribe(this);
		dispatcher = null;
	}
}
