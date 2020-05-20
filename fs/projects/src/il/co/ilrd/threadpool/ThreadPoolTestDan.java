package il.co.ilrd.threadpool;

import static org.junit.jupiter.api.Assertions.*;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import il.co.ilrd.hashmap.HashMap;
import il.co.ilrd.threadpool.ThreadPool.Priority;

class ThreadPoolTestDan {

	//@Test
	void testSetNumThreadsLower() throws Exception {
		ThreadPool pool = new ThreadPool(5);
		HashMap<Long,Integer> map = new HashMap<>();
		
		Callable<Long> task = new Callable<Long>() {
			@Override
			public Long call() throws InterruptedException {
				map.put(Thread.currentThread().getId(), map.getOrDefault(Thread.currentThread().getId(), 
						0) +1);
				return null;
			}
		};

		for(int i = 0; i < 5; ++i) {
			pool.submit(task, Priority.MEDIUM);
		}
		
		Thread.sleep(2000);
				
		pool.setNumThreads(1);
				
		for(int i = 0; i < 5; ++i) {
			pool.submit(task, Priority.MEDIUM);
		}
		
		Thread.sleep(3000);
		
		int counter = 0;
		
		for(Integer i : map.values()) {
			if(i > 1) {
				++counter;
			}
		}
		
		assertEquals(1, counter);
	}
	
	@Test
	void testSetNumThreadsHigher() throws Exception {
		ThreadPool pool = new ThreadPool(1);
		Queue<Long> queue = new LinkedList<>();

		Callable<Long> task = new Callable<Long>() {
			@Override
			public Long call() throws InterruptedException {
				queue.add(Thread.currentThread().getId());
				Thread.sleep(2000);
				return null;
			}
		};

		for(int i = 0; i < 2; ++i) {
			pool.submit(task, Priority.MEDIUM);
			
		}
		
		pool.setNumThreads(2);
		
		Thread.sleep(200);
		
		assertEquals(queue.size(), 2);
	}
	
	@Test
	void testPauseAndResume() throws Exception {
		ThreadPool pool = new ThreadPool(5);
		Queue<Long> queue = new LinkedList<>();
		
		Callable<Long> task = new Callable<Long>() {
			@Override
			public Long call() throws InterruptedException {
				queue.add(Thread.currentThread().getId());
				return null;
			}
		};
		
		pool.submit(task, Priority.MEDIUM);
		Thread.sleep(200);
		pool.pause();
		for (int i = 0; i < 4; ++i) {
			pool.submit(task, Priority.MEDIUM);
		}		
		
		assertEquals(1, queue.size());
		pool.resume();
		Thread.sleep(1000);
		assertEquals(5, queue.size());
	}
	
	void testBasic() throws Exception {
		ThreadPool pool = new ThreadPool(5);
		Queue<Long> queue = new LinkedList<>();
		Future<Integer> future = null;
		
		Callable<Integer> task = new Callable<Integer>() {
			@Override
			public Integer call() throws InterruptedException {
				queue.add(Thread.currentThread().getId());
				return queue.size();
			}
		};
		
		for (int i = 0; i < 5; ++i) {
			future = pool.submit(task, Priority.MEDIUM);
			assertEquals(future.get(), i+1);
		}
		
		assertEquals(true, future.isDone());
	}
	
	void testShutdownAndAwaitTermination() throws Exception {
		ThreadPool pool = new ThreadPool(5);
		Queue<Long> queue = new LinkedList<>();
		Future<Integer> future = null;
		
		Callable<Integer> task = new Callable<Integer>() {
			@Override
			public Integer call() throws InterruptedException {
				queue.add(Thread.currentThread().getId());
				Thread.sleep(2000);
				return queue.size();
			}
		};
		
		future = pool.submit(task, Priority.MEDIUM);
		assertEquals(future.isDone(), false);
		pool.shutdown();
		assertFalse(pool.awaitTermination(1, TimeUnit.SECONDS));
	}
	
	@Test
	void testShutdownAndAwaitTermination2() throws Exception {
		ThreadPool pool = new ThreadPool(5);
		Queue<Long> queue = new LinkedList<>();
		Future<Integer> future = null;
		
		Callable<Integer> task = new Callable<Integer>() {
			@Override
			public Integer call() throws InterruptedException {
				queue.add(Thread.currentThread().getId());
				Thread.sleep(2000);
				return queue.size();
			}
		};
		
		future = pool.submit(task, Priority.MEDIUM);
		assertEquals(future.isDone(), false);
		pool.shutdown();
		assertTrue(pool.awaitTermination(3, TimeUnit.SECONDS));
	}
	
