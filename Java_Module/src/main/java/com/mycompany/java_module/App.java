package com.mycompany.java_module;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import javafx.scene.paint.Color;
import javafx.stage.StageStyle;
import serial_handler.Serial_Handler;

/**
 * JavaFX App
 */
public class App extends Application {

    private static Scene scene;
    private static Serial_Handler serial;
//    private static Thread appThread;
//    private static Thread keyPressEffectThread;

    @Override
    public void start(Stage stage) throws IOException {
        serial = new Serial_Handler();
        serial.init(9600);
//        appThread = new Thread();
//        keyPressEffectThread = new Thread();
        scene = new Scene(loadFXML("primary"), 350, 500);
        stage.setTitle("Calculator");
        stage.initStyle(StageStyle.TRANSPARENT);     // Make the window transparent
        scene.setFill(Color.TRANSPARENT);            // Set scene to transparent
        stage.setResizable(true);
        stage.setScene(scene);
        stage.show();

    }

    static void setRoot(String fxml) throws IOException {
        scene.setRoot(loadFXML(fxml));
    }

    private static Parent loadFXML(String fxml) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource(fxml + ".fxml"));
        return fxmlLoader.load();
    }

    public static void main(String[] args) {
        launch();
    }

    public static Serial_Handler getSerial() {
        return serial;
    }

//    public static void setAppThread(Thread th) {
//        appThread = th;
//    }
//    
//    public static Thread getAppThread() {
//        return appThread;
//    }
//
//    public static void setKeyPressEffectThread(Thread th) {
//        keyPressEffectThread = th;
//    }
//    
//    public static Thread getKeyPressEffectThread() {
//        return keyPressEffectThread;
//    }
}
