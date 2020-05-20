package il.co.ilrd.vendingmachine;

import java.util.ArrayList;
import java.util.List;

public class VendingMachine {
	private int balance = 0;
	private State currentState = State.INIT;
	private List<Product> stock = new ArrayList<>();
	private Monitor monitor;
	private static final int DEFAULT_TIMEOUT = 3;
	private int timeout = DEFAULT_TIMEOUT;
	private volatile int timeCount = 0;
	private Metronome metronome = new Metronome(this);
	private Thread metronomeThread;

	public VendingMachine(Monitor monitor) {
		this.monitor = monitor;
	}

	public VendingMachine(Monitor monitor, int timeout) {
		this(monitor);
		this.timeout = timeout;
	}

	public VendingMachine(Monitor monitor, int timeout, Product... products) {
		this(monitor, timeout);
		for (Product item : products) {
			stock.add(item);
		}
	}

	private enum State {
		INIT {
			final String MESSAGE = "Vending Machine off. Please contact service.";

			@Override
			public void chooseProduct(VendingMachine machine, String product) {
				machine.getMonitor().print(MESSAGE);
			}

			@Override
			public void insertMoney(VendingMachine machine, int sum) {
				machine.getMonitor().print(MESSAGE + "Returning " + sum);
			}

			@Override
			public void start(VendingMachine machine) {
				machine.initMetronomeThread();

				machine.setCurrentState(WAIT_MONEY);
			}
		}, // INIT

		WAIT_MONEY {
			@Override
			public void chooseProduct(VendingMachine machine, String product) {
				machine.getMonitor().print("Please insert money. ");
			}

			@Override
			public void insertMoney(VendingMachine machine, int sum) {
				if (0 > sum) {
					machine.getMonitor().print(
							"Caution! " + "Breaking into the machime may lead to injury!" + " Calling the security");
				} else {
					machine.getMonitor().print("Inserted " + sum);
					machine.addToBalance(sum);

					machine.setCurrentState(WAIT_CHOICE);
				}
			}
		}, // WAIT_MONEY

		WAIT_CHOICE {

			private void treatNullInput(VendingMachine machine) {
				machine.getMonitor().print("Nothing chosen." + "Returning money " + machine.getBalance());
				machine.setBalance(0);
				machine.resetTimeCount();
				machine.setCurrentState(WAIT_MONEY);
			}

			@Override
			public void chooseProduct(VendingMachine machine, String name) {
				int price = 0;
				final int currentBalance = machine.getBalance();

				if (null == name) {
					treatNullInput(machine);
					return;
				}

				final Product product = machine.productFromStock(name);
				if (null == product) {
					machine.getMonitor().print(name + " not in stock");
					machine.getMonitor().print("Returning money: " + currentBalance);
				} else {
					price = product.getPrice();
					if (currentBalance < price) {
						price = 0;
						machine.getMonitor().print("Not enough balance");
					} else {
						machine.getMonitor().print("Vending " + name);
					}

					machine.getMonitor().print("Money Collected: " + price);

					machine.addToBalance(-price);
					machine.getMonitor().print("Change Returned: " + machine.getBalance());
				}

				machine.setBalance(0);
				machine.resetTimeCount();
				machine.setCurrentState(WAIT_MONEY);
			}// chooseProduct()

			@Override
			public void insertMoney(VendingMachine machine, int sum) {
				assert 0 < sum;

				machine.getMonitor().print("Inserted " + sum);
				machine.addToBalance(sum);
			}

			@Override
			public void tick(VendingMachine machine) {
				machine.incrementTimeCount();
				if (machine.timedOut()) {
					machine.resetTimeCount();
					machine.getMonitor().print("Timed out! Returning money: " + machine.getBalance());
					machine.setBalance(0);

					machine.setCurrentState(WAIT_MONEY);
				}
			}
		};// WAIT_CHOICE

		public void stop(VendingMachine machine) {
			machine.getMonitor().print("Returning " + machine.getBalance() + ". Stopping the Vending Machine");
			machine.setBalance(0);

			Thread metronomeThread = machine.getMetronomeThread();
			if (null != metronomeThread) {
				metronomeThread.interrupt();
			}
			machine.setCurrentState(INIT);
		}

		public void start(VendingMachine machine) {
		}

		public void tick(VendingMachine machine) {
		}

		abstract public void chooseProduct(VendingMachine machine, String product);

		abstract public void insertMoney(VendingMachine machine, int sum);
	}// enum State

	public int getTimeout() {
		return timeout;
	}

	public int getBalance() {
		return balance;
	}

	public void insertMoney(int sum) {
		currentState.insertMoney(this, sum);
	}

	public void start() {
		currentState.start(this);
	}

	public void stop() {
		currentState.stop(this);
	}

	public void addProduct(Product product) {
		stock.add(product);
	}

	public void chooseProduct(String productName) {
		currentState.chooseProduct(this, productName);
	}

	Product productFromStock(String name) {
		for (Product runner : stock) {
			if (name.equals(runner.getName())) {
				return runner;
			}
		}

		return null;
	}

	void setTimerThread(Thread metronomeThread) {
		this.metronomeThread = metronomeThread;
	}

	void initMetronomeThread() {
		metronomeThread = new Thread(metronome);
		metronomeThread.setDaemon(true);
		metronomeThread.start();
	}

	private Thread getMetronomeThread() {
		return metronomeThread;
	}

	void tick() {
		currentState.tick(this);
	}

	private void setBalance(int balance) {
		this.balance = balance;
	}

	private void addToBalance(int sum) {
		balance += sum;
	}

	private Monitor getMonitor() {
		return monitor;
	}

	private void incrementTimeCount() {
		++timeCount;
	}

	private void resetTimeCount() {
		timeCount = 0;
	}

	private boolean timedOut() {
		return timeout == timeCount;
	}

	private void setCurrentState(State currentState) {
		this.currentState = currentState;
	}

	@Override
	public final void finalize() {
	}
}// class VendingMachine
