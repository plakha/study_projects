package il.co.ilrd.designpatterns.singleton;
/*Lazy initialization recommended by Effective Java
 * 
 */
public class SingletonJavaLazyRecommended implements Singleton {
	private SingletonJavaLazyRecommended() {}
	
	private static class SingletonHolder implements Singleton {
		public static Singleton INSTANCE
						= new SingletonJavaLazyRecommended();//why not final??

	}
	
	public static Singleton getInstance() {
		return SingletonHolder.INSTANCE;
	}
}

class TestSingletonJavaLazyRecommended {
	Singleton sin1 = SingletonJavaLazyRecommended.getInstance();
	Singleton sin2 = SingletonJavaLazyRecommended.getInstance();
}