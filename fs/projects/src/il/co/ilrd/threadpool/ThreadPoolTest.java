package il.co.ilrd.threadpool;

import static org.junit.jupiter.api.Assertions.*;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.atomic.AtomicInteger;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import il.co.ilrd.threadpool.ThreadPool.Priority;

class ThreadPoolTest {

	@Test
	void testCreatePoolPool() throws InterruptedException, ExecutionException {
		class myFirstTask implements Callable<Integer> {
			int results[];
			int index;

			myFirstTask(int results[], int index) {
				this.results = results;
				this.index = index;
			}

			@Override
			public Integer call() throws Exception {
				results[index] = index;

				return index;
			}
		}

		ThreadPool myPool = new ThreadPool(3);
		int results[] = new int[5];
		int expected[] = new int[5];
		List<Future<Integer>> futuresList = new ArrayList<>();

		for (int i = 0; i < 5; ++i) {
			results[i] = 0;
			expected[i] = i;
			futuresList.add(myPool.submit(new myFirstTask(results, i), Priority.HIGH));
		}

		Thread.sleep(1000);

		for (int i = 0; i < 5; ++i) {
			assertEquals(futuresList.get(i).get(), expected[i]);
		}
	}

	@Test
	void testgGet() throws InterruptedException, ExecutionException {
		class mySecondTask implements Callable<Integer> {
			int index;

			mySecondTask(int index) {
				this.index = index;
			}

			@Override
			public Integer call() throws Exception {
				return ++index;
			}
		}

		ThreadPool myPool = new ThreadPool(3);
		int expected[] = new int[5];
		List<Future<Integer>> futuresList = new ArrayList<>();

		for (int i = 0; i < 5; ++i) {
			expected[i] = i + 1;
			futuresList.add(myPool.submit(new mySecondTask(i), Priority.HIGH));
		}

		Thread.sleep(1000);

		for (int i = 0; i < 5; ++i) {
			assertEquals(futuresList.get(i).get(), expected[i]);
		}
	}

	@Test
	void millionTasksAndShutDown() throws InterruptedException {
		ThreadPool pool = new ThreadPool(12);
		final int million = 1_000_000;
		AtomicInteger cntTasks = new AtomicInteger(0);
		Runnable task = () -> cntTasks.addAndGet(1);
		for (int i = 0; million > i; ++i) {
			pool.execute(task);
		}
		pool.shutdown();
		pool.awaitTermination(Long.MAX_VALUE, TimeUnit.DAYS);
		assertTrue(million == cntTasks.get());
	}

	@Test
	void millionTasksWithPause() throws InterruptedException {
		ThreadPool pool = new ThreadPool(0);
		final int million = 1_000_000;
		AtomicInteger cntTasks = new AtomicInteger(0);
		Runnable task = () -> cntTasks.addAndGet(1);
		pool.setNumThreads(35);
		for (int i = 0; million > i; ++i) {
			pool.execute(task);
		}

		pool.pause();
		pool.resume();

		pool.shutdown();
		pool.awaitTermination(Long.MAX_VALUE, TimeUnit.DAYS);
		assertTrue(million == cntTasks.get());
	}

	@Test
	public void testThreadPool() throws InterruptedException {
		ThreadPool tp = new ThreadPool();
		AtomicInteger ai = new AtomicInteger(0);

		Future<Integer> res1 = tp.submit(() -> {
			Thread.sleep(500);
			return 5;
		});
		Future<?> res2 = tp.submit(() -> ai.getAndIncrement(), ThreadPool.Priority.MEDIUM);

		try {
			Assertions.assertFalse(res1.isDone());
			Assertions.assertEquals(5, res1.get());
			Assertions.assertTrue(res1.isDone());
			Assertions.assertTrue(res2.isDone());

		} catch (InterruptedException | ExecutionException e) {
			e.printStackTrace();
		}

		tp.shutdown();
		Assertions.assertTrue(tp.awaitTermination(10000, TimeUnit.MILLISECONDS));
	}

	@Test
	public void testSubmitAfterShutdown() {
		ThreadPool tp = new ThreadPool();

		Assertions.assertThrows(NullPointerException.class, () -> tp.submit(null, Priority.HIGH, null));
		Runnable runn = null;
		Assertions.assertThrows(NullPointerException.class, () -> tp.submit(runn, Priority.HIGH));

		tp.shutdown();

		Assertions.assertThrows(RejectedExecutionException.class,
				() -> tp.submit(() -> System.out.println("hello"), Priority.HIGH));
	}

