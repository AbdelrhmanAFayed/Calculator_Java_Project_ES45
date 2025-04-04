/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package serial_handler;

import com.fazecast.jSerialComm.*;
import java.io.InputStream;

/**
 *
 * @author fazloka
 */
public class Serial_Handler {

    private SerialPort serialPort = null;
    private InputStream inputStream = null;
    private byte[] buffer = new byte[1024];
    private int bufferLength = 0;
    private Thread readThread;
    private boolean readError = false;


    /*
    openPort checks the available ports and chooses the first one to open
    returns False if it fails to open Port
     */
    public boolean openPort(int baudRate) {

        SerialPort[] ports = SerialPort.getCommPorts(); //get available Ports

        if (ports.length == 0) {
            System.out.println("No serial ports found.");
            return false;
        }

        serialPort = ports[0];
        serialPort.setBaudRate(baudRate);
        serialPort.setNumDataBits(8);
        serialPort.setParity(SerialPort.NO_PARITY);
        serialPort.setNumStopBits(SerialPort.ONE_STOP_BIT);

        if (serialPort.openPort()) {
            inputStream = serialPort.getInputStream(); // Get input stream
            System.out.println("Opened: " + serialPort.getSystemPortName());
            return true;
        } else {
            System.err.println("Failed to open serial port.");
            return false;
        }
    }

    /*
    ReaderThread to implemnt the runnable needed to read the data incoming in the background
     */
    private class ReaderThread implements Runnable {

        @Override
        public void run() {
            try {
                while (serialPort != null && serialPort.isOpen() && inputStream != null) {
                    if (inputStream.available() > 0) {
                        int bytesRead = inputStream.read(buffer, bufferLength, buffer.length - bufferLength);

                        if (bytesRead > 0) {
                            bufferLength += bytesRead;
                        }
                    }
                }
            } catch (Exception e) {
                readError = true; // Set error flag if reading fails to be able to ask the user to reconnect
                System.err.println("Error reading data: " + e.getMessage());
            }
        }
    }

    /*
    init method opens the port to the correct baudRate and if opened starts the reading thread
     */
    public boolean init(int baudRate) {
        if (!openPort(baudRate)) {
            return false;
        }

        inputStream = serialPort.getInputStream();
        readThread = new Thread(new ReaderThread());
        readThread.start();
        return true;
    }

    /*
    Reads the available buffered data
     */
    public synchronized char[] readBuffer() {
        if (readError) {
            return null; // Indicate failure
        }

        if (bufferLength == 0) {
            return new char[0]; // No data, return empty array
        }

        char[] data = new char[bufferLength];
        for (int i = 0; i < bufferLength; i++) {
            data[i] = (char) buffer[i]; // Convert byte to char
        }

        // Clear buffer after reading
        bufferLength = 0;

        return data;
    }

    /*
    Reads the available buffered data after removing every instance of No key pressed
     */
    public synchronized char[] readBufferFiltered() {
        if (readError) {
            return null; // Indicate failure
        }

        if (bufferLength == 0) {

            return new char[0]; // No data, return empty arr
        }

        int newLength = 0;
        char[] tempBuffer = new char[bufferLength];

        for (int i = 0; i < bufferLength; i++) {
            if (buffer[i] != 'K') {
                tempBuffer[newLength++] = (char) buffer[i]; // Convert byte to char
            }
        }

        char[] filteredData = new char[newLength];
        System.arraycopy(tempBuffer, 0, filteredData, 0, newLength);

        // Clear buffer after reading
        bufferLength = 0;

        return filteredData;
    }


    /*
    Gets the Current key pressed so The GUI can be updated if returns 'K' no key is pressed
     */
    public synchronized char getLastKeyPressed() {
        if (readError) {
            return '\0'; // Indicate failure with null character
        }

        if (bufferLength == 0) {
            return '\0'; // No data available
        }

        return (char) buffer[bufferLength - 1];
    }

    /*
    Closes the serial port and the stream
     */
    public void closePort() {
        if (serialPort != null && serialPort.isOpen()) {
            try {
                inputStream.close();
            } catch (Exception e) {
                System.err.println("Failed to close input stream.");
            }
            serialPort.closePort();
            System.out.println("Serial port closed.");
        }
    }
}
