import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;

public class MainGUI {

    static CardLayout card = new CardLayout();
    static JPanel mainPanel = new JPanel(card);

    static ArrayList<Kasir> listKasir = new ArrayList<>();
    static Kasir kasirAktif;
    static JLabel lblKasir = new JLabel();

    static Color PINK = new Color(255,105,180);
    static Color MINT = new Color(152,251,200);
    static Color BG = new Color(245,250,248);

    public static void main(String[] args) {

        JFrame frame = new JFrame("IndoMarket POS");
        frame.setSize(1200, 700);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);

        /* ================= HEADER ================= */
        JPanel header = new JPanel(new BorderLayout());
        header.setBackground(PINK);
        header.setBorder(BorderFactory.createEmptyBorder(10,20,10,20));

        JLabel title = new JLabel("INDOMARKET POS");
        title.setFont(new Font("Segoe UI", Font.BOLD, 26));
        title.setForeground(Color.WHITE);

        lblKasir.setFont(new Font("Segoe UI", Font.PLAIN, 14));
        lblKasir.setForeground(Color.WHITE);

        header.add(title, BorderLayout.WEST);
        header.add(lblKasir, BorderLayout.EAST);

        /* ================= LOGIN ================= */
        JPanel loginPanel = new JPanel(new GridBagLayout());
        loginPanel.setBackground(BG);

        JPanel loginCard = cardPutih("LOGIN KASIR");

        JTextField tUser = new JTextField();
        JPasswordField tPass = new JPasswordField();

        JButton bLogin = tombol("LOGIN", PINK);
        JButton bReg = tombol("REGISTER", MINT);

        loginCard.add(new JLabel("Username"));
        loginCard.add(input(tUser));
        loginCard.add(Box.createVerticalStrut(10));
        loginCard.add(new JLabel("Password"));
        loginCard.add(input(tPass));
        loginCard.add(Box.createVerticalStrut(20));
        loginCard.add(bLogin);
        loginCard.add(Box.createVerticalStrut(10));
        loginCard.add(bReg);

        loginPanel.add(loginCard);

        /* ================= REGISTER ================= */
        JPanel registerPanel = new JPanel(new GridBagLayout());
        registerPanel.setBackground(BG);

        JPanel regCard = cardPutih("REGISTRASI KASIR");

        JTextField rNama = new JTextField();
        JTextField rUser = new JTextField();
        JPasswordField rPass = new JPasswordField();

        JButton bDaftar = tombol("DAFTAR", PINK);
        JButton bBack = tombol("KEMBALI", Color.GRAY);

        regCard.add(new JLabel("Nama Kasir"));
        regCard.add(input(rNama));
        regCard.add(Box.createVerticalStrut(10));
        regCard.add(new JLabel("Username"));
        regCard.add(input(rUser));
        regCard.add(Box.createVerticalStrut(10));
        regCard.add(new JLabel("Password"));
        regCard.add(input(rPass));
        regCard.add(Box.createVerticalStrut(20));
        regCard.add(bDaftar);
        regCard.add(Box.createVerticalStrut(10));
        regCard.add(bBack);

        registerPanel.add(regCard);

        /* ================= MENU ================= */
        JPanel menuPanel = new JPanel(new GridBagLayout());
        menuPanel.setBackground(Color.WHITE);

        JButton bTrans = tombol("TRANSAKSI", MINT);
        JButton bLogout = tombol("LOGOUT", PINK);

        JPanel menuBox = new JPanel();
        menuBox.add(bTrans);
        menuBox.add(bLogout);

        menuPanel.add(menuBox);

        /* ================= TRANSAKSI ================= */
        JPanel transaksiPanel = new JPanel(new BorderLayout(10,10));
        transaksiPanel.setBackground(BG);
        transaksiPanel.setBorder(BorderFactory.createEmptyBorder(15,15,15,15));

        DefaultTableModel model = new DefaultTableModel(
                new Object[]{"Produk","Qty","Harga","Subtotal"},0
        );
        JTable table = new JTable(model);
        table.setRowHeight(28);

        JTextArea struk = new JTextArea();
        struk.setFont(new Font("Consolas", Font.PLAIN, 13));
        struk.setEditable(false);

        JComboBox<String> barang = new JComboBox<>(new String[]{
                "Beras - 12000","Gula - 14000","Minyak - 16000","Teh - 8000"
        });
        JTextField qty = new JTextField(5);

        JButton tambah = tombol("Tambah", MINT);
        JButton bayar = tombol("Bayar", PINK);
        JButton kembali = tombol("Kembali", Color.GRAY);

        JLabel total = new JLabel("TOTAL : Rp 0");
        total.setFont(new Font("Segoe UI", Font.BOLD, 18));

        final int[] totalHarga = {0};

