package il.co.ilrd.threadpool;

import java.util.Map;
import java.util.WeakHashMap;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Future;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import java.util.concurrent.Executors;

import il.co.ilrd.waitablequeue.*;

/**
 * Non thread safe implementation of Thread Pool
 * 
 * @author plahota
 * @version 22/10/2019
 */
public class ThreadPool implements Executor {
	public static final int DEFAULT_NTHREADS = 10;
	
	private static final Priority DEFAULT_PRIORITY = Priority.MEDIUM;
	private final WaitableQueue<Task<?>> taskWaitableQueue = new WaitableQueueConditionVar<>();
	private final Map<Worker, ?> workers = new WeakHashMap<>();// keys are weak
	private int numWorkers;
	
	private boolean isShuttingdown;
	private boolean isPaused;
	private Semaphore pauseSem = new Semaphore(0);
	private final Runnable killer = () -> {// is used to set number of threads and to shutdown the threadpool
		Thread thisWorker = Thread.currentThread();
		assert thisWorker instanceof Worker;// must be Worker, because only workers were created
		((Worker) thisWorker).shouldStop = true;
	};

	/**
	 * C-tor of the ThreadPool. Constructs a ThreadPool instance with
	 * DEFAULT_NTHREADS threads
	 */
	public ThreadPool() {
		this(DEFAULT_NTHREADS);
	}

	/**
	 * C-tor of the ThreadPool.
	 * 
	 * @param nThreads - how many threads to run concurrently in the ThreadPool
	 * @throws IllegalArgumentException - if negative argument passed
	 */
	public ThreadPool(int nThreads) {
		if (0 > nThreads) {
			throw new IllegalArgumentException("At least zero threads required");
		}

		numWorkers = nThreads;
		initThreads(nThreads);
	}

	/**
	 * Execute the command.
	 * 
	 * @param command - non-null Runnable
	 * @throws IllegalArgumentException   - if passed null
	 * @throws RejectedExecutionException - if trying to execute after shutdown has
	 *                                    been called
	 */
	@Override
	public void execute(Runnable command) {
		submit(command, DEFAULT_PRIORITY);
	}

	/**
	 * 
	 * @param command  non-null Callable
	 * @param <T>      - the Callable's return type
	 * @param priority - Enum Priority *
	 * @throws IllegalArgumentException   - if passed null argument
	 * @throws RejectedExecutionException - if trying to submit after shutdown has
	 *                                    been called
	 * @return instance of Future
	 */
	public <T> Future<T> submit(Callable<T> command, Priority priority) {
		return submit(command, priority.getPriorityIndex());
	}

	/**
	 * 
	 * @param command non-null Callable
	 * @param <T>     - the Callable's return type
	 * @throws IllegalArgumentException   - if passed null argument
	 * @throws RejectedExecutionException - if trying to submit after shutdown has
	 *                                    been called
	 * @return instance of Future
	 */
	public <T> Future<T> submit(Callable<T> command) {
		return submit(command, DEFAULT_PRIORITY);
	}

	/**
	 * @param command  non-null Callable
	 * @param <T>      - the Callable's return type
	 * @param priority - Enum Priority
	 * @throws IllegalArgumentException   - if passed null argument
	 * @throws RejectedExecutionException - if trying to submit after shutdown has
	 *                                    been called
	 * @return instance of Future
	 */
	public Future<?> submit(Runnable command, Priority priority) {
		return submit(command, priority, null);
	}

	/**
	 * 
	 * @param command  non-null Callable
	 * @param <T>      - the Callable's return type
	 * @param priority - Enum Priority
	 * @param result   type T instance to refer to the result
	 * @throws IllegalArgumentException   - if passed null argument
	 * @throws RejectedExecutionException - if trying to submit after shutdown has
	 *                                    been called
	 * @return instance of Future
	 */
	public <T> Future<T> submit(Runnable command, Priority priority, T result) {
		if (null == command) {
			throw new NullPointerException("Should pass valid runnable");
		}

		return submit(Executors.callable(command, result), priority);
	}

