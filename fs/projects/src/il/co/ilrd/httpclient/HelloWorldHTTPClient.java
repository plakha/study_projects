package il.co.ilrd.httpclient;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.http.HttpClient;
import java.net.http.HttpClient.Version;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.http.HttpResponse.BodyHandlers;

public class HelloWorldHTTPClient {
	public static void main(String[] args) {
		HttpClient client = HttpClient.newBuilder().version(Version.HTTP_1_1).build();

		HttpRequest request = null;
		try {
			request = HttpRequest.newBuilder().GET().uri(new URI("http://info.cern.ch/hypertext/README.html")).build();
		} catch (URISyntaxException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		HttpResponse<String> response = null;
		try {
			response = client.send(request, BodyHandlers.ofString());
		} catch (IOException | InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		@SuppressWarnings("unused")
		int statusCode = response.statusCode();
		String body = response.body();
		
		System.out.println(body);
	}
}
