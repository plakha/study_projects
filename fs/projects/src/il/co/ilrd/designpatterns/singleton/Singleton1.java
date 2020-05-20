/**
 * 
 */
package il.co.ilrd.designpatterns.singleton;

/**
 * @author student
 * @version 8/9/2019
 * "Classic" not thread-safe singleton,
 * that uses getInstance static factory method. Lazy instantiation (on first use)
 * Its not thread-safe, 
 * because if two threads will invoke getInstance() at the same time, 
 * for the first time, two instances may be created. In fact, in the worst case, 
 * the number of instances may be as great as the number of threads.
 *
 */
public class Singleton1 implements Singleton {
	private static Singleton singleInstance;
	private static int countInstances;
	private Singleton1() {
		++countInstances;
	}
	
	public static Singleton getInstance() {
		return null == singleInstance 
					? singleInstance = new Singleton1() 
					: singleInstance;
	}

	public static int getCountInstances() {
		return countInstances;
	}
}

class TestSingleton1 {
	public static void main(String[] args) {
		Singleton first = Singleton1.getInstance();
		Singleton second = Singleton1.getInstance();
		
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
		
		if (1 == Singleton1.getCountInstances()) {
			System.out.println("SIngleton!!!");
		} else {
			System.out.println("No!!!");
			System.out.println(Singleton1.getCountInstances());
		}

	}
}