	/**
	 * Method to reset number of threads.
	 * 
	 * @param nThreads - non- negative number of threads to set the ThreadPool to
	 * @throws IllegalStateException    - if called after pause() before resume(),
	 *                                  or called after shutdown()
	 * @throws IllegalArgumentException - if passed negative argument
	 */
	public void setNumThreads(int nThreads) {
		if (0 > nThreads) {
			throw new IllegalArgumentException("At least zero threads required");
		}
		if (isPaused || isShuttingdown) {
			throw new IllegalStateException("Can't set Num of Thread while paused or shuttinh down");
		}

		int delta = nThreads - numWorkers;

		numWorkers = nThreads;
		if (0 > delta) {
			decrementNumWorkers(-delta);
		} else {
			assert 0 <= delta;
			incrementNumWorkers(delta);
		}
	}

	/**
	 * Try to pause the the ThreadPool. Lets the tasks already running to complete.
	 * The method is non blocking.
	 * 
	 * @throws IllegalStateException - if already had pause() called and not resumed
	 */
	public void pause() {
		if (isPaused) {
			throw new IllegalStateException("Already paused");
		}

		final Runnable pauseWorker = () -> pauseSem.acquireUninterruptibly();
		final int PAUSE_WORKER_PRIORITY = 15;

		isPaused = true;
		pauseSem.drainPermits();
		for (int i = 0; i < numWorkers; ++i) {
			submit(Executors.callable(pauseWorker), PAUSE_WORKER_PRIORITY);
		}
	}

	/**
	 * Resumes the thread pool.
	 */
	public void resume() {
		if (!isPaused) {
			throw new IllegalStateException("Already resumed");
		}
		isPaused = false;
		pauseSem.release(numWorkers);
	}

	/**
	 * Tries to shutdown the threadpool. Lets the tasks already running to complete.
	 * The methos is non-blocking. If the ThreadPool is paused, the user is expected
	 * to call resume() to allow shutdown process go.
	 */
	public void shutdown() {
		if (!isShuttingdown) {
			final int KILLER_PRIORITY = -5;

			for (int i = 0; i < numWorkers; ++i) {
				submit(Executors.callable(killer), KILLER_PRIORITY);
			}

			isShuttingdown = true;
		}
	}

	/**
	 * Blocking method the user may call to know if the ThreadPool threads die
	 * within the given timeout. It only is possible to call the method on
	 * ThreadPool that is shutting down (shutdown()).
	 * 
	 * @param timeout how long to wait for termination
	 * @param unit
	 * @return true if termination suceeded within the elapsed timeout, false - in
	 *         any other case.
	 * @throws InterruptedException
	 * @throws IllegalStateException if haven't called shutdown
	 */
	public boolean awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {
		if (0 > timeout) {
			throw new IllegalArgumentException();
		}
		if (!isShuttingdown) {
			throw new IllegalStateException("call shutdown() before calling awaitTermination()");
		}

		timeout = unit.toMillis(timeout);

		for (Worker worker : workers.keySet()) {
			long beforeJoin = System.nanoTime();
			worker.join(timeout);
			timeout -= TimeUnit.NANOSECONDS.toMillis(System.nanoTime() - beforeJoin);

			if (0 >= timeout) {
				return false;
			}
		}

		return true;
	}

	/**
	 * enum that presents Priorities for tasks pushed to the ThreadPool
	 * 
	 * @author plahota
	 */
	public enum Priority {
		HIGH(10), MEDIUM(5), LOW(1);

		private int priorityIndex;

		private Priority(int priorityIndex) {
			this.priorityIndex = priorityIndex;
		}

		private int getPriorityIndex() {
			return priorityIndex;
		}
	}// enum Priority

	private <T> Future<T> submit(Callable<T> command, int priority) {
		if (isShuttingdown) {
			throw new RejectedExecutionException();
		}
		if (null == command) {
			throw new NullPointerException("Please pass valid Callable");
		}

		Task<T> newTask = new Task<>(command, priority);

		taskWaitableQueue.enqueue(newTask);

		return newTask.getFuture();

	}

	private void initThreads(int nThreads) {
		assert 0 <= nThreads;

		for (int i = 0; i < nThreads; ++i) {
			Worker worker = new Worker();
			workers.put(worker, null);
			worker.start();
		}
	}

	private void incrementNumWorkers(int delta) {
		assert 0 <= delta;

		initThreads(delta);
	}

	private void decrementNumWorkers(int delta) {
		final int KILLER_PRIORITY = 16;
		assert 0 < delta;

		for (int i = 0; i < delta; ++i) {
			submit(Executors.callable(killer), KILLER_PRIORITY);
		}
	}

