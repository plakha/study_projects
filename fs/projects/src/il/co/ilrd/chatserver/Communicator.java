package il.co.ilrd.chatserver;

import java.io.IOException;

/**
 * 
 * @author Andrei
 * @version 3/11/2019
 *
 */
public interface Communicator {
	public void handleMessage(String message) throws IOException;
}
