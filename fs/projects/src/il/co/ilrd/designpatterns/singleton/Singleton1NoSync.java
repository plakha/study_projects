/**
 * 
 */
package il.co.ilrd.designpatterns.singleton;

/**
 * @author student
 * @version 8/9/2019
 * Still not thread-safe singleton. 
 * Why isn't it thread safe? 
 * While each time the work is on the same copy of instance reference, 
 * the problem is the same as with the first one.
 * That is so even if we make each thread call getInstance() two times. 
 */

public class Singleton1NoSync implements Singleton {
	private volatile static Singleton singleInstance;
	private static int countInstances;
	
	private Singleton1NoSync() {
		++countInstances;
	}
	
	public static Singleton getInstance() {
		return null == singleInstance 
					? singleInstance = new Singleton1NoSync() 
					: singleInstance;
	}

	public static int getCountInstances() {
		return countInstances;
	}
}

class TestSingleton1NoSync {
	public static void main(String[] args) {
		Singleton first = Singleton1NoSync.getInstance();
		Singleton second = Singleton1NoSync.getInstance();
		
		if (first == second) {
			System.out.println("Singleton!");
		} else {
			System.out.println("No!");
		}
		
		if (first.equals(second)) {
			System.out.println("Singleton!!");
		} else {
			System.out.println("No!!");
		}
		
		if (1 == Singleton1NoSync.getCountInstances()) {
			System.out.println("SIngleton!!!");
		} else {
			System.out.println("No!!!");
			System.out.println(Singleton1NoSync.getCountInstances());
		}

	}
}
