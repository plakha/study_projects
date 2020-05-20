package m9.d5.q2;

public class Q2 {
	public static int sizeMaxIdMatrixFromUpLeft(int[][] matrix) {
		final int DIMENSION = matrix.length;
		int retval = 0;
		
		for(int i = 0; DIMENSION > i; ++i) {
			if (1 == matrix[i][i]
			 &&	allHorizontalZeros(matrix, i)
			 && allVerticalZeros(matrix, i)) {
				++retval;
			} else {
				break;
			}
		}
		return retval;
	}

	private static boolean allHorizontalZeros(int[][] matrix, int diagonal) {
		for (int i = 0; i < diagonal; ++i) {
			if (0 != matrix[diagonal][i]) {
				return false;
			}
		}
		return true;
	}
	
	private static boolean allVerticalZeros(int[][] matrix, int diagonal) {		
		for (int i = 0; i < diagonal; ++i) {
			if (0 != matrix[i][diagonal]) {
				return false;
			}
		}
			
		return true;	
	}
	
	public static void main(String[] args) {
		int[][] matrix = {{1, 0 , 3}, {0, 1, 2}, {3, 1, 1}};
		
		System.out.println(sizeMaxIdMatrixFromUpLeft(matrix));
	}
}