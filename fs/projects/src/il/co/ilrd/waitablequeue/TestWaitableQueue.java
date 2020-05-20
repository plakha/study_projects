package il.co.ilrd.waitablequeue;

public class TestWaitableQueue {
	private static WaitableQueue<String> wt1 = new WaitableQueueConditionVar<String>();
	private static final int NUM_ELEMENTS = 5;

	public static void main(String[] args) {
		Thread producer = new Thread(() -> {
			wt1.enqueue("a");
			wt1.enqueue("b");
			wt1.enqueue("c");
			wt1.enqueue("d");
			wt1.enqueue("e");
		});

		Thread consumer = new Thread(() -> {
			for (int i = 0; NUM_ELEMENTS > i; ++i) {
				try {
					System.out.println(wt1.dequeue());
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
		producer.start();
		
		consumer.start();
		wt1.remove("e");
		
		try {
			producer.join();
			consumer.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
