package il.co.ilrd.logmonitor.serverside;

import java.io.IOException;

import il.co.ilrd.crud.CRUD;
//import il.co.ilrd.crud.CRUDFile;
import il.co.ilrd.crud_sql.CRUDSQL;
import il.co.ilrd.logmonitor.serverside.ServerLogProtocol.ServerTransmissionProtocol;

/**
 * 
 * @author Andrei
 *
 */
public class LogListener implements AutoCloseable {
	private ServerLogProtocol listenProtocol;
	private CRUD<String, Integer> logged;

	public LogListener(int port) {
		try {
			final String dbName = "log";
			final String tableName = "logTable";
			listenProtocol = new ServerLogProtocol(null, port, ServerTransmissionProtocol.UDP);
		//	logged = new CRUDFile("/home/student0/Desktop/Logged");
			logged =  new CRUDSQL(CRUDSQL.LOCAL_ADDR, CRUDSQL.DEFAULT_MYSQL_PORT, dbName,
					"andrei", "password", tableName);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void start() {
		while (true) {
			try {
				String message = new String(listenProtocol.receiveNextMessage());
				System.out.println("Insering to CRUD: " + message);
				logged.create(message);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] args) {
		try (

				LogListener logListener = new LogListener(4444);

		) {

			logListener.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void close() throws Exception {
		listenProtocol.close();
	}
}