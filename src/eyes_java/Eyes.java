/*
	USPDroidsSimulator
	(C) 2007  Diogo Oliveira de Melo

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	src/eyes_java/Eyes.java
*/

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import java.lang.Thread;
import java.net.*;
import java.io.*;
import java.lang.Math;
import static java.lang.System.*;

public class Eyes extends JApplet {
    final static int maxCharHeight = 15;
    final static int minFontSize = 6;


    final static double escala = 4.61835;
    final static double x0 = 1 * escala;
    final static double y0 = 1 * escala;
    final static double gol_largura = 10 * escala;
    final static double gol_altura = 40 * escala;
    final static double campo_largura = 150 * escala;
    final static double campo_altura = 130 * escala;
    final static double triangulo_lado = 7 * escala;
    final static double bola_diametro = 4.2 * escala;
    final static double robo_aresta = 7.5 * escala;
    final static double circulo_central_diametro = 40 * escala;
    final static double grande_area_altura = 70 * escala;
    final static double grande_area_largura = 15 * escala;
    final static double cruz_tamanho = 5 * escala;
    final static double c_pequeno_diametro = 2.5 * escala;
    final static int nJogadores = 3;
    boolean ball = false;
    boolean t1[] = new boolean[nJogadores];
    boolean t2[] = new boolean[nJogadores];
    double time1x[] = new double[nJogadores];
    double time1y[] = new double[nJogadores];
    double angulo1[] = new double[nJogadores];
    double time2x[] = new double[nJogadores];
    double time2y[] = new double[nJogadores];
    double angulo2[] = new double[nJogadores];
    double bolax = 0;
    double bolay = 0;

    double time1x_a[] = new double[nJogadores];
    double time1y_a[] = new double[nJogadores];
    double angulo1_a[] = new double[nJogadores];
    double time2x_a[] = new double[nJogadores];
    double time2y_a[] = new double[nJogadores];
    double angulo2_a[] = new double [nJogadores];
    double bolax_a = 0;
    double bolay_a = 0;

    static double x[] = new double[20];
    static double y[] = new double[20];

    final static Color bg = Color.black;
    final static Color fg = Color.white;
    final static Color red = Color.red;
    final static Color white = Color.white;

    final static BasicStroke stroke = new BasicStroke(2.0f);
    final static BasicStroke wideStroke = new BasicStroke(8.0f);

    final static float dash1[] = {10.0f};
    final static BasicStroke dashed = new BasicStroke(1.0f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10.0f, dash1, 0.0f);
    Dimension totalSize;
    FontMetrics fontMetrics;
    ServerSocket serverSocket = null;
    Socket socket = null;
    int portNumber = 4321;

    public void init() {
        //Initialize drawing colors
	definir();
	
	try {
		serverSocket = new ServerSocket(portNumber);
	} catch(IOException e) {
		err.println("Erro: a porta " + portNumber + " nao possui socket.");
		exit(1);
	}
	out.println("Esperando...");
	try {
		socket = serverSocket.accept();
	} catch(IOException e) {
		err.println("Erro: falha na conexao.");
		exit(1);
	}

	out.println("Conexao aceita.");

        setBackground(bg);
        setForeground(fg);
    }

    FontMetrics pickFont(Graphics2D g2,
                         String longString,
                         int xSpace) {
        boolean fontFits = false;
        Font font = g2.getFont();
        FontMetrics fontMetrics = g2.getFontMetrics();
        int size = font.getSize();
        String name = font.getName();
        int style = font.getStyle();

        while ( !fontFits ) {
            if ( (fontMetrics.getHeight() <= maxCharHeight)
                 && (fontMetrics.stringWidth(longString) <= xSpace) ) {
                fontFits = true;
            }
            else {
                if ( size <= minFontSize ) {
                    fontFits = true;
                }
                else {
                    g2.setFont(font = new Font(name,
                                               style,
                                               --size));
                    fontMetrics = g2.getFontMetrics();
                }
            }
        }

        return fontMetrics;
    }

