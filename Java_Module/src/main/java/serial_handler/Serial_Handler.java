/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package serial_handler;

import com.fazecast.jSerialComm.*;
import java.io.IOException;
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
    private char lastKey;

    /*
    openPort checks the available ports and chooses the first one to open
    returns False if it fails to open Port
     */
    public boolean openPort(int baudRate) {
        SerialPort[] ports = SerialPort.getCommPorts();

        if (ports.length == 0) {
            System.out.println("No serial ports found.");
            return false;
        }

        for (SerialPort port : ports) {
            String name = port.getSystemPortName();

            if (name.contains("ttyUSB") || name.startsWith("COM")) {
                serialPort = port;
                break;
            } else if (serialPort == null) {
                serialPort = port;
            }
        }

        if (serialPort == null) {
            System.err.println("No suitable serial port found.");
            return false;
        }

        serialPort.setBaudRate(baudRate);
        serialPort.setNumDataBits(8);
        serialPort.setParity(SerialPort.NO_PARITY);
        serialPort.setNumStopBits(SerialPort.ONE_STOP_BIT);
        serialPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_SEMI_BLOCKING, 1000, 1000);

        if (serialPort.openPort()) {
            try {
                inputStream = serialPort.getInputStream();
            } catch (Exception e) {
                System.err.println("Failed to get input stream: " + e.getMessage());
                return false;
            }

            System.out.println("Opened port: " + serialPort.getSystemPortName());
            return true;
        } else {
            System.err.println("Failed to open port: " + serialPort.getSystemPortName());
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
                        int data = inputStream.read(); // Blocking read

                        if (data == -1) {
                            continue;
                        }

                        char c = (char) data;
                        lastKey = c;

                        if ((c >= '0' && c <= '9') || c == '.' || c == 'K') {
                            if (bufferLength < buffer.length) {
                                buffer[bufferLength++] = (byte) c; // Add the digit, dot, or 'K'
                            }
                        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
                            if (bufferLength > 0) {
                                // Loop from the last character in the buffer backward
                                for (int i = bufferLength - 1; i >= 0; i--) {
                                    byte lastChar = buffer[i];

                                    if (lastChar != 'K') {
                                        // If it's an operator, overwrite it
                                        if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/' || lastChar == '=') {
                                            buffer[i] = (byte) c; // Overwrite the operator
                                            // System.out.println("Overwritten operator: " + c); // Log when overwriting occurs
                                        } else {
                                            buffer[bufferLength++] = (byte) c;
                                        }

                                        break; // Exit the loop after finding the first non-'K' character
                                    }
                                }
                            } else {
                                buffer[bufferLength++] = '0';
                                buffer[bufferLength++] = (byte) c; // Add the operator at the start
                                System.out.println("Added operator at start: " + c); // Log when adding operator at start

                            }
                        } else {

                        }
                    }

                }
            } catch (IOException e) {
                readError = true;
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

    public synchronized void insertCharToBuffer(char c) {
        if ((c >= '0' && c <= '9') || c == '.' || c == 'K') {
            
            if (bufferLength < buffer.length) {
                buffer[bufferLength++] = (byte) c;
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
            if (bufferLength > 0) {
                
                for (int i = bufferLength - 1; i >= 0; i--) {
                    byte lastChar = buffer[i];

                    if (lastChar != 'K') {
                      
                        if (lastChar == '+' || lastChar == '-' || lastChar == '*' || lastChar == '/' || lastChar == '=') {
                            buffer[i] = (byte) c; 
                        } else {
                            buffer[bufferLength++] = (byte) c;
                        }
                        break; 
                    }
                }
            } else {
               
                if (bufferLength < buffer.length) {
                    buffer[bufferLength++] = (byte) '0';  // Add a default value before the operator
                    buffer[bufferLength++] = (byte) c; // Add the operator
                }
            }
        }
    }

    /*
    Reads the available buffered data
     */
    public synchronized char[] readBuffer() {
        if (readError) {
            return null;
        }

        if (bufferLength == 0) {
            return new char[0];
        }

        char[] data = new char[bufferLength];
        for (int i = 0; i < bufferLength; i++) {
            data[i] = (char) buffer[i];
        }

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

        return lastKey;
    }

    /*Clear the data stored*/
    public void clearBuffer() {
        bufferLength = 0;  // Reset the buffer length
        System.out.println("Buffer cleared");
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
