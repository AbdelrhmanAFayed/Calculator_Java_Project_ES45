module com.mycompany.java_module {
    requires javafx.controls;
    requires javafx.fxml;

    opens com.mycompany.java_module to javafx.fxml;
    exports com.mycompany.java_module;
}
