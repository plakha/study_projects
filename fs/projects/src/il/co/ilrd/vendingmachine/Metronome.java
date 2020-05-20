package il.co.ilrd.vendingmachine;

class Metronome implements Runnable {
	final VendingMachine machine;
	private final int SEC = 1000;

	Metronome(VendingMachine machine) {
		this.machine = machine;
	}

	@Override
	public void run() {
		while (true) {
			if (Thread.interrupted()) {
				return;
			}
			try {
				Thread.sleep(SEC);
			} catch (InterruptedException e) {
				return;
			}
			machine.tick();
		}
	}
}// class Metronome