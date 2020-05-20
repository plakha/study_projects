/**
* WeakReferncing helps prevent OutOfMemory error
*
*/
import java.util.*; //List
import java.lang.*; //sleep()
import java.lang.ref.*;

class ListOfArrays {
	private final int N_OF_ARRAYS = 1000000000;
	private final int N_OF_ARR_MEMBS = 100000;

	List listOfArrays()
		/* throws InterruptedException */ {
		List<WeakReference<Integer[]>> listOfArrays = new ArrayList<>();

		for (int i = 0; N_OF_ARRAYS > i; ++i) {
			WeakReference<Integer[]> array = 
					new WeakReference<Integer[]>(new Integer[N_OF_ARR_MEMBS]);

            listOfArrays.add(i, array);
			try {
				Thread.sleep(1);
			}
			catch (InterruptedException e) {
				System.out.println(e);
			}

			System.out.println(Runtime.getRuntime().freeMemory());

		}

		return listOfArrays;
	}

	public static void main(String[] args) {
		ListOfArrays testHeap = new ListOfArrays();
		
		List newList = testHeap.listOfArrays();
	}
}