    Graphics2D g2;
    public void paint(Graphics g) {
    	g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        Dimension d = getSize();
        int gridWidth = d.width / 6;
        int gridHeight = d.height / 2;
	int count = 0;

        fontMetrics = pickFont(g2, "Filled and Stroked GeneralPath",
                               gridWidth);

        Color fg3D = Color.lightGray;

        g2.setPaint(fg3D);
        g2.setPaint(fg);

	

        // draw Line2D.Double
		campo(0);
	while(true) {
		/*g2.setPaint(new GradientPaint(0, 0, Color.BLUE, 100, 0, Color.BLUE));

	        g2.fill(new Rectangle2D.Double(0, 0, 100, 50));*/
		out.println("Pronto para receber as coordenadas.");
		String mensagem = null;
		try {
			BufferedReader entrada = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			mensagem = entrada.readLine();
		} catch(IOException e) {
			err.println("erro: Nao foi possivel usar o socket.");
			exit(1);
		}
		out.println("mensagem: "+mensagem);
		if(mensagem == null) {
			out.println("erro: falha na conexao. Saindo...");
			exit(1);
		}
		if(mensagem != "") {
			if(decodificar(mensagem) == false) {
				try {
					Thread.sleep(30);
				} catch(InterruptedException e){
				}
			}
		}
		//campo(count + 1);
		campo(1);
		if(ball == true) {
			bola(bolax_a, bolay_a, bolax, bolay);
			bolax_a = bolax;
			bolay_a = bolay;
		}
		for(int i = 0; i < nJogadores; i++) {
			if(t1[i] == true) {
				//out.println("AKI!!!");
				robo(i, time1x_a[i], time1y_a[i], angulo1_a[i], time1x[i], time1y[i], angulo1[i]);
				time1x_a[i] = time1x[i];
				time1y_a[i] = time1y[i];
				angulo1_a[i] = angulo1[i];
			}
			if(t2[i] == true) {
				robo(i + 3, time2x_a[i], time2y_a[i], angulo2_a[i], time2x[i], time2y[i], angulo2[i]);
				time2x_a[i] = time2x[i];
				time2y_a[i] = time2y[i];
				angulo2_a[i] = angulo2[i];
			}
		}
		out.println("ball: "+ball);
		for(int i = 0; i < nJogadores; i++) {
			out.println("t1["+i+"]: "+t1[i]);
			out.println("t2["+i+"]: "+t2[i]);
		}

		count = (count + 1) % 9;
		/*
		try {
			Thread.sleep(30);
		} catch(InterruptedException e){
		}*/
	}



    }

    public void definir() {
	x[0] = 0;
	y[0] = 0;

	x[1] = x0 + gol_largura + campo_largura + gol_largura + x0;
	y[1] = 0;

	x[2] = x[1];
	y[2] = y0 + campo_altura + y0;

	x[3] = x[0];
	y[3] = y[2];

	x[4] = x0 + gol_largura;
	y[4] = y0 + triangulo_lado;

	x[5] = x[4] + triangulo_lado;
	y[5] = y[4] - triangulo_lado;

	x[6] = x[4] + campo_largura - triangulo_lado;
	y[6] = y[5];

	x[7] = x[6] + triangulo_lado;
	y[7] = y[4];

	x[8] = x[7];
	y[8] = y0 + ((campo_altura - gol_altura) / 2);

	x[9] = x[7] + gol_largura;
	y[9] = y[8];

	x[10] = x[9];
	y[10] = y[9] + gol_altura;

	x[11] = x[8];
	y[11] = y[10];

	x[12] = x[11];
	y[12] = y[11] + ((campo_altura - gol_altura) / 2) - triangulo_lado;

	x[13] = x[6];
	y[13] = y[12] + triangulo_lado;

	x[14] = x[5];
	y[14] = y[13];

	x[15] = x[4];
	y[15] = y[12];

	x[16] = x[15];
	y[16] = y[11];

	x[17] = x0;
	y[17] = y[16];

	x[18] = x[17];
	y[18] = y[8];

	x[19] = x[4];
	y[19] = y[18];
    }

