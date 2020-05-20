package il.co.ilrd.chatserver;

import java.net.ProtocolException;

/**
 * 
 * @author Andrei
 * @version 3/11/2019
 *
 * 
 */
public class ChatProtocol {
	private static final String delimiter = "$#";

	public static String encode(String message) {
		return delimiter + message + delimiter;
	}

	public static String decode(String encodedMessage) throws ProtocolException {
		if (encodedMessage.startsWith(delimiter) && encodedMessage.endsWith(delimiter)) {
			return encodedMessage.substring(delimiter.length(), encodedMessage.length() - delimiter.length());
		} else {
			throw new ProtocolException();
		}
	}
}
