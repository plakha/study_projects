package iot.log_client;

import java.io.IOException;
import iot.log_client.HTTPClientAdapter;
import il.co.ilrd.logmonitor.client_side.LogMonitor;

public class HTTPLogMonitor {
	
	public static void main(String[] args) {
		LogMonitor logMonitor = new LogMonitor("/var/log/syslog");
		HTTPClientAdapter adapter = new HTTPClientAdapter("http://localhost:8080/IOT/LogToSQLServlet");
		logMonitor.registerEventHandler((String entry) -> {
			System.out.println(entry);
			try {
				adapter.sendPost(entry);
			} catch (IOException e1) {
				e1.printStackTrace();
			} catch (InterruptedException e1) {
				e1.printStackTrace();
			}
		});

		logMonitor.registerExceptionHandler((Exception e) -> System.out.println(e));
		try {
			logMonitor.start();
		} catch (IOException e1) {
			e1.printStackTrace();
		}

	}
}
