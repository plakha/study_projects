package leetcode;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ZeroEvenOdd {
	private final int n;
	private volatile int counter = 1;

	// private final Semaphore printZero = new Semaphore(1);
	private final Lock printLock = new ReentrantLock();

	private final Condition zeroCondition = printLock.newCondition();
	private final Condition oddCondition = printLock.newCondition();
	private final Condition evenCondition = printLock.newCondition();

	private volatile boolean shouldZero = true;
	private volatile boolean shouldOdd;
	private volatile boolean shouldEven;

	public ZeroEvenOdd(int n) {
		this.n = n;
	}

	// printNumber.accept(x) outputs "x", where x is an integer.
	public void zero() throws InterruptedException {
		while (true) {
			try {
				printLock.lock();
				if (n <= counter) {
					//++counter; 
					return;
				}
				while (!shouldZero) {
					zeroCondition.await();
				}
	
				shouldZero = false;
				//printNumber.accept(0);
				System.out.print(0);
				if (0 == counter % 2) {
					shouldEven = true;
					evenCondition.signalAll();
	
				} else {
					shouldOdd = true;
					oddCondition.signalAll();
				}
			} catch (Exception e) {
	
			} finally {
				printLock.unlock();
			}
		}
	}

	public void odd() throws InterruptedException {
		while (true) {
			try {
				printLock.lock();
				if (n < counter) {
					return;
				}

				while (!shouldOdd) {
					oddCondition.await();
				}
				assert 0 != counter % 2;

				shouldOdd = false;
				//printNumber.accept(counter++);
				System.out.print(counter++);

				shouldZero = true;
				zeroCondition.signalAll();

			} catch (Exception e) {

			} finally {
				printLock.unlock();
			}
		}
	}

	public void even() throws InterruptedException {
		while (true) {
			try {
				printLock.lock();
				if (n < counter) {
					return;
				}

				while (!shouldEven) {
					evenCondition.await();
				}
				assert 0 == counter % 2;

				shouldEven = false;
				//printNumber.accept(counter++);
				System.out.print(counter++);

				shouldZero = true;
				zeroCondition.signalAll();

			} catch (Exception e) {

			} finally {
				printLock.unlock();
			}
		}
	}
	
	public static void main(String[] args) {
		ZeroEvenOdd zeo = new ZeroEvenOdd(10);
		
		Thread zero = new Thread(new Runnable() {
			
			@Override
			public void run() {
				try {
					zeo.zero();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		
		Thread odd = new Thread(new Runnable() {
			
			@Override
			public void run() {
				try {
					zeo.odd();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		
		Thread even = new Thread(new Runnable() {
			
			@Override
			public void run() {
				try {
					zeo.even();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		
		even.start();
		odd.start();
		zero.start();
		
		try {
			even.join();
			odd.join();
			zero.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
