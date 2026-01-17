public class Kasir extends User {
    private String idKasir;

    public Kasir(String idKasir, String nama, String username, String password) {
        super(nama, username, password);
        this.idKasir = idKasir;
    }

    public String getIdKasir() {
        return idKasir;
    }
}
