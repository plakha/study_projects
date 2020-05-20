package playground;

import java.util.concurrent.Callable;

public class Closure {
	static Callable<Integer> getCounterRunner() {
		int cnt = 0;
		
		return new Callable<Integer>() {
			@Override
			public Integer call() throws Exception {
				return cnt;
			}
			
		};
	}
}
