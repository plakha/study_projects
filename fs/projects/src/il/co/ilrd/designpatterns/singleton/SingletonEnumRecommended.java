package il.co.ilrd.designpatterns.singleton;

public enum SingletonEnumRecommended implements Singleton {
	SINGLETON;
}

class TestSingletonHolder {
	public static void main(String[] args) {
	//	if (SingletonEnumRecommended.SINGLETON == SingletonEnumRecommended.SINGLETON) {
		//	System.out.println("SINGLETON!");
		//}
	}
}
