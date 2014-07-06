import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;

public class SummarizeGraphPanel extends JPanel{
	private ImagePanel imagePanel;
	private BufferedImage graph;

	public SummarizeGraphPanel(){
		super();
		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createEtchedBorder());

		imagePanel = new ImagePanel();
		//this.add(imagePanel, BorderLayout.CENTER);

		this.setPreferredSize(new Dimension(700, 600));
	};

	protected void paintComponent(Graphics g){
		super.paintComponent(g);
		g.drawImage(graph, 0, 0, null);
	};

	public void update(String path){
		try{
			graph = ImageIO.read(new File(path));
			System.out.println("Reloaded the graph");
			this.repaint();
		}catch(IOException e){
			System.out.println("Could not load the image");
		};
	};
};
