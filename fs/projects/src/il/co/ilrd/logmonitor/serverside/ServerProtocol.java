package il.co.ilrd.logmonitor.serverside;

import java.io.IOException;

public interface ServerProtocol extends AutoCloseable {
	/* RETURNS NEXT UNIQUE MESSAGE, HANDLES ACKNOLEDGEMENT OF INCOMING MESSAGES */
	public byte[] receiveNextMessage() throws IOException;
}
