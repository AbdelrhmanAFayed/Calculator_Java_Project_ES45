package com.mycompany.java_module;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import javafx.scene.paint.Color;
import javafx.stage.StageStyle;

/**
 * JavaFX App
 */
public class App extends Application {

    private static Scene scene;

    @Override
    public void start(Stage stage) throws IOException {
        scene = new Scene(loadFXML("primary"), 380, 550);
//        stage.initStyle(StageStyle.UNDECORATED);      // Remove window decoration
        stage.initStyle(StageStyle.UTILITY);   // Removes window decorations (optional)
        stage.setOpacity(1);  // Set the opacity of the entire window
        stage.setTitle("Calculator");
//        stage.initStyle(StageStyle.TRANSPARENT);     // Make the window transparent
//        scene.setFill(Color.TRANSPARENT);                   // Set scene to transparent
        
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

}