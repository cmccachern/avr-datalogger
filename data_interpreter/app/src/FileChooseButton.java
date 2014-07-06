import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;

public class FileChooseButton extends JButton implements ActionListener{
	public FileChooseButton(){
		super("Select File");
		this.addActionListener(this);
	};

	@Override
	public void actionPerformed(ActionEvent e){
		JFileChooser fileChooser = new JFileChooser();
		if( fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION )
			DataSampler.processInputFile( fileChooser.getSelectedFile() );
	};
};