    public void campo(int n) {
    	//g2.setPaint(new GradientPaint(0, 0, Color.BLACK, LARGURA_TOTAL, ALTURA_TOTAL, Color.BLACK));
	double x2Points[] = {x[4], x[5], x[6], x[7], x[8], x[9], x[10], x[11], x[12], x[13], x[14], x[15], x[16], x[17], x[18], x[19], x[4]};
	double y2Points[] = {y[4], y[5], y[6], y[7], y[8], y[9], y[10], y[11], y[12], y[13], y[14], y[15], y[16], y[17], y[18], y[19], y[4]};
	GeneralPath poligono = null;

	if((n == 0) || (n == 1)) {
		poligono = new GeneralPath(GeneralPath.WIND_EVEN_ODD, 10);

		g2.setPaint(fg);
	}

	//***********************
	if(n == 0) {
		poligono.moveTo(x2Points[0], y2Points[0]);
		for(int i = 1; i < x2Points.length; i++)
			poligono.lineTo(x2Points[i], y2Points[i]);
		g2.draw(poligono);
	}
	//***********************

	//***********************
	if(n == 0) {
		poligono = new GeneralPath(GeneralPath.WIND_EVEN_ODD, 10);
		double x3Points[] = {x[0], x[1], x[2], x[3], x[0]};
		double y3Points[] = {y[0], y[1], y[2], y[3], y[0]};

		poligono.moveTo(x3Points[0], y3Points[0]);
		for(int i = 1; i < x3Points.length; i++)
			poligono.lineTo(x3Points[i], y3Points[i]);
		g2.draw(poligono);
	}
	//***********************
	
	//***********************
	if((n == 0)||(n == 1)) {
		poligono = new GeneralPath(GeneralPath.WIND_EVEN_ODD, 10);
		double x4Points[] = {(x[5] + x[6]) / 2, (x[5] + x[6]) / 2};
		double y4Points[] = {y[5], y[14]};

		poligono.moveTo(x4Points[0], y4Points[0]);
		poligono.lineTo(x4Points[1], y4Points[1]);
		g2.draw(poligono);
	}
	//***********************

	//***********************
	if((n == 0)||(n == 1))
		g2.draw(new Ellipse2D.Double(((x[5] + x[6]) / 2) - (circulo_central_diametro / 2), ((y[5] + y[14]) / 2) - (circulo_central_diametro / 2), circulo_central_diametro, circulo_central_diametro));
	//***********************


	//***********************
	double x5Points[] = {x[19], x[19] + grande_area_largura, x[19] + grande_area_largura, x[19], x[19]};
	double y5Points[] = {y[19] - ((grande_area_altura - gol_altura) / 2), y[19] - ((grande_area_altura - gol_altura) / 2), y[19] - ((grande_area_altura - gol_altura) / 2) + grande_area_altura, y[19] - ((grande_area_altura - gol_altura) / 2) + grande_area_altura, y[19] - ((grande_area_altura - gol_altura) / 2)};
	if((n == 0)||(n == 1)) {
		poligono = new GeneralPath(GeneralPath.WIND_EVEN_ODD, 10);

		poligono.moveTo(x5Points[0], y5Points[0]);
		for(int i = 1; i < x5Points.length; i++)
			poligono.lineTo(x5Points[i], y5Points[i]);
		g2.draw(poligono);
	}
	//***********************


	//***********************
	if((n == 0)||(n == 1)) {
		poligono = new GeneralPath(GeneralPath.WIND_EVEN_ODD, 10);
		double deslocamento = campo_largura - grande_area_largura;

		for(int i = 0; i < x5Points.length; i++)
			x5Points[i] += deslocamento;
		
		poligono.moveTo(x5Points[0], y5Points[0]);
		for(int i = 1; i < x5Points.length; i++)
			poligono.lineTo(x5Points[i], y5Points[i]);
		g2.draw(poligono);
	}
	//***********************
	
	
	//***********************
	double ax1 = x[4] + (37.5 * escala), ax2 = x[7] - (37.5 * escala);
	if((n == 0)||(n == 1)) {
		cruz(ax1, y[5] + (25 * escala));
		cruz(ax1, y[5] + (65 * escala));
		cruz(ax1, y[14] - (25 * escala));

		cruz(ax2, y[5] + (25 * escala));
		cruz(ax2, y[5] + (65 * escala));
		cruz(ax2, y[14] - (25 * escala));
	}

	//***********************
	


	//***********************
	if((n == 0)||(n == 1)) {
		circulo_pequeno(ax1 - (20 * escala), y[5] + (25 * escala)); 
		circulo_pequeno(ax1 + (20 * escala), y[5] + (25 * escala));
		circulo_pequeno(ax1 - (20 * escala), y[14] - (25 * escala));
		circulo_pequeno(ax1 + (20 * escala), y[14] - (25 * escala));

		circulo_pequeno(ax2 - (20 * escala), y[5] + (25 * escala)); 
		circulo_pequeno(ax2 + (20 * escala), y[5] + (25 * escala));
		circulo_pequeno(ax2 - (20 * escala), y[14] - (25 * escala));
		circulo_pequeno(ax2 + (20 * escala), y[14] - (25 * escala));
	}


	//***********************

    }

