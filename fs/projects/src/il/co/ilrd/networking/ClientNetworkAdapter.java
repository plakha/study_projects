package il.co.ilrd.networking;

import java.io.IOException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

public interface ClientNetworkAdapter extends AutoCloseable{
	public void send(byte[] data) throws IOException;

	public long testTimeout(int maxTimeoutMillis);

	public byte[] receive(int maxBytesBuf, long timeout, TimeUnit timeUnit) throws IOException, TimeoutException;

//	/**
//	 * blocks for a default time
//	 * 
//	 * @return the receibed data as byre array
//	 */
//	public byte[] receive() throws IOException, TimeoutException;
}
