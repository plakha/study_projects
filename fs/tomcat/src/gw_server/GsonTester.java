package gw_server;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.FileWriter;
import java.io.IOException;
import java.math.BigDecimal;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GsonTester {

	public static void main(String[] args) {

		// pretty print
		Gson gson = new GsonBuilder().setPrettyPrinting().create();

		Staff staff = createStaffObject();

		// Java objects to String
	//	String json = gson.toJson(staff);

		// System.out.println(json);

		// Java objects to File
		try (FileWriter writer = new FileWriter("/home/student0/Desktop/staff.json")) {
			gson.toJson(staff, writer);
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	@SuppressWarnings("unused")
	public static class Staff {

		private String name;
		private int age;
		private String[] position; // array
		private List<String> skills; // list
		private Map<String, BigDecimal> salary; // map

		public void setName(String name) {
			this.name = name;
		}

		public void setAge(int age) {
			this.age = age;
		}

		public void setPosition(String[] position) {
			this.position = position;// should do protective copying
		}

		public void setSalary(Map<String, BigDecimal> salary) {
			this.salary = salary;// should do protective copying
		}

		public void setSkills(List<String> skills) {
			this.skills = skills;
		}
	}

	private static Staff createStaffObject() {

		Staff staff = new Staff();

		staff.setName("mkyong");
		staff.setAge(35);
		staff.setPosition(new String[] { "Founder", "CTO", "Writer" });
		Map<String, BigDecimal> salary = new HashMap<>() {
			

			/**
			 * 
			 */
			private static final long serialVersionUID = 1L;

			{
				put("2010", new BigDecimal(10000));
				put("2012", new BigDecimal(12000));
				put("2018", new BigDecimal(14000));
			}
		};
		staff.setSalary(salary);
		staff.setSkills(Arrays.asList("java", "python", "node", "kotlin"));

		return staff;

	}

}
