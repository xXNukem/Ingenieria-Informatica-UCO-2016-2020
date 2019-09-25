/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package easyDOS;

/**
 *
 * @author josel
 */
public class Juego {

    private String Nombre;
    private String Desarrollador;
    private String Compania;
    private String Tipo;
    private String Descrip;
    private String imagen;
    private int id;
    private String url;

    public Juego() {
        this.imagen = "/img/AddGameUnknown.png";
        this.Nombre = "";
        this.Desarrollador = "";
        this.Compania = "";
        this.Tipo = "";
        this.Descrip = "";
        this.id = 99;
    }

    public Juego(int id, String Nombre, String Desarrollador, String Compania, String Tipo, String Descrip, String imagen) {
        this.Nombre = Nombre;
        this.Desarrollador = Desarrollador;
        this.Compania = Compania;
        this.Tipo = Tipo;
        this.Descrip = Descrip;
        this.imagen = imagen;
        this.id = id;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getImagen() {
        return imagen;
    }

    public void setImagen(String imagen) {
        this.imagen = imagen;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNombre() {
        return Nombre;
    }

    public void setNombre(String Nombre) {
        this.Nombre = Nombre;
    }

    public String getDesarrollador() {
        return Desarrollador;
    }

    public void setDesarrollador(String Desarrollador) {
        this.Desarrollador = Desarrollador;
    }

    public String getCompania() {
        return Compania;
    }

    public void setCompania(String Compania) {
        this.Compania = Compania;
    }

    public String getTipo() {
        return Tipo;
    }

    public void setTipo(String Tipo) {
        this.Tipo = Tipo;
    }

    public String getDescrip() {
        return Descrip;
    }

    public void setDescrip(String Descrip) {
        this.Descrip = Descrip;
    }

    public void copy(Juego g) {
        g.Descrip = this.Descrip;
        g.Tipo = this.Tipo;
        g.Compania = this.Compania;
        g.Desarrollador = this.Desarrollador;
        g.Nombre = this.Nombre;
        g.imagen = this.imagen;
        g.id = this.id;
    }
}
