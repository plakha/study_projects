package il.co.ilrd.vendingmachine;

public class Test {

	public static void main(String[] args) {
		VendingMachine machine = new VendingMachine(new VendingMachineMonitorImpl());
		Product coke = new Product("coke", 3);
		machine.stop();

		machine.addProduct(coke);
		machine.start();
		machine.insertMoney(4);

		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
		}

		machine.chooseProduct("coke");
		machine.chooseProduct("coke");

		machine.stop();
		machine.stop();

	}

	private static class VendingMachineMonitorImpl implements Monitor {
		public void print(String message) {
			System.out.println(message);
		}
	}// class VendingMachineMonitorImpl
}// class Test
