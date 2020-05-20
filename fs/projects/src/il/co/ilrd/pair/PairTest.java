package il.co.ilrd.pair;

import static org.junit.Assert.*;
import static il.co.ilrd.pair.Pair.of;
import static il.co.ilrd.pair.Pair.minMax;


import org.junit.Test;

public class PairTest {

	@Test
	public void testEqualsHashCode() {
		Pair<Integer, Integer> p = of(null, null);
		Pair<Integer, Integer> p1 = of(null, null);
		assertEquals(p, p1);
		assertEquals(p.hashCode(), p1.hashCode());
		
		p = of(1, 2);
		p1 = of(1, 2);
		assertEquals(p, p1);
		assertEquals(p.hashCode(), p1.hashCode());
		
		p = of(1, 2);
		p1 = of(2, 1);
		assertNotEquals(p, p1);
		
		p = of((Integer)1, 2);
		p1 = of(null, null);
		assertNotEquals(p, p1);
		
		p = of((Integer)1, null);
		p1 = of(null, null);
		assertNotEquals(p, p1);	
	}
	
	@Test
	public void testMinMax() {
		Integer[] arr = {8,9,8,56,7,-9};
		
		Pair<Integer, Integer> result = minMax(arr);
		Pair<Integer, Integer> expected = of(-9, 56);
		
		assertEquals(result, expected);
		
		Integer[] arr1 = {8,9, 8,56,7,-9, 100};
		result = minMax(arr1);
		expected = of(-9, 100);
		
		assertEquals(result, expected);

	}
}
