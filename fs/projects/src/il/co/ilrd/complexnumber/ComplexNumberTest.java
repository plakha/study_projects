package il.co.ilrd.complexnumber;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.jupiter.api.Test;
import static java.lang.System.out;

class ComplexNumberTest {
	@BeforeClass
	void beforeClass() {
		out.println("Start testing...");
	}

	@AfterClass
	void afterClass() {
		out.println("...end testing");
	}

	@Test
	void testEquals() {
		ComplexNumber comp2 = new ComplexNumber(2, 7);
		ComplexNumber comp1 = new ComplexNumber(2.0, 7.0);
		ComplexNumber comp3 = new ComplexNumber();

		assertEquals(comp1, comp2);
		assertEquals(comp1, comp1);
		assertEquals(comp2, comp2);
		assertFalse(comp1.equals(comp3));
	}
	
	@Test
	void testCompareTo() {
		ComplexNumber comp2 = new ComplexNumber(2, 7);
		ComplexNumber comp1 = new ComplexNumber(2.0, 7.0);
		ComplexNumber comp3 = new ComplexNumber();

		
		assertTrue(0 == comp2.compareTo(comp1));
		assertTrue(0 == comp1.compareTo(comp1));
		assertFalse(0 == comp3.compareTo(comp2));
		assertFalse(0 == comp3.compareTo(comp1));
	}
	
	@Test
	void testAdd() {
		ComplexNumber augend = new ComplexNumber(2.21, -7.0);
		ComplexNumber addend = new ComplexNumber(-1.11, 7.0);
		ComplexNumber expectedSum = new ComplexNumber(1.1, 0.0);
		
		ComplexNumber actualSum = augend.add(addend);
		
		out.println(actualSum);
		
		assertEquals(expectedSum, actualSum);
	}
	
	@Test
	void testSubtract() {
		ComplexNumber minuhend = new ComplexNumber(2, 7);
		ComplexNumber subtrahend = new ComplexNumber(2.0, 7.0);
		ComplexNumber difference = new ComplexNumber();
		
		assertEquals(difference, minuhend.subtract(subtrahend));
	}
	
	@Test 
	void testMultiply() {
		ComplexNumber multiplicant = new ComplexNumber(3.0, 13.0);
		ComplexNumber multiplier = new ComplexNumber(7.0, 17.0);
		ComplexNumber product = new ComplexNumber(-200, 142);
		
		assertEquals(product, multiplicant.multiply(multiplier));
	}
	
	@Test
	void testDivide() {
		ComplexNumber dividend = new ComplexNumber(1.0, 1.0);
		ComplexNumber divisor = new ComplexNumber(1.0, 1.0);
		ComplexNumber quotent = new ComplexNumber(1.0, 0.0);
		
		assertEquals(quotent, dividend.divide(divisor));
	}
	
	@Test 
	void testToString() {
		assertEquals("1.0+1.0i", (new ComplexNumber(1.0, 1.0)).toString());

		//toString of rounded sum result
		assertEquals((new ComplexNumber(1.1, 0.0)).toString(),
		((new ComplexNumber(2.21, -7.0)).add(new ComplexNumber(-1.11, 7.0))).toString());
					
	}
}//class ComplexNumberTest