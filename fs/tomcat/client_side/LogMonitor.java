package il.co.ilrd.logmonitor.client_side;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.ClosedWatchServiceException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.LinkedList;
import java.util.Queue;
import java.util.function.Consumer;
import static java.nio.file.StandardWatchEventKinds.ENTRY_MODIFY;

/**
 * 
 * @author Andrei
 *
 */
public class LogMonitor {
	private final Queue<Consumer<Exception>> exceptionHandlers = new LinkedList<>();
	private final Queue<Consumer<String>> eventHandlers = new LinkedList<>();
	private WatchService watchService;
	private final String source;
	private volatile boolean shouldStop;
	private Thread loggerThread;
	private final File sourceFile;

	public LogMonitor(String source) {
		this.source = source;
		sourceFile = new File(source);
	}

	public void start() throws IOException {
		checkIfStarted();
		if (!sourceFile.isFile()) {
			throw new FileNotFoundException();
		}
		shouldStop = false;
		watchService = Paths.get(source).getParent().getFileSystem().newWatchService();
		Paths.get(source).getParent().register(watchService, ENTRY_MODIFY);
		(loggerThread = new LoggerThread()).start();
	}

	public void registerEventHandler(Consumer<String> onEvent) {
		checkIfStarted();
		eventHandlers.offer(onEvent);
	}

	public void registerExceptionHandler(Consumer<Exception> onException) {
		checkIfStarted();
		exceptionHandlers.offer(onException);
	}

	public void stop() throws IOException, InterruptedException {
		if (null == watchService) {
			throw new IllegalStateException("not started");
		}
		shouldStop = true;
		watchService.close();
		loggerThread.join();

	}

	private void checkIfStarted() throws IllegalStateException {
		if (null != watchService) {
			throw new IllegalStateException("already started");
		}
	}

	private class LoggerThread extends Thread {
		private WatchKey watchKey;
		private long offset = 0;// first read from the start of the monitored log

		@Override
		public void run() {
			while (!shouldStop) {
				try {
					watchKey = watchService.take();
				} catch (ClosedWatchServiceException e) {
					for (Consumer<Exception> exceptionHandler : exceptionHandlers) {
						exceptionHandler.accept(e);
					}
					return;
				} catch (InterruptedException e) {
					for (Consumer<Exception> exceptionHandler : exceptionHandlers) {
						exceptionHandler.accept(e);
					}
					return;
				}

				for (WatchEvent<?> event : watchKey.pollEvents()) {
					// ENTRY_MODIFY event context is a Path
					if (((Path) event.context()).endsWith(sourceFile.getName())) {
						updateNewEntries();
						break;
					}
				}
				watchKey.reset();
			} // while (!shouldStop)
		}

		private void updateNewEntries() {
			try (RandomAccessFile reader = new RandomAccessFile(sourceFile, "r")) {
				String entry = null;
				reader.seek(offset);
				while (null != (entry = reader.readLine())) {
					for (Consumer<String> eventHandler : eventHandlers) {
						eventHandler.accept(entry);
					}
					offset += entry.length();
				}
			} catch (IOException e) {
				for (Consumer<Exception> exceptionHandler : exceptionHandlers) {
					exceptionHandler.accept(e);
				}
			}
		}
	}// class LoggerThread
}