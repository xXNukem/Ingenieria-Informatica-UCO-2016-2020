/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package easyDOS;

import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import keeptoo.Drag;

/**
 *
 * @author josel
 */
public class Home extends javax.swing.JFrame {

    public Home() {
        try {
            checkFileUser();
        } catch (IOException ex) {
            Logger.getLogger(Home.class.getName()).log(Level.SEVERE, null, ex);
        }
        initComponents(); //Inicializo el home
        //Establezco que inicie en el centro de la pantalla
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dim.width / 2 - this.getSize().width / 2, dim.height / 2 - this.getSize().height / 2);
        DisplayPanel.setVisible(false);
        btnAddJuego.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        btnSalir.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        btnMisJuegos.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        btnPreferencias1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
    }

    private void checkFileUser() throws IOException {
        String url = new java.io.File(".").getCanonicalPath();
        url = url.replace("\\", "/");
        url = url + "/Juegos/default.txt";
        File f = new File(url);
        try {
            File file = new File(url);
            file.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        DisplayPanel = new javax.swing.JPanel();
        JScrollBilioteca = new javax.swing.JScrollPane();
        biblioteca = new easyDOS.Biblioteca();
        jPanel1 = new javax.swing.JPanel();
        btnAddJuego = new keeptoo.KButton();
        btnMisJuegos = new keeptoo.KButton();
        btnPreferencias1 = new keeptoo.KButton();
        btnSalir = new keeptoo.KButton();
        jLabel1 = new javax.swing.JLabel();
        background = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setBackground(new java.awt.Color(255, 255, 255));
        setLocationByPlatform(true);
        setUndecorated(true);
        addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
            public void mouseDragged(java.awt.event.MouseEvent evt) {
                formMouseDragged(evt);
            }
        });
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        JScrollBilioteca.setBorder(javax.swing.BorderFactory.createEtchedBorder());
        JScrollBilioteca.setViewportBorder(javax.swing.BorderFactory.createMatteBorder(1, 1, 1, 1, new java.awt.Color(51, 51, 51)));
        JScrollBilioteca.setViewportView(biblioteca);

        javax.swing.GroupLayout DisplayPanelLayout = new javax.swing.GroupLayout(DisplayPanel);
        DisplayPanel.setLayout(DisplayPanelLayout);
        DisplayPanelLayout.setHorizontalGroup(
            DisplayPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(JScrollBilioteca)
        );
        DisplayPanelLayout.setVerticalGroup(
            DisplayPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(JScrollBilioteca)
        );

        getContentPane().add(DisplayPanel, new org.netbeans.lib.awtextra.AbsoluteConstraints(260, 10, 740, 520));

        jPanel1.setOpaque(false);

        btnAddJuego.setIcon(new javax.swing.ImageIcon(getClass().getResource("/img/obtenerJuego.png"))); // NOI18N
        btnAddJuego.setText("Añadir Plantilla");
        btnAddJuego.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnAddJuego.setkEndColor(new java.awt.Color(153, 0, 153));
        btnAddJuego.setkHoverEndColor(new java.awt.Color(153, 153, 255));
        btnAddJuego.setkHoverForeGround(new java.awt.Color(255, 255, 255));
        btnAddJuego.setkHoverStartColor(new java.awt.Color(153, 153, 255));
        btnAddJuego.setkSelectedColor(new java.awt.Color(102, 102, 255));
        btnAddJuego.setkStartColor(new java.awt.Color(102, 204, 255));
        btnAddJuego.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAddJuegoActionPerformed(evt);
            }
        });

        btnMisJuegos.setIcon(new javax.swing.ImageIcon(getClass().getResource("/img/cd.png"))); // NOI18N
        btnMisJuegos.setText("Mis Juegos");
        btnMisJuegos.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnMisJuegos.setkEndColor(new java.awt.Color(153, 0, 153));
        btnMisJuegos.setkHoverEndColor(new java.awt.Color(153, 153, 255));
        btnMisJuegos.setkHoverForeGround(new java.awt.Color(255, 255, 255));
        btnMisJuegos.setkHoverStartColor(new java.awt.Color(153, 153, 255));
        btnMisJuegos.setkSelectedColor(new java.awt.Color(102, 102, 255));
        btnMisJuegos.setkStartColor(new java.awt.Color(102, 204, 255));
        btnMisJuegos.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnMisJuegosActionPerformed(evt);
            }
        });

        btnPreferencias1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/img/settings.png"))); // NOI18N
        btnPreferencias1.setText("Preferencias");
        btnPreferencias1.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnPreferencias1.setkEndColor(new java.awt.Color(153, 0, 153));
        btnPreferencias1.setkHoverEndColor(new java.awt.Color(153, 153, 255));
        btnPreferencias1.setkHoverForeGround(new java.awt.Color(255, 255, 255));
        btnPreferencias1.setkHoverStartColor(new java.awt.Color(153, 153, 255));
        btnPreferencias1.setkSelectedColor(new java.awt.Color(102, 102, 255));
        btnPreferencias1.setkStartColor(new java.awt.Color(102, 204, 255));
        btnPreferencias1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnPreferencias1ActionPerformed(evt);
            }
        });

        btnSalir.setIcon(new javax.swing.ImageIcon(getClass().getResource("/img/out.png"))); // NOI18N
        btnSalir.setText("Salir");
        btnSalir.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnSalir.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        btnSalir.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        btnSalir.setkBackGroundColor(new java.awt.Color(255, 0, 153));
        btnSalir.setkEndColor(new java.awt.Color(255, 102, 102));
        btnSalir.setkHoverEndColor(new java.awt.Color(153, 153, 255));
        btnSalir.setkHoverForeGround(new java.awt.Color(255, 255, 255));
        btnSalir.setkHoverStartColor(new java.awt.Color(153, 153, 255));
        btnSalir.setkSelectedColor(new java.awt.Color(102, 102, 255));
        btnSalir.setkStartColor(new java.awt.Color(102, 204, 255));
        btnSalir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnSalirActionPerformed(evt);
            }
        });

        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/img/easyBox.png"))); // NOI18N

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(btnMisJuegos, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnAddJuego, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(jPanel1Layout.createSequentialGroup()
                            .addGap(65, 65, 65)
                            .addComponent(jLabel1))
                        .addGroup(jPanel1Layout.createSequentialGroup()
                            .addGap(35, 35, 35)
                            .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                .addComponent(btnSalir, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(btnPreferencias1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))))
                .addContainerGap(40, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                .addGap(59, 59, 59)
                .addComponent(jLabel1, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(37, 37, 37)
                .addComponent(btnAddJuego, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(btnMisJuegos, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(btnPreferencias1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(btnSalir, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(50, Short.MAX_VALUE))
        );

        getContentPane().add(jPanel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 260, 530));

        background.setIcon(new javax.swing.ImageIcon(getClass().getResource("/img/fondo.jpg"))); // NOI18N
        background.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                backgroundKeyPressed(evt);
            }
        });
        getContentPane().add(background, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, 1010, 540));

        pack();
    }// </editor-fold>//GEN-END:initComponents

	private void btnAddJuegoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnAddJuegoActionPerformed
            // TODO add your handling code here:
            biblioteca.removeAll();
            biblioteca.repaint();
            biblioteca.crearBiblioteca(); //Genero la biblioteca
            biblioteca.setVisible(true);
            JScrollBilioteca.setVisible(true);
            JScrollBilioteca.getVerticalScrollBar().setUnitIncrement(16);
            DisplayPanel.setVisible(true);
	}//GEN-LAST:event_btnAddJuegoActionPerformed

	private void btnSalirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnSalirActionPerformed
            // TODO add your handling code here:
            System.exit(0);
	}//GEN-LAST:event_btnSalirActionPerformed

	private void btnMisJuegosActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnMisJuegosActionPerformed
            try {
                biblioteca.removeAll(); //Elimino todos los elementos de la biblioteca (graficos)
                biblioteca.repaint();
                biblioteca.getMisJuegos();
                biblioteca.setVisible(true);
                JScrollBilioteca.setVisible(true);
                DisplayPanel.setVisible(true);
            } catch (IOException ex) {
                Logger.getLogger(Home.class.getName()).log(Level.SEVERE, null, ex);
            }
	}//GEN-LAST:event_btnMisJuegosActionPerformed

	private void backgroundKeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_backgroundKeyPressed
            // TODO add your handling code here:
	}//GEN-LAST:event_backgroundKeyPressed

	private void formMouseDragged(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_formMouseDragged
            // TODO add your handling code here:
            new Drag(background).moveWindow(evt);
	}//GEN-LAST:event_formMouseDragged

	private void biblioteca1MousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_biblioteca1MousePressed
            // TODO add your handling code here:
	}//GEN-LAST:event_biblioteca1MousePressed

	private void btnPreferencias1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnPreferencias1ActionPerformed
            // TODO add your handling code here:
            preferencias p = new preferencias();
            Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
            p.setLocation(dim.width / 2 - this.getSize().width / 2, dim.height / 2 - this.getSize().height / 2);
            p.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
            p.setVisible(true);

	}//GEN-LAST:event_btnPreferencias1ActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel DisplayPanel;
    private javax.swing.JScrollPane JScrollBilioteca;
    private javax.swing.JLabel background;
    private easyDOS.Biblioteca biblioteca;
    private keeptoo.KButton btnAddJuego;
    private keeptoo.KButton btnMisJuegos;
    private keeptoo.KButton btnPreferencias1;
    private keeptoo.KButton btnSalir;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JPanel jPanel1;
    // End of variables declaration//GEN-END:variables
}