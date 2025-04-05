/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.mycompany.java_module;

import java.net.URL;
import java.util.Arrays;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;


import serial_handler.Serial_Handler;
/**
 * FXML Controller class
 *
 * @author fazloka
 */
public class PrimaryController implements Initializable {
    
    Serial_Handler serial = null; 

    @FXML
    private TextField tf;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        serial = new Serial_Handler(); 
        
        serial.init(9600);
     
        // TODO
    }    

    @FXML
    private void BtnHand(MouseEvent event) {
      
       tf.setText(new String(serial.readBuffer()));
    }

    @FXML
    private void BtnClear(MouseEvent event) {
        tf.setText(new String(serial.readBufferFiltered()));
    }
    
}
