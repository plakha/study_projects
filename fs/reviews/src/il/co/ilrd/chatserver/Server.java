package il.co.ilrd.chatserver;

import java.util.function.BiConsumer;
import java.util.function.Consumer;

public interface Server {
	public void start();
	public void stop();
	public void registerNewMessage(BiConsumer<ComObj, String> onNewMessage);
	public void registerClientDisconnect(Consumer<ComObj> onClientDisconnect);
	public void registerNewClient(Consumer<ComObj> onNewClient);
}
