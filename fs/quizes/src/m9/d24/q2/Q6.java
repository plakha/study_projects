package m9.d24.q2;

import java.util.ArrayList;
import java.util.List;

public class Q6 {

	public static void foo(List<Object> list) {
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static void main(String[] args) {
		List<String> strList = null;
		List rawList = null;
		List<Object> objList = null;
		List<?> list = null;
		List<?> list1 = null;

		//foo(strList);
		foo(rawList);
		foo((List<Object>)rawList);
		foo(objList);
		
		rawList = strList;
		rawList = objList;
		objList = rawList;
		strList = rawList;
		list = rawList;
		list = strList;
		//strList = list;
		list = list1;
		rawList = list;
		list = rawList;
		
		List<Object> names = new ArrayList<>();
		names.add("John");
		names.add("Mary");
		names.add(Boolean.FALSE);
	}
}
