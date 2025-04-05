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
import java.util.ResourceBundle;
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
    private Button button_8;
    @FXML
    private Button button_7;
    @FXML
    private Button button_9;
    @FXML
    private Button button_div;
    @FXML
    private Button button_4;
    @FXML
    private Button button_5;
    @FXML
    private Button button_6;
    @FXML
    private Button button_mul;
    @FXML
    private Button button_1;
    @FXML
    private Button button_2;
    @FXML
    private Button button_3;
    @FXML
    private Button button_sub;
    @FXML
    private Button button_dot;
    @FXML
    private Button button_0;
    @FXML
    private Button button_eql;
    @FXML
    private Button button_add;
    @FXML
    private Button minButton;
    @FXML
    private Button maxButton;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {

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
    }

    @FXML
    private void buttonHandler(ActionEvent event) {

    }

    @FXML
    private void exit(ActionEvent event) {
        // Close the application
        Stage stage = (Stage) exitButton.getScene().getWindow();
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

}
