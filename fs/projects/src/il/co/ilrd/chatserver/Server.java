package il.co.ilrd.chatserver;

import java.io.IOException;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

/**
 * 
 * @author Andrei
 * @version 3/11/2019
 *
 */
public interface Server extends AutoCloseable{
	public void registerNewClient(Consumer<Communicator> onNewClient) ;

	public void registerNewMessage(BiConsumer<Communicator, String> onNewMessage) ;

	public void registerClientDisconnect(Consumer<Communicator> onClientDisconnect) ;

	public void start() throws IOException;
}// interface Server