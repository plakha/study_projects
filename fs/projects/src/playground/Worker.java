package playground;

public class Worker extends Thread {
	@Override
	public void interrupt() {
		System.out.println("interrupt");
	}

	@Override
	public void run() {
		System.out.println("run");
		Thread.currentThread().interrupt();
		System.out.println("dsadsa");
	}
	
	@SuppressWarnings("unused")
	static private class Nested{
		
		private class Inner{
			
		}
	}
	
	public static void main(String[] args) {
	
		System.out.println("main");
		new Worker().start();
	}
}