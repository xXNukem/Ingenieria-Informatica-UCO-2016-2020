/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package easyDOS;

import java.awt.Color;
import java.awt.Cursor;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

/**
 *
 * @author Carlos
 */
public class preferencias extends javax.swing.JFrame {

    String fullscreen;
    int sensitivity;
    String core;
    String output;

    public preferencias() {
        initComponents();
        this.pack();
        this.setLocationRelativeTo(null);
        setTitle("Preferencias");
        kButton1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        btnAcceptChanges.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        setResizable(false);
        try {
            lectura_fichero();
        } catch (IOException ex) {
            Logger.getLogger(preferencias.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    void lectura_fichero() throws FileNotFoundException, IOException {

        String[] parts;
        String file = new java.io.File(".").getCanonicalPath();
        file = file.replace("\\", "/");
        file = file + "/dosBOX/";
        File dir = new File(file);
        if (!dir.exists()) {
            JFrame topFrame = (JFrame) SwingUtilities.getWindowAncestor(jPanel1);
            JOptionPane.showMessageDialog(jPanel1, "No se han encontrado los archivos de configuración para DosBox, se ejecutarán las preferencias en modo lectura.");
        } else {

            file = file + "Data/settings/";
            dir = new File(file);
            if (!dir.exists()) {
                jPanel1.removeAll();
            } else {
                file = file + "dosbox.conf";
                FileReader f = new FileReader(file);
                BufferedReader b = new BufferedReader(f);
                String cadena = b.readLine();
                while (cadena != null) {
                    parts = cadena.split("=");
                    if (parts[0].equals("fullscreen")) {
                        if (parts[1].equals("false")) {
                            btnFullScreenNo.setBackground(Color.green);
                            btnFullScreenYes.setBackground(Color.red);
                            fullscreen = "false";
                        } else {
                            btnFullScreenNo.setBackground(Color.red);
                            btnFullScreenYes.setBackground(Color.green);
                            fullscreen = "true";
                        }
                    }

                    if (parts[0].equals("sensitivity")) {
                        switch (parts[1]) {
                            case "50":
                                btnMouseSensivity50.setBackground(Color.green);
                                btnMouseSensivity100.setBackground(Color.red);
                                btnMouseSensivity150.setBackground(Color.red);
                                btnMouseSensivity200.setBackground(Color.red);
                                sensitivity = 50;
                                break;
                            case "100":
                                btnMouseSensivity50.setBackground(Color.red);
                                btnMouseSensivity100.setBackground(Color.green);
                                btnMouseSensivity150.setBackground(Color.red);
                                btnMouseSensivity200.setBackground(Color.red);
                                sensitivity = 100;
                                break;
                            case "150":
                                btnMouseSensivity50.setBackground(Color.red);
                                btnMouseSensivity100.setBackground(Color.red);
                                btnMouseSensivity150.setBackground(Color.green);
                                btnMouseSensivity200.setBackground(Color.red);
                                sensitivity = 150;
                                break;
                            case "200":
                                btnMouseSensivity50.setBackground(Color.red);
                                btnMouseSensivity100.setBackground(Color.red);
                                btnMouseSensivity150.setBackground(Color.red);
                                btnMouseSensivity200.setBackground(Color.green);
                                sensitivity = 200;
                                break;
                        }
                    }
                    if (parts[0].equals("core")) {
                        switch (parts[1]) {
                            case "auto":
                                btnCpuAuto.setBackground(Color.green);
                                btnCpuNormal.setBackground(Color.red);
                                btnCpuSimple.setBackground(Color.red);
                                btnCpuDina.setBackground(Color.red);
                                core = "auto";
                                break;
                            case "normal":
                                btnCpuAuto.setBackground(Color.red);
                                btnCpuNormal.setBackground(Color.green);
                                btnCpuSimple.setBackground(Color.red);
                                btnCpuDina.setBackground(Color.red);
                                core = "normal";
                                break;
                            case "simple":
                                btnCpuAuto.setBackground(Color.red);
                                btnCpuNormal.setBackground(Color.red);
                                btnCpuSimple.setBackground(Color.green);
                                btnCpuDina.setBackground(Color.red);
                                core = "simple";
                                break;
                            case "dynamic":
                                btnCpuAuto.setBackground(Color.red);
                                btnCpuNormal.setBackground(Color.red);
                                btnCpuSimple.setBackground(Color.red);
                                btnCpuDina.setBackground(Color.green);
                                core = "dynamic";
                                break;
                        }
                    }
                    if (parts[0].equals("output")) {
                        switch (parts[1]) {
                            case "surface":
                                btnRenderNormal.setBackground(Color.green);
                                btnRenderOpen.setBackground(Color.red);
                                btnRenderDir.setBackground(Color.red);
                                output = "surface";
                                break;
                            case "opengl":
                                btnRenderNormal.setBackground(Color.red);
                                btnRenderOpen.setBackground(Color.green);
                                btnRenderDir.setBackground(Color.red);
                                output = "opengl";
                                break;
                            case "ddraw":
                                btnRenderNormal.setBackground(Color.red);
                                btnRenderOpen.setBackground(Color.red);
                                btnRenderDir.setBackground(Color.green);
                                output = "ddraw";
                                break;
                        }
                    }
                    cadena = b.readLine();
                }
                b.close();
            }

        }

    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel2 = new javax.swing.JPanel();
        jPanel1 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        btnFullScreenYes = new javax.swing.JButton();
        btnFullScreenNo = new javax.swing.JButton();
        jLabel3 = new javax.swing.JLabel();
        btnMouseSensivity50 = new javax.swing.JButton();
        btnMouseSensivity100 = new javax.swing.JButton();
        btnMouseSensivity150 = new javax.swing.JButton();
        btnMouseSensivity200 = new javax.swing.JButton();
        jLabel4 = new javax.swing.JLabel();
        btnCpuAuto = new javax.swing.JButton();
        btnCpuNormal = new javax.swing.JButton();
        btnCpuSimple = new javax.swing.JButton();
        btnCpuDina = new javax.swing.JButton();
        jLabel5 = new javax.swing.JLabel();
        btnRenderOpen = new javax.swing.JButton();
        btnRenderDir = new javax.swing.JButton();
        btnRenderNormal = new javax.swing.JButton();
        btnAcceptChanges = new keeptoo.KButton();
        kButton1 = new keeptoo.KButton();
        jLabel6 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setUndecorated(true);

        jPanel1.setForeground(new java.awt.Color(255, 255, 255));
        jPanel1.setOpaque(false);

        jLabel1.setFont(new java.awt.Font("Arial Black", 1, 48)); // NOI18N
        jLabel1.setText("Preferencias");

        jLabel2.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jLabel2.setForeground(new java.awt.Color(255, 255, 255));
        jLabel2.setText("Pantalla Completa");

        btnFullScreenYes.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnFullScreenYes.setText("Si");
        btnFullScreenYes.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnFullScreenYesActionPerformed(evt);
            }
        });

        btnFullScreenNo.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnFullScreenNo.setText("No");
        btnFullScreenNo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnFullScreenNoActionPerformed(evt);
            }
        });

        jLabel3.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jLabel3.setForeground(new java.awt.Color(255, 255, 255));
        jLabel3.setText("Sensibilidad del ratón");

        btnMouseSensivity50.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnMouseSensivity50.setText("50");
        btnMouseSensivity50.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnMouseSensivity50ActionPerformed(evt);
            }
        });

        btnMouseSensivity100.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnMouseSensivity100.setText("100");
        btnMouseSensivity100.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnMouseSensivity100ActionPerformed(evt);
            }
        });

        btnMouseSensivity150.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnMouseSensivity150.setText("150");
        btnMouseSensivity150.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnMouseSensivity150ActionPerformed(evt);
            }
        });

        btnMouseSensivity200.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnMouseSensivity200.setText("200");
        btnMouseSensivity200.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnMouseSensivity200ActionPerformed(evt);
            }
        });

        jLabel4.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jLabel4.setForeground(new java.awt.Color(255, 255, 255));
        jLabel4.setText("Tipo de CPU");

        btnCpuAuto.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnCpuAuto.setText("Auto");
        btnCpuAuto.setToolTipText("");
        btnCpuAuto.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCpuAutoActionPerformed(evt);
            }
        });

        btnCpuNormal.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnCpuNormal.setText("Normal");
        btnCpuNormal.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCpuNormalActionPerformed(evt);
            }
        });

        btnCpuSimple.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnCpuSimple.setText("Simple");
        btnCpuSimple.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCpuSimpleActionPerformed(evt);
            }
        });

        btnCpuDina.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnCpuDina.setText("Dinámica");
        btnCpuDina.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCpuDinaActionPerformed(evt);
            }
        });

        jLabel5.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
        jLabel5.setForeground(new java.awt.Color(255, 255, 255));
        jLabel5.setText("Renderizado");

        btnRenderOpen.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnRenderOpen.setText("OpenGL");
        btnRenderOpen.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRenderOpenActionPerformed(evt);
            }
        });

        btnRenderDir.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnRenderDir.setText("DirectX");
        btnRenderDir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRenderDirActionPerformed(evt);
            }
        });

        btnRenderNormal.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnRenderNormal.setText("Normal");
        btnRenderNormal.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRenderNormalActionPerformed(evt);
            }
        });

        btnAcceptChanges.setText("Aceptar");
        btnAcceptChanges.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        btnAcceptChanges.setkEndColor(new java.awt.Color(153, 0, 153));
        btnAcceptChanges.setkHoverEndColor(new java.awt.Color(153, 153, 255));
        btnAcceptChanges.setkHoverForeGround(new java.awt.Color(255, 255, 255));
        btnAcceptChanges.setkHoverStartColor(new java.awt.Color(153, 153, 255));
        btnAcceptChanges.setkSelectedColor(new java.awt.Color(102, 102, 255));
        btnAcceptChanges.setkStartColor(new java.awt.Color(102, 204, 255));
        btnAcceptChanges.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAcceptChangesActionPerformed(evt);
            }
        });

        kButton1.setText("Cancelar");
        kButton1.setFont(new java.awt.Font("Tahoma", 0, 18)); // NOI18N
        kButton1.setkEndColor(new java.awt.Color(153, 0, 153));
        kButton1.setkHoverEndColor(new java.awt.Color(153, 153, 255));
        kButton1.setkHoverForeGround(new java.awt.Color(255, 255, 255));
        kButton1.setkHoverStartColor(new java.awt.Color(153, 153, 255));
        kButton1.setkSelectedColor(new java.awt.Color(102, 102, 255));
        kButton1.setkStartColor(new java.awt.Color(102, 204, 255));
        kButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                kButton1ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(2510, 2510, 2510)
                .addComponent(jLabel1))
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(10, 10, 10)
                .addComponent(jLabel2)
                .addGap(49, 49, 49)
                .addComponent(btnFullScreenYes, javax.swing.GroupLayout.PREFERRED_SIZE, 59, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(21, 21, 21)
                .addComponent(btnFullScreenNo, javax.swing.GroupLayout.PREFERRED_SIZE, 60, javax.swing.GroupLayout.PREFERRED_SIZE))
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(10, 10, 10)
                .addComponent(jLabel3)
                .addGap(22, 22, 22)
                .addComponent(btnMouseSensivity50)
                .addGap(37, 37, 37)
                .addComponent(btnMouseSensivity100)
                .addGap(47, 47, 47)
                .addComponent(btnMouseSensivity150)
                .addGap(37, 37, 37)
                .addComponent(btnMouseSensivity200))
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(10, 10, 10)
                .addComponent(jLabel4)
                .addGap(102, 102, 102)
                .addComponent(btnCpuAuto)
                .addGap(18, 18, 18)
                .addComponent(btnCpuNormal)
                .addGap(13, 13, 13)
                .addComponent(btnCpuSimple)
                .addGap(15, 15, 15)
                .addComponent(btnCpuDina))
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(10, 10, 10)
                .addComponent(jLabel5)
                .addGap(94, 94, 94)
                .addComponent(btnRenderNormal)
                .addGap(11, 11, 11)
                .addComponent(btnRenderDir)
                .addGap(23, 23, 23)
                .addComponent(btnRenderOpen))
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(90, 90, 90)
                .addComponent(kButton1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(15, 15, 15)
                .addComponent(btnAcceptChanges, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(11, 11, 11)
                .addComponent(jLabel1, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(19, 19, 19)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel2)
                    .addComponent(btnFullScreenYes)
                    .addComponent(btnFullScreenNo))
                .addGap(29, 29, 29)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel3)
                    .addComponent(btnMouseSensivity50)
                    .addComponent(btnMouseSensivity100)
                    .addComponent(btnMouseSensivity150)
                    .addComponent(btnMouseSensivity200))
                .addGap(39, 39, 39)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel4)
                    .addComponent(btnCpuAuto)
                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(btnCpuSimple)
                        .addComponent(btnCpuNormal))
                    .addComponent(btnCpuDina))
                .addGap(29, 29, 29)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel5)
                    .addComponent(btnRenderNormal)
                    .addComponent(btnRenderDir)
                    .addComponent(btnRenderOpen))
                .addGap(49, 49, 49)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(kButton1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnAcceptChanges, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
        );

        jLabel6.setIcon(new javax.swing.ImageIcon(getClass().getResource("/img/fondo.jpg"))); // NOI18N
        jLabel6.setText("jLabel6");

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, 622, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
            .addComponent(jLabel6, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jLabel6, javax.swing.GroupLayout.PREFERRED_SIZE, 430, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void kButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_kButton1ActionPerformed
        // TODO add your handling code here:
        this.dispose();
    }//GEN-LAST:event_kButton1ActionPerformed

    private void btnAcceptChangesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnAcceptChangesActionPerformed
        // TODO add your handling code here:
        try {
            saveOpts();
            this.dispose();
        } catch (IOException ex) {
            Logger.getLogger(preferencias.class.getName()).log(Level.SEVERE, null, ex);
        }
    }//GEN-LAST:event_btnAcceptChangesActionPerformed

    private void btnRenderNormalActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRenderNormalActionPerformed
        btnRenderNormal.setBackground(Color.green);
        btnRenderDir.setBackground(Color.red);
        btnRenderOpen.setBackground(Color.red);
        output = "surface";
    }//GEN-LAST:event_btnRenderNormalActionPerformed

    private void btnRenderDirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRenderDirActionPerformed
        btnRenderNormal.setBackground(Color.red);
        btnRenderDir.setBackground(Color.green);
        btnRenderOpen.setBackground(Color.red);
        output = "ddraw";
    }//GEN-LAST:event_btnRenderDirActionPerformed

    private void btnRenderOpenActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRenderOpenActionPerformed
        btnRenderNormal.setBackground(Color.red);
        btnRenderDir.setBackground(Color.red);
        btnRenderOpen.setBackground(Color.green);
        output = "opengl";
    }//GEN-LAST:event_btnRenderOpenActionPerformed

    private void btnCpuDinaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnCpuDinaActionPerformed
        btnCpuAuto.setBackground(Color.red);
        btnCpuNormal.setBackground(Color.red);
        btnCpuSimple.setBackground(Color.red);
        btnCpuDina.setBackground(Color.green);
        core = "dynamic";
    }//GEN-LAST:event_btnCpuDinaActionPerformed

    private void btnCpuSimpleActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnCpuSimpleActionPerformed
        btnCpuAuto.setBackground(Color.red);
        btnCpuNormal.setBackground(Color.red);
        btnCpuSimple.setBackground(Color.green);
        btnCpuDina.setBackground(Color.red);
        core = "simple";
    }//GEN-LAST:event_btnCpuSimpleActionPerformed

    private void btnCpuNormalActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnCpuNormalActionPerformed
        btnCpuAuto.setBackground(Color.red);
        btnCpuNormal.setBackground(Color.green);
        btnCpuSimple.setBackground(Color.red);
        btnCpuDina.setBackground(Color.red);
        core = "normal";
    }//GEN-LAST:event_btnCpuNormalActionPerformed

    private void btnCpuAutoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnCpuAutoActionPerformed
        btnCpuAuto.setBackground(Color.green);
        btnCpuNormal.setBackground(Color.red);
        btnCpuSimple.setBackground(Color.red);
        btnCpuDina.setBackground(Color.red);
        core = "auto";
    }//GEN-LAST:event_btnCpuAutoActionPerformed

    private void btnMouseSensivity200ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnMouseSensivity200ActionPerformed
        btnMouseSensivity50.setBackground(Color.red);
        btnMouseSensivity100.setBackground(Color.red);
        btnMouseSensivity150.setBackground(Color.red);
        btnMouseSensivity200.setBackground(Color.green);
        sensitivity = 200;
    }//GEN-LAST:event_btnMouseSensivity200ActionPerformed

    private void btnMouseSensivity150ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnMouseSensivity150ActionPerformed
        btnMouseSensivity50.setBackground(Color.red);
        btnMouseSensivity100.setBackground(Color.red);
        btnMouseSensivity150.setBackground(Color.green);
        btnMouseSensivity200.setBackground(Color.red);
        sensitivity = 150;
    }//GEN-LAST:event_btnMouseSensivity150ActionPerformed

    private void btnMouseSensivity100ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnMouseSensivity100ActionPerformed
        btnMouseSensivity50.setBackground(Color.red);
        btnMouseSensivity100.setBackground(Color.green);
        btnMouseSensivity150.setBackground(Color.red);
        btnMouseSensivity200.setBackground(Color.red);
        sensitivity = 100;
    }//GEN-LAST:event_btnMouseSensivity100ActionPerformed

    private void btnMouseSensivity50ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnMouseSensivity50ActionPerformed
        btnMouseSensivity50.setBackground(Color.green);
        btnMouseSensivity100.setBackground(Color.red);
        btnMouseSensivity150.setBackground(Color.red);
        btnMouseSensivity200.setBackground(Color.red);
        sensitivity = 50;
    }//GEN-LAST:event_btnMouseSensivity50ActionPerformed

    private void btnFullScreenNoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnFullScreenNoActionPerformed
        btnFullScreenYes.setBackground(Color.red);
        btnFullScreenNo.setBackground(Color.green);
        fullscreen = "false";
    }//GEN-LAST:event_btnFullScreenNoActionPerformed

    private void btnFullScreenYesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnFullScreenYesActionPerformed
        btnFullScreenYes.setBackground(Color.green);
        btnFullScreenNo.setBackground(Color.red);
        fullscreen = "true";
    }//GEN-LAST:event_btnFullScreenYesActionPerformed

    private void saveOpts() throws FileNotFoundException, IOException {
        //FICHERO INICIAL        
        String file = new java.io.File(".").getCanonicalPath();
        file = file.replace("\\", "/");
        file = file + "/dosBOX/Data/settings/dosbox.conf";
        File dir = new File(file);
        if (!dir.exists()) {
            jPanel1.removeAll();
        } else {
            FileReader f = new FileReader(file);
            BufferedReader b = new BufferedReader(f);
            String cadena;

            //FICHERO AUXILIAR
            String url = new java.io.File(".").getCanonicalPath();
            url = url.replace("\\", "/");
            url = url + "temp.conf";

            File file2 = new File(url);
            file2.createNewFile();

            FileWriter fw = new FileWriter(file2);

            String[] parts;

            while ((cadena = b.readLine()) != null) {

                parts = cadena.split("=");
                switch (parts[0]) {
                    case "fullscreen":
                        fw.append("fullscreen=" + fullscreen + "\n");
                        break;
                    case "sensitivity":
                        fw.append("sensitivity=" + Integer.toString(sensitivity) + "\n");
                        break;
                    case "core":
                        fw.append("core=" + core + "\n");
                        break;
                    case "output":
                        fw.append("output=" + output + "\n");
                        break;
                    default:
                        fw.append(cadena + "\n");
                        break;
                }

            }

            b.close();
            fw.close();

            File antiguo = new File(file);
            antiguo.delete();

            File nuevo = new File(url);
            boolean success = nuevo.renameTo(antiguo);

        }

    }


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private keeptoo.KButton btnAcceptChanges;
    private javax.swing.JButton btnCpuAuto;
    private javax.swing.JButton btnCpuDina;
    private javax.swing.JButton btnCpuNormal;
    private javax.swing.JButton btnCpuSimple;
    private javax.swing.JButton btnFullScreenNo;
    private javax.swing.JButton btnFullScreenYes;
    private javax.swing.JButton btnMouseSensivity100;
    private javax.swing.JButton btnMouseSensivity150;
    private javax.swing.JButton btnMouseSensivity200;
    private javax.swing.JButton btnMouseSensivity50;
    private javax.swing.JButton btnRenderDir;
    private javax.swing.JButton btnRenderNormal;
    private javax.swing.JButton btnRenderOpen;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private keeptoo.KButton kButton1;
    // End of variables declaration//GEN-END:variables
}
