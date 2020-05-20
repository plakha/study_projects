package il.co.ilrd.waitablequeue;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueueSemaphore<T> implements WaitableQueue<T> {
	private Queue<T> queue;
	private Lock lock = new ReentrantLock();
	private Semaphore numOfAvailableData = new Semaphore(0);

	public WaitableQueueSemaphore() {
		queue = new PriorityQueue<>();
	}

	public WaitableQueueSemaphore(Comparator<? super T> comparator) {
		queue = new PriorityQueue<>(comparator);
	}

	@Override
	public void enqueue(T item) {
		lock.lock();
		try {
			queue.add(item);
			numOfAvailableData.release();
		} finally {
			lock.unlock();
		}
	}

	@Override
	public T dequeue() throws InterruptedException {
		try {
			return dequeue(Long.MAX_VALUE, TimeUnit.DAYS);
		} catch (TimeoutException e) {
			assert false;// shouldn't happen
			e.printStackTrace();

			return null;
		}
	}

	@Override
	public T dequeue(long timeout, TimeUnit timeUnit) throws TimeoutException, InterruptedException {
		if (!numOfAvailableData.tryAcquire(timeout, timeUnit)) {
			throw new TimeoutException();
		}
		lock.lock();
		assert !queue.isEmpty();
		try {
			return queue.poll();
		} finally {
			lock.unlock();
		}
	}

	@Override
	public boolean remove(T item) {
		if (!numOfAvailableData.tryAcquire()) {
			return false;// was empty
		}

		lock.lock();
		boolean removed = false;
		try {
			removed = queue.remove(item);
			if (!removed) {
				numOfAvailableData.release();
			}
		} finally {
			lock.unlock();
		}

		return removed;
	}
}