    public void bola(double x, double y, double n_x, double n_y) {
    	g2.setPaint(Color.BLACK);
	g2.fill(new Ellipse2D.Double(x - 1, y - 1, bola_diametro + 2, bola_diametro + 2));
    	g2.setPaint(Color.ORANGE);
	g2.fill(new Ellipse2D.Double(n_x, n_y, bola_diametro, bola_diametro));
    }

    public void robo(int id, double x, double y, double angulo, double novo_x, double novo_y, double novo_angulo) {
	Paint aux = g2.getPaint();
	GeneralPath poligono = new GeneralPath(GeneralPath.WIND_EVEN_ODD, 10);
	double ang = (angulo + Math.PI / 4);
	double px[] = new double[4];
	double py[] = new double[4];
	out.println("robo: " + id);
	if((x != 0)&&(y != 0)&&((x != novo_x)||(y != novo_y)||(angulo != novo_angulo))) {
		while(ang >= Math.PI)
			ang -= Math.PI / 2;
		for(int i = 0; i < 4; i++) {
			px[i] = x0 + x + (Math.cos(ang) * ((robo_aresta / 2) + 2));
			py[i] = y0 + y + (Math.sin(ang) * ((robo_aresta / 2) + 2));
			ang += Math.PI / 2;
		}

		g2.setPaint(Color.BLACK);
		poligono.moveTo(px[0], py[0]);
		for(int i = 1; i < 4; i++)
			poligono.lineTo(px[i], py[i]);
		poligono.lineTo(px[0], py[0]);
		g2.fill(poligono);
	}
	
	poligono = new GeneralPath(GeneralPath.WIND_EVEN_ODD, 10);
	ang = novo_angulo + (Math.PI / 4);

	/*while(ang >= Math.PI)
		ang -= Math.PI / 2;*/
	for(int i = 0; i < 4; i++) {
		px[i] = x0 + novo_x + (Math.cos(ang) * ((robo_aresta / 2)));
		py[i] = y0 + novo_y + (Math.sin(ang) * ((robo_aresta / 2)));
		ang += Math.PI / 2;
	}

	if(id < 3)
		g2.setPaint(Color.BLUE);
	else
		g2.setPaint(Color.YELLOW);
	poligono.moveTo(px[0], py[0]);
	for(int i = 1; i < 4; i++)
		poligono.lineTo(px[i], py[i]);
	poligono.lineTo(px[0], py[0]);
	g2.fill(poligono);

	g2.setPaint(Color.RED);
	g2.drawLine((int) (novo_x + x0), (int) (novo_y + y0),(int) ((px[0] + px[3]) / 2), (int) ((py[0] + py[3]) / 2));

	g2.setPaint(aux);
}

    public void cruz(double x, double y) {
    	GeneralPath poligono = new GeneralPath(GeneralPath.WIND_EVEN_ODD, 10);
	double ax[] = {x, x, x, x - (cruz_tamanho / 2), x + (cruz_tamanho / 2)};
	double ay[] = {y - (cruz_tamanho / 2), y + (cruz_tamanho / 2), y, y, y};

	poligono.moveTo(ax[0], ay[0]);
	for(int i = 1; i < ax.length; i++)
		poligono.lineTo(ax[i], ay[i]);
	
	g2.draw(poligono);
    }
		
    public void circulo_pequeno(double x, double y) {
    	Paint aux = g2.getPaint();
    	x -= c_pequeno_diametro / 2;
	y -= c_pequeno_diametro / 2;

	g2.draw(new Ellipse2D.Double(x, y, c_pequeno_diametro, c_pequeno_diametro));
	x++;
	y++;
	g2.setPaint(Color.GRAY);
	g2.fill(new Ellipse2D.Double(x, y, c_pequeno_diametro - 2, c_pequeno_diametro - 2));
	g2.setPaint(aux);
    }

