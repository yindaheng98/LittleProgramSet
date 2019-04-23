package HelloFX;

import javafx.application.Application;
import javafx.scene.*;
import javafx.stage.Stage;
import javafx.fxml.FXMLLoader;

public class Main extends Application
{
    @Override
    public void start(Stage primaryStage) throws Exception
    {
        Parent root = FXMLLoader.load(getClass().getResource("/MainPage.fxml"));
        primaryStage.setTitle("My Application");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }

    public static void main(String[] args)
    {
        launch(args);
    }
}