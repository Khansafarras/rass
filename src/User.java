public class User {
    protected String nama;
    protected String username;
    protected String password;

    public User(String nama, String username, String password) {
        this.nama = nama;
        this.username = username;
        this.password = password;
    }

    public boolean login(String u, String p) {
        return username.equals(u) && password.equals(p);
    }

    public String getUsername() {
        return username;
    }

    public String getNama() {
        return nama;
    }
}
