/**
* 
*
*/
import java.util.*; //List
import java.lang.*; //sleep()

class ListOfArrays {
	private final int N_OF_ARRAYS = 100000000;
	private final int N_OF_ARR_MEMBS = 100000;

	List listOfArrays()
		/* throws InterruptedException */ {
		List<Integer[]> listOfArrays = new ArrayList<Integer[]>();

		for (int i = 0; N_OF_ARRAYS > i; ++i) {
			Integer array[] = new Integer[N_OF_ARR_MEMBS];
		
			listOfArrays.add(i, array);
			try {
				Thread.sleep(1);
			}
			catch (InterruptedException e) {
				System.out.println(e);
			}

			//array = null; //setting "block-local" array to null doesn't prevent OutOfMemory error
			//listOfArrays.set(i, null);//prevents OutOfMemory error

			System.out.println(Runtime.getRuntime().freeMemory());

		}

		return listOfArrays;
	}

	public static void main(String[] args) {
		ListOfArrays testHeap = new ListOfArrays();
		
		List newList = testHeap.listOfArrays();
	}
}