	private class Task<V> implements Comparable<Task<?>> {
		private final Callable<V> command;
		private final int priority;
		private final TaskFuture taskFuture = new TaskFuture();

		public Task(Callable<V> command, int priority) {
			assert null != command;

			this.command = command;
			this.priority = priority;
		}

		public void execute() {
			try {
				taskFuture.result = command.call();
			} catch (Exception e) {
				taskFuture.failure = e;
			} finally {
				taskFuture.isDone = true;
				taskFuture.doneLatch.countDown();
			}
		}

		public Future<V> getFuture() {
			return taskFuture;
		}

		@Override
		public int compareTo(Task<?> other) {
			return other.priority - priority;
		}

		public class TaskFuture implements Future<V> {
			private volatile V result;
			private volatile boolean isDone;
			private boolean isCancelled;
			private volatile Exception failure;
			private CountDownLatch doneLatch = new CountDownLatch(1);

			/**
			 * Attempts to cancel execution of this task. This attempt will fail if the task
			 * has already completed, has already been cancelled, or could not be cancelled
			 * for some other reason. If successful, and this task has not started when
			 * cancel is called, this task should never run. If the task has already
			 * started, then the mayInterruptIfRunning parameter determines whether the
			 * thread executing this task should be interrupted in an attempt to stop the
			 * task.
			 * 
			 * After this method returns, subsequent calls to isDone() will always return
			 * true. Subsequent calls to isCancelled() will always return true if this
			 * method returned true.
			 * 
			 * @param mayInterruptIfRunning - cues if running in-progress tasks should be
			 *                              interrupted.
			 * @return false - if the task could not be cancelled, typically because it has
			 *         already completed normally; true - otherwise
			 */
			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				boolean wasRemoved = false;

				if (isCancelled || isDone || !(wasRemoved = taskWaitableQueue.remove(Task.this))) {
					return false;
				} else if (wasRemoved) {
					isCancelled = true;
				}

				isDone = true;

				return true;
			}

			/**
			 * Waits if necessary for the computation to complete, and then retrieves its
			 * result.
			 * 
			 * @return the computed result
			 * @throws CancellationException - if the computation was cancelled
			 * @throws ExecutionException    - if the computation threw an exception
			 * @throws InterruptedException  - if the current thread was interrupted while
			 *                               waiting
			 */
			@Override
			public V get() throws InterruptedException, ExecutionException {

				try {
					return get(Long.MAX_VALUE, TimeUnit.DAYS);
				} catch (TimeoutException e) {
					throw new RuntimeException("Couldn't have happened.");
				}
			}

			/**
			 * Waits if necessary for at most the given time for the computation to
			 * complete, and then retrieves its result, if available.
			 * 
			 * @param timeout - the maximum time to wait
			 * @param unit    - the time unit of the timeout argument
			 * @return the computed result
			 * @throws CancellationException - if the computation was cancelled
			 * @throws ExecutionException    - if the computation threw an exception
			 * @throws InterruptedException  - if the current thread was interrupted while
			 *                               waiting
			 * @throws TimeoutException      - if the wait timed out
			 */
			@Override
			public V get(long timeout, TimeUnit unit)
					throws InterruptedException, ExecutionException, TimeoutException {
				if (isCancelled) {
					throw new CancellationException("Can't get cancelled task result");
				} else if (!doneLatch.await(timeout, unit)) {
					throw new TimeoutException();
				} else if (null != failure) {
					throw new ExecutionException("Failure", failure);
				}

				return result;
			}

			/**
			 * Returns true if this task was cancelled before it completed normally.
			 * 
			 * @return true if this task was cancelled before it completed
			 */
			@Override
			public boolean isCancelled() {
				return isCancelled;
			}

			/**
			 * Returns true if this task completed. Completion may be due to normal
			 * termination, an exception, or cancellation -- in all of these cases, this
			 * method will return true.
			 * 
			 * @return true if this task completed
			 */
			@Override
			public boolean isDone() {
				return isDone;
			}
		}
	}// class Task

	private class Worker extends Thread {
		private volatile boolean shouldStop = false;

		@Override
		public void run() {
			while (!shouldStop) {
				try {
					Task<?> task = taskWaitableQueue.dequeue();
					task.execute();
				} catch (InterruptedException e) {
					// keep running
				}
			}
		}
	}// class Worker
}// class ThreadPoolx