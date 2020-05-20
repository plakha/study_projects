package il.co.ilrd.crud;

import java.io.IOException;

public class CRUDFileTest {

	public static void main(String[] args) {

		try (CRUD<String, Integer> crudFile = new CRUDFile("/home/student/Desktop/htres")) {
			crudFile.create("sargew");
			crudFile.create("qsargesrhawdse");
			crudFile.create("qsarfgse");

		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e1) {
			e1.printStackTrace();
		}

	}

}
