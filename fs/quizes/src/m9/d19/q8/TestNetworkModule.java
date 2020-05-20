package m9.d19.q8;

public class TestNetworkModule {
	public static void main(String[] args) {
		NetworkModule networkModule = new NetworkModule();
		
		networkModule.receiveNum(1);
		System.out.println(networkModule.firstNotDuplicated());
		
		networkModule.receiveNum(2);
		System.out.println(networkModule.firstNotDuplicated());
		
		networkModule.receiveNum(2);
		System.out.println(networkModule.firstNotDuplicated());
		
		networkModule.receiveNum(3);
		System.out.println(networkModule.firstNotDuplicated());
		
		networkModule.receiveNum(3);
		System.out.println(networkModule.firstNotDuplicated());
		
		networkModule.receiveNum(4);
		System.out.println(networkModule.firstNotDuplicated());
		
		networkModule.receiveNum(1);
		System.out.println(networkModule.firstNotDuplicated());
		
		networkModule.receiveNum(1);
		System.out.println(networkModule.firstNotDuplicated());
		
		networkModule.receiveNum(1);
		System.out.println(networkModule.firstNotDuplicated());
	}
}
