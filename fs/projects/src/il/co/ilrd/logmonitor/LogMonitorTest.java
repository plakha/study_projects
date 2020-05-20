package il.co.ilrd.logmonitor;

import java.io.IOException;

import il.co.ilrd.crud.CRUD;
//import il.co.ilrd.crud.CRUDFile;
import il.co.ilrd.crud_sql.CRUDSQL;
import il.co.ilrd.logmonitor.client_side.LogMonitor;

public class LogMonitorTest {
	public static void main(String[] args) {

		String dbName = "log";
		String tableName = "logTable";
		LogMonitor logMonitor = new LogMonitor("/var/log/syslog");
		try (

				//CRUD<String, Integer> outputFile = new CRUDFile("/home/student0/Desktop/crud11");
				CRUD<String, Integer> outputSQL = new CRUDSQL(CRUDSQL.LOCAL_ADDR, CRUDSQL.DEFAULT_MYSQL_PORT, dbName,
						"andrei", "password", tableName);) {
			logMonitor.registerEventHandler(entry -> {
			//	outputFile.create(entry);
				System.out.println(entry);
				outputSQL.create(entry);
			});
			logMonitor.registerExceptionHandler((Exception e) -> System.out.println(e));
			logMonitor.start();
//			Thread.sleep(10000);
//			logMonitor.stop();
		} catch (IOException e) {
		} catch (Exception e) {
		}
	}

}
