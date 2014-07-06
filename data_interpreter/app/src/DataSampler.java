import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;

public class DataSampler{
	private static JFrame window;

	private static SummarizeChooseFilePanel chooseFilePanel;
	private static SummarizeGraphPanel graphPanel;

	public static void main(String[] args){
		window = new JFrame("Data sampler");
		window.setLayout(new BorderLayout());
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		graphPanel = new SummarizeGraphPanel();
		chooseFilePanel = new SummarizeChooseFilePanel(graphPanel);

		window.add(chooseFilePanel, BorderLayout.WEST);
		window.add(graphPanel, BorderLayout.CENTER);
		window.pack();

		window.setVisible(true);
	};

	public static void processInputFile(File input){
		chooseFilePanel.update(input);
	};
};
