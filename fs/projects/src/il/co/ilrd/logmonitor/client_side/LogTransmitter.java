package il.co.ilrd.logmonitor.client_side;

import java.io.IOException;
import java.net.ProtocolException;

import il.co.ilrd.logmonitor.client_side.ClientLogProtocol.ClientTransmissionProtocol;

/**
 * 
 * @author Andrei
 *
 */
public class LogTransmitter {
	private final LogMonitor logMonitor;

	public LogTransmitter(String log) {
		logMonitor = new LogMonitor(log);
	}

	public void start() {
		try (

				ClientLogProtocol transmitProtocol = new ClientLogProtocol("127.0.0.1", 4444,
						ClientTransmissionProtocol.UDP);

		) {

			logMonitor.registerEventHandler(string -> {
				try {
					transmitProtocol.sendData(string.getBytes());
				} catch (ProtocolException e1) {
					e1.printStackTrace();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
			});

			logMonitor.registerExceptionHandler(e -> System.out.println("LogMonitor :" + e));

			try {
				logMonitor.start();
				System.out.println("Started logMonitor");
			} catch (IOException e) {
				System.err.print("LogMonitor fail");
				e.printStackTrace();
			}
			Thread.sleep(Long.MAX_VALUE);
		} catch (Exception e1) {
			e1.printStackTrace();
		}
	}

	public static void main(String[] args) {
		new LogTransmitter("/var/log/syslog").start();
	}
}