	@Test
	void testCancel() throws Exception {
		ThreadPool pool = new ThreadPool(5);
		Queue<Long> queue = new LinkedList<>();
		Future<Integer> future = null;
		
		Callable<Integer> task = new Callable<Integer>() {
			@Override
			public Integer call() throws InterruptedException {
				queue.add(Thread.currentThread().getId());
				return queue.size();
			}
		};
		
		pool.pause();
		
		future = pool.submit(task, Priority.MEDIUM);
		
		future.cancel(true);
		
		pool.resume();
		
		Thread.sleep(1000);
		
		assertTrue(future.isCancelled());
		assertEquals(queue.size(), 0);
	}
	
	@Test
	void testGet() throws Exception {
		ThreadPool pool = new ThreadPool(5);
		Queue<Integer> queue = new LinkedList<>();
		Future<Integer> future = null;
		
		Callable<Integer> task = new Callable<Integer>() {
			@Override
			public Integer call() throws InterruptedException {
				queue.add(1);
				Thread.sleep(2000);
				return queue.size();
			}
		};
		
		future = pool.submit(task, Priority.MEDIUM);
		try{
			future.get(1, TimeUnit.SECONDS);
			fail();
		}catch(TimeoutException e) {
			assertEquals(queue.peek(), 1);
		}
	}

	@Test
	void testGet2() throws Exception {
		ThreadPool pool = new ThreadPool(5);
		Future<Integer> future = null;
		
		Callable<Integer> task = new Callable<Integer>() {
			@Override
			public Integer call() throws InterruptedException {
				return 1;
			}
		};
		
		future = pool.submit(task, Priority.MEDIUM);
		try{
			assertEquals(future.get(2, TimeUnit.SECONDS), 1);
		}catch(TimeoutException e) {
			fail();
		}
	}
	
	@Test
	public void testPauseResume() throws Exception {
		ThreadPool tp = new ThreadPool(1);
		
		Future<?> f2 = tp.submit(() -> { Thread.sleep(100); return 0; }, Priority.MEDIUM);

		tp.pause();
		tp.shutdown();

		Thread.sleep(700);

		Assertions.assertFalse(f2.isDone());
		
		tp.resume();
		
		Thread.sleep(1000);
		
		Assertions.assertTrue(f2.isDone());
	}
	
	@Test
	public void testSetNumThreadsWhenPaused() throws Exception {
		ThreadPool tp = new ThreadPool(2);
		
		Future<?> f1 = tp.submit(() -> { Thread.sleep(1000); return 0; }, Priority.MEDIUM);
		Future<?> f2 = tp.submit(() -> { Thread.sleep(1000); return 0; }, Priority.MEDIUM);
		
		Thread.sleep(200);
		
		tp.pause();
		
		tp.setNumThreads(0);
		
		Future<?> f3 = tp.submit(() -> { Thread.sleep(100); return 0; }, Priority.MEDIUM);

		tp.resume();

		Thread.sleep(700);

		Assertions.assertFalse(f3.isDone());
		
		
		Thread.sleep(1000);
		
		tp.shutdown();
		
		Assertions.assertTrue(f1.isDone());
		Assertions.assertTrue(f2.isDone());
		tp.awaitTermination(500, TimeUnit.MILLISECONDS);
	}
	
	@Test
	public void testSetNumThreadsWhenPaused2() throws Exception {
		ThreadPool tp = new ThreadPool(0);
		
		Future<?> f1 = tp.submit(() -> { System.out.println("hey"); Thread.sleep(1000); return 0; }, Priority.MEDIUM);
		Future<?> f2 = tp.submit(() -> { System.out.println("hey"); Thread.sleep(1000); return 0; }, Priority.MEDIUM);
		
		Thread.sleep(200);
		
		tp.pause();
		
		tp.setNumThreads(2);
		
		Assertions.assertFalse(f1.isDone());
		Assertions.assertFalse(f2.isDone());
		
		tp.shutdown();
		tp.awaitTermination(500, TimeUnit.MILLISECONDS);
	}
	
	@Test
	public void testGetWhenDone() throws InterruptedException, ExecutionException {
		ThreadPool tp = new ThreadPool(1);
		
		Future<?> f1 = tp.submit(() -> { return 1; }, Priority.MEDIUM);
		
		Thread.sleep(200);
		
		Assertions.assertTrue(f1.isDone());
		Assertions.assertEquals(f1.get(), 1);
		
		tp.shutdown();
		tp.awaitTermination(500, TimeUnit.MILLISECONDS);
	}
}