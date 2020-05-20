package il.co.ilrd.hashmap;

import java.util.List;

/**
 * Note item 28 of Effective java: prefer lists to arrays
 * 
 * @author student
 *
 */
class ArrayVList {
	public static void main(String[] args) {
		System.out.println("awsdg");
		@SuppressWarnings("unchecked")
		List<Integer>[] listsArr = new List[10];
		Object[] ref = listsArr;
		ref[0] = new Object();//Array StoreException

		// listsArr[0] = new ArrayList<>();
		// listsArr[1].add(1);
		// List<List<Integer>> listsList = new ArrayList<>();

		// listsArr[1] = new ArrayList<Character>(); //doesn't complile
	}
}
