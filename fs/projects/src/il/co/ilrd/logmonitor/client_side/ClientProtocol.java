package il.co.ilrd.logmonitor.client_side;

import java.io.IOException;
import java.net.ProtocolException;

public interface ClientProtocol extends AutoCloseable {
	public void sendData(byte[] data) throws IOException, ProtocolException;
}
