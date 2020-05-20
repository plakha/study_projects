package il.co.ilrd.designpatterns.singleton;

/*still lazy instatntiation. Thread safe at that!
 * (Without volatile keyword won't be thread safe! According to javadoc - because of memory caching;
 * according to www.learn4master.com/design-pattern/java-singleton-pattern ,
 * because of compiler optimizations - I think oracle javadoc guys are correct) 
 * 
 * 
 */
public class Singleton1DoubleChecked implements Singleton {
	private volatile static Singleton singleInstance;
	private static int countInstances;//don't include in actual code!!

	private Singleton1DoubleChecked() {
		++countInstances;
	}
	
	public static Singleton getInstance() {
		
		if (null == singleInstance) {
			synchronized (Singleton.class) {
				if (null == singleInstance) {
					singleInstance = new Singleton1DoubleChecked();
				}
			}
		}
		return singleInstance;
	}
	
	public static int getCountInstances() {
		return countInstances;
	}
}

class TestSingleton1DoubleChecked {
	public static void main(String[] args) {
		Singleton first = Singleton1DoubleChecked.getInstance();
		Singleton second = Singleton1DoubleChecked.getInstance();
		
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
		
		if (1 == Singleton1DoubleChecked.getCountInstances()) {
			System.out.println("SIngleton!!!");
		} else {
			System.out.println("No!!!");
			System.out.println(Singleton1DoubleChecked.getCountInstances());
		}

	}
}
