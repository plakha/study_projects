package iot.log_client;

import java.io.IOException;
import java.io.OutputStream;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

import com.sun.net.httpserver.HttpExchange;

public class HTTPClientAdapter {
	private String url;
	private final HttpClient connection = HttpClient.newBuilder().build();

	public HTTPClientAdapter(String url) {
		this.url = url;
	}

	public int sendPost(String message) throws IOException, InterruptedException {
		HttpRequest request = HttpRequest.newBuilder(URI.create(url)).POST(HttpRequest.BodyPublishers.ofString(message))
				.build();
		HttpResponse<String> response = connection.send(request, HttpResponse.BodyHandlers.ofString());

		System.out.println(response.body());

		return response.statusCode();
	}

	@SuppressWarnings("unused")
	private void handleRequest(HttpExchange exchange) {
		String response = "Hello, hello";

		try (

				OutputStream outstream = exchange.getResponseBody();

		) {
			outstream.write(response.getBytes());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}
