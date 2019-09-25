/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package easyDOS;

import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

/**
 *
 * @author josel
 */
public class Auxiliares {

    public BufferedImage loadImage(String fileName) {

        BufferedImage buff = null;
        try {
            buff = ImageIO.read(getClass().getResourceAsStream(fileName));
        } catch (IOException e) {
            return null;
        }
        return buff;

    }

    public void inicializar() {
        try {
            String url = new java.io.File(".").getCanonicalPath();
            url = url + "/Juegos/";
            url = url.replace("\\", "/");
            File f = new File(url);
            if (f.exists()) {
                String listado = url + "listado_juegos.txt";
                url = url + "default.txt";
                File file = new File(url);
                File list = new File(listado);
                if (file.exists() && !file.isDirectory() && list.exists() && !list.isDirectory()) {
                    Home h = new Home();
                    h.setVisible(true);
                } else {
                    file.createNewFile();
                    createList();
                    Bienvenida b = new Bienvenida();
                    b.setVisible(true);
                }

            } else {
                new File(url).mkdirs();
                url = url + "default.txt";
                File file = new File(url);
                file.createNewFile();
                createList();
                Bienvenida b = new Bienvenida();
                b.setVisible(true);
            }
        } catch (IOException ex) {
            Logger.getLogger(Inicio.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    String getFileExtension(File file) {
        String name = file.getName();
        int lastIndexOf = name.lastIndexOf(".");
        if (lastIndexOf == -1) {
            return ""; // empty extension
        }
        return name.substring(lastIndexOf + 1);
    }

    public final void createList() throws IOException {
        String url = new java.io.File(".").getCanonicalPath();
        url = url + "/Juegos/listado_juegos.txt";
        url = url.replace("\\", "/");

        File file2 = new File(url);

        String texto = "   Doom (1993)\nID Software\nJohn Romero\nShooter\nViaja al infierno acribillando a balazos a todos los demonios que se pongan en tu camino. Uno de los juegos mas influyentes en su genero y un clasico imprescindible.\n/img/doomcover.jpg\n";
        texto = texto + "﻿System Shock (1994)\nLooking Glass Studios\nWarren Spector\nAventura\nPionero en el genero CyberPunk, System Shock fue la clave para todos los juegos que combinan el RPG y la accion.\n/img/systemshockcover.jpg\n";
        texto = texto + "﻿Monkey Island (1990)\nLucas Arts\nRon Gilbert\nAventura Grafica\nAcompaña a Guybrush Threepwood en su aventura para convertirse en el pirata mas temible de todos los tiempos.\n/img/monkeyislandcover.jpg\n";
        texto = texto + "﻿Wolfenstein 3D (1991)\nID Software\nJohn Romero\nShooter\nEl juego que inicio la fiebre de los First Person Shooter en elos años 90. A dia de hoy sigue siendo tan adictivo y divertido como en su momento.\n/img/wolfenstein3dcover.jpg\n";
        texto = texto + "Alone in the Dark (1992)\nInfogrames\nBruno Bonnel\nSurvival Horror\nAntes de Resident Evil, Alone in the Dark marco las pautas para el genero Survival Horror influyendo en el resto de titulos que se desarrollaron en la epoca y sorprendiendo con sus espectaculares graficos.\n/img/aloneinthedarkcover.jpg\n";
        texto = texto + "Alien Breed (1991)\nTeam 17\nMicro League\nAccion\nBrutal juego que accion inspirado en las peliculas de Alien y la accion de los arcades de la epoca.\n/img/alienbreedcover.jpg\n";
        texto = texto + "Corridor 7 (1994)\nCapstone LTD\nCapstone\nShooter\nJuego de accion y ciencia ficcion en el que recorreremos laberintos infestados de alienigenas.\n/img/corr7cover.jpg\n";
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file2), "UTF8"));
        writer.write(texto);
        writer.close();

    }

}
