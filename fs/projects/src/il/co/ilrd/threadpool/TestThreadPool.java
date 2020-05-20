package il.co.ilrd.threadpool;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

import il.co.ilrd.threadpool.ThreadPool.Priority;

public class TestThreadPool {
	private static final int NUM_RUNNABLES = 2;
	private static final int NUM_CALLABLES = 32;

	private static class CallableCounter implements Callable<Integer> {
		private static int count;
		int index = count++;

		@Override
		public Integer call() throws Exception {
			System.out.println(this);
			return index;
		}

		@Override
		public String toString() {
			return "Callable number" + index;
		}

	}

	private static class RunnableCounter implements Runnable {
		private static int count;
		int index = count++;

		@Override
		public String toString() {
			return "Runnable number" + index;
		}

		@Override
		public void run() {
			System.out.println(this);
		}
	}

	public static void main(String[] args) {
		ThreadPool myThreadPool = new ThreadPool(2);
		
		List<Runnable> myRunnables = new ArrayList<>();
		for (int i = 0; NUM_RUNNABLES > i; ++i) {
			myRunnables.add(new RunnableCounter());
		}

		List<Callable<Integer>> myCallables = new ArrayList<>();
		for (int i = 0; NUM_CALLABLES > i; ++i) {
			myCallables.add(new CallableCounter());
		}

		List<Future<Integer>> callableFutures= new ArrayList<>(); 
		for (Callable<Integer> callable : myCallables) {
			callableFutures.add(myThreadPool.submit(callable, Priority.LOW));

		}

		for (Runnable runnable : myRunnables) {
			 myThreadPool.submit(runnable, Priority.MEDIUM);
		}
		
		for (Future<Integer> future : callableFutures) {
			try {
				System.out.println(future.get());
			} catch (InterruptedException | ExecutionException e) {
				e.printStackTrace();
			}	
		}
	}
}