        tambah.addActionListener(e -> {
            try {
                String item = barang.getSelectedItem().toString();
                int harga = Integer.parseInt(item.split("-")[1].trim());
                int jml = Integer.parseInt(qty.getText());
                int sub = harga * jml;

                model.addRow(new Object[]{
                        item.split("-")[0], jml, harga, sub
                });

                totalHarga[0] += sub;
                total.setText("TOTAL : Rp " + totalHarga[0]);
                qty.setText("");
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(frame, "Jumlah harus angka!");
            }
        });

        bayar.addActionListener(e -> {
            struk.setText("");
            struk.append("      INDOMARKET\n");
            struk.append("  ------------------------\n");
            struk.append("  Kasir : " + kasirAktif.getNama() + "\n");
            struk.append("  ------------------------\n");

            for (int i = 0; i < model.getRowCount(); i++) {
                struk.append(
                        String.format(
                                "  %-10s x%-2s Rp %s\n",
                                model.getValueAt(i,0),
                                model.getValueAt(i,1),
                                model.getValueAt(i,3)
                        )
                );
            }

            struk.append("  ------------------------\n");
            struk.append("  TOTAL : Rp " + totalHarga[0] + "\n");
            struk.append("  Terima Kasih 💖\n");

            model.setRowCount(0);
            totalHarga[0] = 0;
            total.setText("TOTAL : Rp 0");
        });

        JPanel topTrans = new JPanel();
        topTrans.add(barang);
        topTrans.add(qty);
        topTrans.add(tambah);

        JPanel bottom = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        bottom.add(total);
        bottom.add(bayar);
        bottom.add(kembali);

        transaksiPanel.add(topTrans, BorderLayout.NORTH);
        transaksiPanel.add(new JScrollPane(table), BorderLayout.CENTER);
        transaksiPanel.add(new JScrollPane(struk), BorderLayout.EAST);
        transaksiPanel.add(bottom, BorderLayout.SOUTH);

        /* ================= LOGIC ================= */
        bLogin.addActionListener(e -> {
            for (Kasir k : listKasir) {
                if (k.login(tUser.getText(), tPass.getText())) {
                    kasirAktif = k;
                    lblKasir.setText("Kasir : " + k.getNama());
                    card.show(mainPanel, "menu");
                    return;
                }
            }
            JOptionPane.showMessageDialog(frame, "Login gagal");
        });

        bDaftar.addActionListener(e -> {
            listKasir.add(new Kasir(
                    "K" + (listKasir.size()+1),
                    rNama.getText(),
                    rUser.getText(),
                    new String(rPass.getPassword())
            ));
            JOptionPane.showMessageDialog(frame, "Registrasi berhasil");
            card.show(mainPanel, "login");
        });

        bReg.addActionListener(e -> card.show(mainPanel, "register"));
        bBack.addActionListener(e -> card.show(mainPanel, "login"));
        bTrans.addActionListener(e -> card.show(mainPanel, "transaksi"));
        bLogout.addActionListener(e -> card.show(mainPanel, "login"));
        kembali.addActionListener(e -> card.show(mainPanel, "menu"));

        mainPanel.add(loginPanel, "login");
        mainPanel.add(registerPanel, "register");
        mainPanel.add(menuPanel, "menu");
        mainPanel.add(transaksiPanel, "transaksi");

        frame.add(header, BorderLayout.NORTH);
        frame.add(mainPanel, BorderLayout.CENTER);
        card.show(mainPanel, "login");
        frame.setVisible(true);
    }

    /* ================= KOMPONEN ================= */
    static JPanel cardPutih(String judul) {
        JPanel p = new JPanel();
        p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS));
        p.setBackground(Color.WHITE);
        p.setPreferredSize(new Dimension(360, 420));
        p.setBorder(BorderFactory.createEmptyBorder(25,30,25,30));

        JLabel l = new JLabel(judul);
        l.setFont(new Font("Segoe UI", Font.BOLD, 22));
        l.setForeground(PINK);
        l.setAlignmentX(Component.CENTER_ALIGNMENT);

        p.add(l);
        p.add(Box.createVerticalStrut(25));
        return p;
    }

    static JTextField input(JTextField t) {
        t.setMaximumSize(new Dimension(260,35));
        t.setAlignmentX(Component.CENTER_ALIGNMENT);
        return t;
    }

    static JButton tombol(String text, Color c) {
        JButton b = new JButton(text);
        b.setBackground(c);
        b.setForeground(Color.WHITE);
        b.setFocusPainted(false);
        b.setFont(new Font("Segoe UI", Font.BOLD, 14));
        b.setMaximumSize(new Dimension(260, 38));
        b.setAlignmentX(Component.CENTER_ALIGNMENT);
        return b;
    }
}
