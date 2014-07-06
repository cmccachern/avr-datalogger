import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;
import javax.swing.border.*;
import java.util.*;

public class SummarizeChooseFilePanel extends JPanel{
	private JLabel inputPrompt, rangePrompt;

	private JPanel fileChooserContainer;
	private FileChooseButton fileChooser;

	private SummarizeGraphPanel grapher;

	public SummarizeChooseFilePanel(SummarizeGraphPanel grapher){
		super();
		this.setLayout(new GridLayout(4, 1));
		this.setBorder(BorderFactory.createEtchedBorder());

		inputPrompt = new JLabel("Choose an input file:");
		rangePrompt = new JLabel("Select the date range:");

		fileChooserContainer = new JPanel(new FlowLayout());
		fileChooser = new FileChooseButton();
		fileChooserContainer.add(fileChooser);

		this.add(inputPrompt);
		this.add(fileChooserContainer);
		this.add(rangePrompt);

		this.setPreferredSize(new Dimension(250,600));

		this.grapher = grapher;
	};

	public void update(File input){
		try{
			Process p = new ProcessBuilder("python", "/home/dragostea/Dev/Robotics/UnderwaterSensor/Plotter.py", input.getAbsolutePath()).start();

			p.waitFor();
			if(p.exitValue() == 0)
				grapher.update("/home/dragostea/Dev/Robotics/UnderwaterSensor/graph.png");
		}catch(Exception e){
			System.out.println("Error executing python!");
			System.out.println(e.getMessage());
		};
	};
};