    public boolean decodificar(String mensagem) {
	String pedacos[] = mensagem.split("#");

	//out.println("pedacos.length: " + pedacos.length);
	if(pedacos.length != ((nJogadores * 3 * 2) + 2))
		return false;
	
	if((Double.parseDouble(pedacos[0]) != 0)&&(Double.parseDouble(pedacos[1]) != 0)) {
		ball = true;
		bolax = (Double.parseDouble(pedacos[0]) * escala * 100) - 4;
		bolay = (Double.parseDouble(pedacos[1]) * escala * 100) - 4;
	}
	else
		ball = false;

	for(int i = 0; i < nJogadores; i++) {
		if((Double.parseDouble(pedacos[(3 * i) + 2]) != 0.0)&&(Double.parseDouble(pedacos[(3 * i) + 3]) != 0.0)) {
			t1[i] = true;
			time1x[i] = Double.parseDouble(pedacos[(3 * i) + 2]) * escala * 100;
			time1y[i] = Double.parseDouble(pedacos[(3 * i) + 3]) * escala * 100;
			angulo1[i] = Double.parseDouble(pedacos[(3 * i) + 4]);
		}
		else
			t1[i] = false;

		if((Double.parseDouble(pedacos[(3 * i) + 11]) != 0)&&(Double.parseDouble(pedacos[(3 * i) + 12]) != 0)) {
			t2[i] = true;
			time2x[i] = Double.parseDouble(pedacos[(3 * i) + 11]) * escala * 100;
			time2y[i] = Double.parseDouble(pedacos[(3 * i) + 12]) * escala * 100;
			angulo2[i] = Double.parseDouble(pedacos[(3 * i) + 13]);
		}
		else
			t2[i] = false;
	}

	return true;
    }

    	

    public boolean decodificar_antigo(String mensagem) {
    	//out.println("mensagem: " + mensagem);
    	String pedacos[] = mensagem.split("#");

	if((pedacos.length != 3)||(pedacos[1].split("@").length != nJogadores)||(pedacos[2].split("@").length != nJogadores)) {
		//out.println("erro: mensagem fora do protocolo.");
		ball = false;
		for(int i = 0; i < nJogadores; i++) {
			t1[i] = false;
			t2[i] = false;
		}
			
		return false;
	}
	
	//Coordenadas da bola.
	String bola[] = pedacos[0].split(",");
	if(pedacos[0].split(",").length != 0) {
		//out.println("pedacos[0].split(\",\").length: "+pedacos[0].split(",").length);
		//out.println("bola[0]: " + bola[0] + ". bola[1]: " + bola[1]);
		ball = true;
		try {
			bolax = (Double.parseDouble(bola[0]) * escala * 100);
			bolay = (Double.parseDouble(bola[1]) * escala * 100);
			//out.println("x: " + bola[0] + ". y: " + bola[1]);
		} catch(NumberFormatException e) {
			ball = false;
		}
	}
	else
		ball = false;

	// Coordenadas dos jogadores dos times A e B.
	String ta[][] = new String[nJogadores][];
	String tb[][] = new String[nJogadores][];
	for(int i = 0; i < nJogadores; i++) {
		ta[i] = pedacos[1].split("@")[i].split(",");
		tb[i] = pedacos[2].split("@")[i].split(",");

		if(ta[i].length !=3)
			t1[i] = false;
		else {
			t1[i] = true;
			try {
				time1x[i] = (Double.parseDouble(ta[i][0]) * escala * 100);
				time1y[i] = (Double.parseDouble(ta[i][1]) * escala * 100);
				angulo1[i] = (Double.parseDouble(ta[i][2]));
				//out.println("time1x["+i+"]: "+time1x[i]+". time1y["+i+"]: "+time1y[i]+". angulo1["+i+"]: "+angulo1[i]+".");
			} catch(NumberFormatException e) {
				t1[i] = false;
			}
		}

		if(tb[i].length !=2)
			t2[i] = false;
		else {
			t2[i] = true;
			try {
				time2x[i] = (Double.parseDouble(tb[i][0]) * escala * 100);
				time2y[i] = (Double.parseDouble(tb[i][1]) * escala * 100);
				angulo1[i] = (Double.parseDouble(ta[i][2]));
				//out.println("time1x["+i+"]: "+time1x[i]+". time1y["+i+"]: "+time1y[i]+". angulo2["+i+"]: "+angulo2[i]+".");
			} catch(NumberFormatException e) {
				t1[i] = false;
			}
		}
	}

    	return true;
    }

    public static void main(String s[]) {
        JFrame f = new JFrame("Eyes");
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {System.exit(0);}
        });
        JApplet applet = new Eyes();
        f.getContentPane().add("Center", applet);
        applet.init();
        f.pack();
        f.setSize(new Dimension((int) x[2] + 1, (int) y[2] + 100));
        f.setVisible(true);
    }

}
