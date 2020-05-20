package m9.d19.q8;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

public class NetworkModule {
	private Map<Long, Long> duplicates = new HashMap<>();
	private Map<Long, Long> distincts = new LinkedHashMap<>();//the iteration on LinkedHashMap is in the order of insertion

	void receiveNum(long input) {
		if (!duplicates.containsKey(input)) {
			distincts.put(input, input);
			duplicates.put(input, input);
		} else {
			distincts.remove(input);
		}
	}

	long firstNotDuplicated() {
		if (distincts.isEmpty()) {
			return 0L;
		}

		return distincts.entrySet().iterator().next().getValue();
	}
}

/*

public class NetworkModule {
	private Map<Long, Long> duplicates = new HashMap<>();
	private LinkedList<Long> distincts = new LinkedList<>();// consider hashList to remove in O(1)

	void receiveNum(long input) {
		if (!duplicates.containsValue(input)) {
			distincts.add(input);
			duplicates.put(input, input);
		} else {
			distincts.remove(input);
		}
	}

	long firstNotDuplicated() {
		if (distincts.isEmpty()) {
			return 0L;
		}

		return distincts.getFirst();
	}
}


*/