package il.co.ilrd.waitablequeue;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueueConditionVar<T> implements WaitableQueue<T> {
	private PriorityQueue<T> queue;
	private Lock lock = new ReentrantLock();
	private Condition notEmpty = lock.newCondition();

	public WaitableQueueConditionVar() {
		queue = new PriorityQueue<>();
	}

	public WaitableQueueConditionVar(Comparator<? super T> comparator) {
		queue = new PriorityQueue<>(comparator);
	}

	@Override
	public void enqueue(T item) {
		lock.lock();
		try {
			queue.add(item);
			notEmpty.signal();
		} finally {
			lock.unlock();
		}
	}

	@Override
	public T dequeue() throws InterruptedException {
		T ret = null;

		try {
			ret = dequeue(Long.MAX_VALUE, TimeUnit.DAYS);
		} catch (TimeoutException e) {
			assert false;// should never happen
			e.printStackTrace();
		}

		return ret;
	}

	@Override
	public T dequeue(long timeout, TimeUnit timeUnit) throws TimeoutException, InterruptedException {
		lock.lock();
		try {
			while (queue.isEmpty()) {// "if" is not safe: think about two consumers: one awaits, another goes ??										// through ???
				if (!notEmpty.await(timeout, timeUnit)) {
					throw new TimeoutException();
				}
			}
			assert !queue.isEmpty();
			return queue.poll();
		} finally {
			lock.unlock();
		}
	}

	@Override
	public boolean remove(T item) {
		lock.lock();
		try {
			return queue.remove(item);
		} finally {
			lock.unlock();
		}
	}
}