/**
 * 
 */
package il.co.ilrd.designpatterns.singleton;

/**
 * @author student
 * @version 8/9/2019 "Classic" thread-safe singleton. Not efficient (!) because
 *          the sync is only needed on the first getCountInstance() invocation;
 *          and sync is expensive!
 */

public class Singleton1Sync implements Singleton {
	private static Singleton singleInstance;
	private static int countInstances;

	private Singleton1Sync() {
		++countInstances;
	}

	public synchronized static Singleton getInstance() {
		return null == singleInstance ? singleInstance = new Singleton1Sync() : singleInstance;
	}

	public static int getCountInstances() {
		return countInstances;
	}
}

class TestSingleton1Sync {
	public static void main(String[] args) {
		Singleton first = Singleton1Sync.getInstance();
		Singleton second = Singleton1Sync.getInstance();

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

		if (1 == Singleton1Sync.getCountInstances()) {
			System.out.println("SIngleton!!!");
		} else {
			System.out.println("No!!!");
			System.out.println(Singleton1Sync.getCountInstances());
		}

	}
}
