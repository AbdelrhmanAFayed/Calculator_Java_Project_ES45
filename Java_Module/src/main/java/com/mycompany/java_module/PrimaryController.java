/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
 /*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.mycompany.java_module;

import java.net.URL;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Rectangle2D;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Screen;
import javafx.stage.Stage;
import serial_handler.Serial_Handler;

/**
 * FXML Controller class
 *
 * @author mariam
 */
public class PrimaryController implements Initializable {

    private double xOffset = 0;
    private double yOffset = 0;
    private double centerX = 0;
    private double centerY = 0;
    private Serial_Handler serial;
    private Thread appThread;
    private Thread keyPressEffectThread;
    private Calculator calculator;
    private boolean appThreadRunning = true;
    private Map<Character, Button> btnsMap = null;

    @FXML
    private Label operationField;
    @FXML
    private Label resultField;
    @FXML
    private AnchorPane rootPane;
    @FXML
    private Button exitButton;
    @FXML
    private AnchorPane guiPane;
    @FXML
    private Button btn7;
    @FXML
    private Button btn8;
    @FXML
    private Button btn9;
    @FXML
    private Button btnDiv;
    @FXML
    private Button btn4;
    @FXML
    private Button btn5;
    @FXML
    private Button btn6;
    @FXML
    private Button btnMul;
    @FXML
    private Button btn1;
    @FXML
    private Button btn2;
    @FXML
    private Button btn3;
    @FXML
    private Button btnSub;
    @FXML
    private Button btnEqual;
    @FXML
    private Button btn0;
    @FXML
    private Button btnDot;
    @FXML
    private Button btnSum;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        serial = new Serial_Handler();
        serial.init(9600);
        appThread = new Thread(this::appHandler);
        keyPressEffectThread = new Thread(this::keyPressEffectHandler);
        calculator = new Calculator();
        appThread.start();
        keyPressEffectThread.start();

        btnsMap = Map.ofEntries(
                Map.entry('7', btn7),
                Map.entry('8', btn8),
                Map.entry('9', btn9),
                Map.entry('/', btnDiv),
                Map.entry('4', btn4),
                Map.entry('5', btn5),
                Map.entry('6', btn6),
                Map.entry('*', btnMul),
                Map.entry('1', btn1),
                Map.entry('2', btn2),
                Map.entry('3', btn3),
                Map.entry('-', btnSub),
                Map.entry('=', btnEqual),
                Map.entry('0', btn0),
                Map.entry('.', btnDot),
                Map.entry('+', btnSum)
        );
    }

    @FXML
    private void handleMousePressed(MouseEvent event) {
        // Capture the initial mouse position when pressed
        xOffset = event.getSceneX();
        yOffset = event.getSceneY();
    }

    @FXML
    private void handleMouseDragged(MouseEvent event) {
        // Move the window by updating its position based on mouse movement
        Stage stage = (Stage) rootPane.getScene().getWindow();
        stage.setX(event.getScreenX() - xOffset);
        stage.setY(event.getScreenY() - yOffset);
    }

    @FXML
    private void clearDisplay(ActionEvent event) {
        resultField.setText("0");
        operationField.setText("");
        serial.clearBuffer();
    }

    @FXML
    private void buttonHandler(ActionEvent event) {
        Button clickedButton = (Button) event.getSource();
        String buttonText = clickedButton.getText();   // Button's visible text
        if (buttonText.equals("×")) {
            buttonText = "*";
        } else if (buttonText.equals("÷")) {
            buttonText = "/";
        }
        serial.insertCharToBuffer(buttonText.charAt(0));
    }

    @FXML
    private void exit(ActionEvent event) {
        // Close the application
        Stage stage = (Stage) exitButton.getScene().getWindow();
        serial.closePort();
        appThreadRunning = false;
        stage.close();
    }

    @FXML
    private void minimize(ActionEvent event) {
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        stage.setIconified(true);  // Minimizes the window
    }

    @FXML
    private void maximize(ActionEvent event) {
        Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
        Screen screen = Screen.getPrimary();
        Rectangle2D bounds = screen.getVisualBounds();

        if (stage.getWidth() == bounds.getWidth() && stage.getHeight() == bounds.getHeight()) {
            // Restore to default size
            stage.setWidth(350);  // or your default width
            stage.setHeight(500); // or your default height
            System.out.println(centerX);
            System.out.println(centerY);
            stage.setX(centerX);
            stage.setY(centerY);

        } else {
            // Maximize manually
            centerX = stage.getX();
            System.out.println(centerX);
            centerY = stage.getY();
            System.out.println(centerY);
            stage.setX(bounds.getMinX());
            stage.setY(bounds.getMinY());
            stage.setWidth(bounds.getWidth());
            stage.setHeight(bounds.getHeight());
        }
    }

    private void appHandler() {
        boolean isResult = false;
        while (appThreadRunning) {
            char lastPressedKey = '\0';
            
            String cleanedBuffer = new String(serial.readBufferFiltered());
            if (!cleanedBuffer.isEmpty()) {
                lastPressedKey = cleanedBuffer.charAt(cleanedBuffer.length() - 1);
            }
            if (lastPressedKey == '=') {
                Double result = calculator.getResult(cleanedBuffer.substring(0, cleanedBuffer.length() - 1));
                String finalResult = result.toString().equals("NaN") ? "Invalid Expression" : result.toString();
                isResult = true;
                Platform.runLater(new Runnable() {
                    @Override
                    public void run() {
                        resultField.setText(finalResult);
                    }
                });
            } else {
                if (isResult) {
                    serial.clearBuffer();
                    serial.insertCharToBuffer(lastPressedKey);
                    isResult = false ;
                }

                Platform.runLater(new Runnable() {
                    @Override
                    public void run() {
                        operationField.setText(cleanedBuffer);
                    }
                });

            }
            try {
                Thread.sleep(50);
            } catch (InterruptedException ex) {
                Logger.getLogger(PrimaryController.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    private void keyPressEffectHandler() {
        boolean isStyled = false;
        char lastStyledKey = 'z';
        while (appThreadRunning) {
            char lastPressedKey = serial.getLastKeyPressed();

            if (lastPressedKey != 'K' && !isStyled) {
                if (btnsMap.get(lastPressedKey) != null) {
                    btnsMap.get(lastPressedKey).getStyleClass().add("hwButtonPressed");
                    lastStyledKey = lastPressedKey;
                    isStyled = true;
                }
            } else if (lastPressedKey == 'K' && isStyled) {
                if (btnsMap.get(lastStyledKey) != null) {
                    btnsMap.get(lastStyledKey).getStyleClass().remove("hwButtonPressed");
                    isStyled = false;
                }
            }
            try {
                Thread.sleep(50);
            } catch (InterruptedException ex) {
                Logger.getLogger(PrimaryController.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