	@Test
	public void testPriority() throws InterruptedException {
		ThreadPool tp = new ThreadPool(1);
		AtomicInteger ai = new AtomicInteger(0);

		tp.pause();

		Future<Integer> f1 = tp.submit(() -> ai.decrementAndGet(), Priority.LOW);
		Future<Integer> f2 = tp.submit(() -> ai.decrementAndGet(), Priority.MEDIUM);
		Future<Integer> f3 = tp.submit(() -> ai.getAndSet(10), Priority.HIGH);

		tp.resume();

		try {
			Assertions.assertEquals(8, f1.get());
			Assertions.assertEquals(9, f2.get());
			Assertions.assertEquals(0, f3.get());
		} catch (InterruptedException | ExecutionException e) {
			e.printStackTrace();
		}

		tp.shutdown();
		tp.awaitTermination(1000, TimeUnit.MILLISECONDS);
	}

	@Test
	public void testPauseResume() throws InterruptedException {
		ThreadPool tp = new ThreadPool(1);
		@SuppressWarnings("unused")
		AtomicInteger ai = new AtomicInteger(0);

		@SuppressWarnings("unused")
		Future<?> f1 = tp.submit(() -> {
			Thread.sleep(250);
			return 0;
		}, Priority.HIGH);
		Future<?> f2 = tp.submit(() -> {
			Thread.sleep(250);
			return 0;
		}, Priority.HIGH);

		tp.pause();
		tp.shutdown();

		try {
			Thread.sleep(700);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		Assertions.assertFalse(f2.isDone());

		tp.resume();
		try {
			Thread.sleep(400);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		Assertions.assertTrue(f2.isDone());
		Assertions.assertTrue(tp.awaitTermination(1000, TimeUnit.MILLISECONDS));
	}

	@Test
	public void testExecutionFailure() {
		ThreadPool tp = new ThreadPool(1);

		@SuppressWarnings("unused")
		Future<Integer> f1 = tp.submit(() -> {
			if (true) {
				throw new IllegalArgumentException();
			}

			return 0;
		}, Priority.HIGH);
		Assertions.assertThrows(ExecutionException.class, () -> f1.get());
		Assertions.assertFalse(f1.isCancelled());

		try {
			f1.get();
		} catch (InterruptedException e) {
		} catch (ExecutionException e) {
			Assertions.assertEquals(e.getCause().getClass(), IllegalArgumentException.class);
		}
	}

	@Test
	public void testSetNumThreads() throws InterruptedException {
		ThreadPool tp = new ThreadPool(1);

		// tp.pause();

		Future<Integer> f1 = tp.submit(() -> 1, Priority.HIGH);

		tp.setNumThreads(0);

		// tp.resume();

		Assertions.assertThrows(TimeoutException.class, () -> f1.get(300, TimeUnit.MILLISECONDS));

		tp.setNumThreads(3);

		try {
			Assertions.assertEquals(1, f1.get(300, TimeUnit.MILLISECONDS));
		} catch (InterruptedException | ExecutionException | TimeoutException e1) {
			e1.printStackTrace();
		}

		tp.shutdown();
		Assertions.assertTrue(tp.awaitTermination(3000, TimeUnit.MILLISECONDS));
	}

	@Test
	public void testExecuteAndRunnable() throws InterruptedException {
		ThreadPool tp = new ThreadPool(1);
		AtomicInteger ai = new AtomicInteger(0);

		@SuppressWarnings("unused")
		Future<?> f = tp.submit(() -> {
			ai.getAndIncrement();
		}, Priority.HIGH);
		tp.execute(() -> ai.getAndIncrement());
		Future<AtomicInteger> f2 = tp.submit(() -> {
			ai.getAndIncrement();
		}, Priority.HIGH, ai);

		tp.shutdown();
		Assertions.assertTrue(tp.awaitTermination(1000, TimeUnit.MILLISECONDS));
		Assertions.assertEquals(3, ai.get());
		try {
			Assertions.assertEquals(f2.get(), ai);
		} catch (InterruptedException | ExecutionException e) {
			Assertions.assertFalse(true);
			e.printStackTrace();
		}
	}

	@Test
	public void testCancel() {
		ThreadPool tp = new ThreadPool(1);

		tp.pause();

		Future<Integer> f1 = tp.submit(() -> 1);
		Future<Integer> f2 = tp.submit(() -> {
			Thread.sleep(1000);
			return 1;
		});

		Assertions.assertFalse(f1.isDone());
		Assertions.assertTrue(f1.cancel(true));
		Assertions.assertFalse(f1.cancel(false));
		Assertions.assertTrue(f1.isCancelled());
		Assertions.assertTrue(f1.isDone());

		tp.resume();

		Assertions.assertFalse(f2.isCancelled());
	}

	@Test
	public void testAwaitTermination() throws InterruptedException {
		ThreadPool tp = new ThreadPool(1);

		tp.submit(() -> {
			Thread.sleep(2000);
			return 1;
		});

		tp.shutdown();

		Assertions.assertFalse(tp.awaitTermination(100, TimeUnit.MILLISECONDS));
	}

}
