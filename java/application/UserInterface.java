package application;

import java.io.*;
import java.util.Scanner;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.paint.Color;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.geometry.Insets;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.stage.FileChooser;
import javafx.scene.Group;
import javafx.scene.shape.Line;
import javafx.scene.shape.Circle;
import javafx.scene.text.TextFlow;
import javafx.scene.text.Text;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;
import javafx.event.*;

public class UserInterface extends Application {

	private File file;

	@Override
	public void start(Stage primaryStage) {
		try {
			// Browse : choose file
			Button browse_button = new Button("Browse");
			browse_button.setMaxWidth(Double.MAX_VALUE);
			FileChooser fileChooser = new FileChooser();
			fileChooser.setTitle("Open Segments File");
			TextFlow file_label = new TextFlow();
			file_label.setMaxWidth(Double.MAX_VALUE);
			Text text1 = new Text("Input file: ");
			text1.setStyle("-fx-font-weight: bold");
			Text text2 = new Text("");
			file_label.getChildren().addAll(text1, text2);

			// Choose algorithm
			Label algo_label = new Label();
			algo_label.setText("Choose your algorithm:");
			algo_label.setStyle("-fx-font-weight: bold");
			algo_label.setDisable(true);
			ChoiceBox<String> combobox = new ChoiceBox<String>();
			combobox.setMaxWidth(Double.MAX_VALUE);
			combobox.getItems().addAll("All pairs", "Bentley-Ottmmann");
			combobox.setDisable(true);

			// Execute
			Button run_button = new Button("Run");
			run_button.setMaxWidth(Double.MAX_VALUE);
			run_button.setDisable(true);

			Group group = new Group();

			browse_button.setOnAction(
			new EventHandler<ActionEvent>() {
				@Override
				public void handle(final ActionEvent e) {
					file = fileChooser.showOpenDialog(primaryStage);
					if (file != null) {
						text2.setText(file.getName());
						algo_label.setDisable(false);
						combobox.setDisable(false);
						showSegments(file, group);
					}
				}
			});

			combobox.setOnAction(
			new EventHandler<ActionEvent>() {
                @Override
                public void handle(final ActionEvent e) {
                	run_button.setDisable(false);
                }
			});

			run_button.setOnAction(
			new EventHandler<ActionEvent>() {
				@Override
				public void handle(final ActionEvent e) {
					if (combobox.getValue().equals("All pairs")) {
						new Intersections().runAllPairs(file.getAbsolutePath(), file.getAbsolutePath() + ".out");
						markIntersections(new File(file.getAbsolutePath() + ".out"), group);
					}
					else if (combobox.getValue().equals("Bentley-Ottmmann")) {
						new Intersections().runBentleyOttmann(file.getAbsolutePath(), file.getAbsolutePath() + ".out");
						markIntersections(new File(file.getAbsolutePath() + ".out"), group);
					}
				}
			});

			VBox vbox = new VBox();
			vbox.setPadding(new Insets(5, 20, 5, 20));
			vbox.setSpacing(10);
			vbox.setStyle("-fx-background-color: #336699;");
			vbox.getChildren().addAll(browse_button, file_label, algo_label, combobox, run_button);

			BorderPane root = new BorderPane();
			root.setRight(vbox);
			root.setCenter(group);

			Scene scene = new Scene(root, 800, 600, Color.GRAY);
			primaryStage.setScene(scene);
			primaryStage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
        launch(args);
    }

	private void showSegments(File file, Group group) {
		try {
			group.getChildren().clear();
			Scanner scan = new Scanner(file);
			String line;

			while (scan.hasNextLine()) {
				long a1, b1, c1, d1, a2, b2, c2, d2;
				line = scan.nextLine();
				int begin = 0;
				int end = line.indexOf("/", begin);
				a1 = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				end = line.indexOf(",", begin);
				b1 = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				end = line.indexOf("/", begin);
				c1 = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				end = line.indexOf(" ", begin);
				d1 = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				end = line.indexOf("/", begin);
				a2 = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				end = line.indexOf(",", begin);
				b2 = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				end = line.indexOf("/", begin);
				c2 = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				d2 = Integer.parseInt(line.substring(begin));

				Line l = new Line((double) a1/b1, (double) c1/d1, (double) a2/b2, (double) c2/d2);
				l.setStroke(Color.DARKBLUE);
				l.setStrokeWidth(1);
				group.getChildren().add(l);
				Circle p1 = new Circle((double) a1/b1, (double) c1/d1, 2);
				p1.setFill(Color.DARKGREEN);
				group.getChildren().add(p1);
				Circle p2 = new Circle((double) a2/b2, (double) c2/d2, 2);
				p2.setFill(Color.DARKGREEN);
				group.getChildren().add(p2);
			}
		} catch(FileNotFoundException ex) {
			System.err.println("File not found");
		}
	}

	private void markIntersections(File file, Group group) {
		try {
			Scanner scan = new Scanner(file);
			String line;

			while (scan.hasNextLine()) {
				long a, b, c, d;
				line = scan.nextLine();
				int begin = 0;
				int end = line.indexOf("/", begin);
				a = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				end = line.indexOf(",", begin);
				b = Integer.parseInt(line.substring(begin,end));
				begin = end+1;
				end = line.indexOf("/", begin);
				c = Integer.parseInt(line.substring(begin,end));
                begin = end+1;
                d = Integer.parseInt(line.substring(begin));

				Circle p = new Circle((double) a/b, (double) c/d, 2);
				p.setFill(Color.RED);
				group.getChildren().add(p);
			}
		}
		catch(FileNotFoundException ex) {
            System.err.println("File not found");
        }
	}

	static {
		System.loadLibrary("intersections");
	}

}