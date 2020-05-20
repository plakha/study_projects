package gw_server;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

//import com.google.gson.Gson;
import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpServer;

public class GatewaySyncTest {

	private HttpServer server;
	private HttpContext context;

	public GatewaySyncTest() throws IOException {
		server = HttpServer.create(new InetSocketAddress(4444), 0);
		context = server.createContext("/aa");
		context.setHandler(this::handleRequest);
	}

	public void start() {
		server.start();
	}
	
	public void stop(int delay) {
		server.stop(delay);
	}
	
	public static void main(String[] args) {
		try {
			GatewaySyncTest gw = new GatewaySyncTest();
			gw.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private void handleRequest(HttpExchange exchange) throws IOException {
		String response = "Hello, hello";
		exchange.sendResponseHeaders(200, response.getBytes().length);
		try (

				OutputStream outstream = exchange.getResponseBody();

		) {
			outstream.write(response.getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

}
